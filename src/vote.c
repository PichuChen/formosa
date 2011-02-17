/*
 * written by lthuang@cc.nsysu.edu.tw
 */

#include "bbs.h"
#include "tsbbs.h"
#include <sys/stat.h>


#ifdef USE_VOTE
/* TODO: 開票自動張貼結果 */

int TheTickets = 0;
char TheTitle[STRLEN] = "";
int MyTickets;
int MyOffset;
struct Box MyBox;

BOOL show_info = 0;

extern BOOL hasBMPerm;


#if 0
typedef struct VOTE
{
	char filename[15];
	char ident;
	char title[STRLEN];
	char owner[IDLEN];
	char allow_ip[27];
	time_t start_time;
	time_t end_time;
	int tickets;
	unsigned int userlevel;
	time_t firstlogin;
	unsigned int numlogins;
	unsigned int numposts;
}
VOTE;
#endif


static void setvotefile2(char *fname, char *direct, char *vf, char *f)
{
	setdotfile(fname, direct, vf);
	strcat(fname, f);
}


void DisplayNewVoteMesg()
{
	pmore("doc/NewVote", TRUE);
}


void CheckNewSysVote()
{
	static BOOL sysvoting = FALSE;

	if (!sysvoting)
	{
		if (is_new_vote("sysop", curuser.lastlogin))	/* Here, use board ``sysop'' for system voting */
			sysvoting = TRUE;
	}
	if (sysvoting)
		DisplayNewVoteMesg();
}


static void vote_title()
{
	title_func(BBSTITLE, "投票區");
	outs(_msg_vote_17);
	if (show_info)
		prints("[7m  %4s %-12.12s %12s %15s %4s %6s %6s %10s [m",
		       "編號", "投票名稱", "舉辦人", "上站來源", "等級",
		       "上站數", "張貼數", "註冊時間");
	else
		prints("[7m  %4s %-34.34s %4s %8s   %10s %10s[m",
		       "編號", "投票名稱", "認證", "投票開始", "預計開票", "每人票數");
}


static char *Vtime(time_t *ti)
{
	static char timestr[11];

	strftime(timestr, sizeof(timestr), "%Y.%m.%d", localtime(ti));
	return timestr;
}


static void vote_entry(const int x, void *ep, const int idx, const int top, const int last, const int rows)
{
	VOTE *ent = (VOTE *)ep;
	int i, num;

	for (i = top - idx; i < rows && i <= last - idx; i++)
	{
		num = i + idx;

		if (show_info)
		{
			prints("   %3d %-12.12s %12s %15s %4d %6d %6d %10s\n",
			       num, ent[i].title, ent[i].owner,
			       *(ent[i].allow_ip) ? ent[i].allow_ip : "不限",
			       ent[i].userlevel, ent[i].numlogins, ent[i].numposts,
			       (ent[i].firstlogin) ? Vtime(&(ent[i].firstlogin)) : "不限");
		}
		else
		{
			/* kmwang:20000831:勿再犯, 勿將兩段 prints 合併,
			   由於 Vtime 傳址回來, prints 處理時,
			   end_time 的址將會是 start_time 的址. */
			prints("   %3d %-35.35s %s %s - ",
			       num, ent[i].title, (ent[i].ident == 7) ? _str_marker : "  ",
			       Vtime(&(ent[i].start_time)));
			prints("%s   %2d\n",
			       Vtime(&(ent[i].end_time)),
			       ent[i].tickets);
		}
	}
}


static void cand_title()
{
	title_func("投票區", TheTitle);
	outs("\n(→)(Enter)選定投票項目 (←)(q)離開\n\
(a)增加候選項目? (d)刪除候選項目 (E)修改候選項目\n\
[7m  編號 圈選 候選項目                                                          [m");
}


static void cand_entry(int x, void *ep, int idx, int top, int last, int rows)
{
	CAND *ent = (CAND *)ep;
	int i, num;
	unsigned long j;

	for (num = top; num <= last; num++)
	{
		if (num - top >= rows)
			break;
		i = num - idx;

		j = 1 << (num - 1);
		prints("   %3d  %s  %s\n",
		       num, (MyBox.vbits & j) ? "◎" : "  ", ent[i].item);
	}
}


static int ccmd_enter(int ent, CAND *cinfo, char *direct)
{
	/* 你不能再多投了啦 */
	if (MyTickets >= TheTickets)
	{
		msg(_msg_vote_7, TheTickets);
		getkey();
		return C_FULL;
	}

	/* sarek:02/23:2001:confirm for voting */
	msg(_msg_not_sure);
	if (igetkey() != 'y')
	{
		msg(_msg_abort);
		getkey();
		return C_FULL;
	}

	/* 將票投入暫存箱 */
	if (!(MyBox.vbits & (1 << (ent - 1))))
	{
		MyBox.vbits |= 1 << (ent - 1);
		strcpy(MyBox.userid, curuser.userid);
		MyTickets++;
	}

	/* 填寫投票意見表 */
	move(10, 0);
	clrtobot();
	if (getdata(10, 0, "您對本次投票有其它意見嗎? [n]: ", genbuf, 2,
		    ECHONOSP) && genbuf[0] == 'y')
	{
		char buf[PATHLEN];

		if (getdata(11, 0, "", buf, 60, XECHO))
		{
			sprintf(genbuf, "\n%-12s: %s", curuser.userid, buf);
			setdotfile(buf, direct, "mess");
			append_record(buf, genbuf, strlen(genbuf));
		}
	}
	return C_FULL;
}


static int ccmd_add(int ent, CAND *cinfo, char *direct)
{
	CAND ch;

	if (!hasBMPerm)
		return C_NONE;

	if (get_num_records(direct, sizeof(*cinfo)) > sizeof(MyBox.vbits) * 8)
	{
		msg("候選項目最多 %d 項", sizeof(MyBox.vbits) * 8);
		getkey();
		return C_FOOT;
	}

	memset(&ch, 0, sizeof(ch));
	if (getdata(b_line, 0, "候選項目名: ", ch.item, sizeof(ch.item), XECHO))
	{
		append_record(direct, &ch, sizeof(ch));
		return C_INIT;
	}
	return C_FOOT;
}


static int ccmd_edit(int ent, CAND *cinfo, char *direct)
{
	if (!hasBMPerm)
		return C_NONE;

	if (getdata_str(b_line, 0, "候選項目名: ", cinfo->item, sizeof(cinfo->item),
		    XECHO, cinfo->item))
	{
		substitute_record(direct, cinfo, sizeof(*cinfo), ent);
		return C_INIT;
	}
	return C_FOOT;
}


static int ccmd_delete(int ent, CAND *cinfo, char *direct)
{
	if (!hasBMPerm)
		return C_NONE;

	msg("Are you sure ? [n]: ");
	if (igetkey() == 'y')
	{
		/* 刪除候選項目 */
		delete_record(direct, sizeof(*cinfo), ent);
		return C_INIT;
	}
	return C_FOOT;
}


struct one_key cand_comms[] =
{
	{'a', ccmd_add},
	{'r', ccmd_enter},
	{'d', ccmd_delete},
	{'E', ccmd_edit},
	{0, NULL}
};


static int vcmd_desc(int ent, VOTE *vinfo, char *direct)
{
	/* 選舉說明 */
	setvotefile2(genbuf, direct, vinfo->filename, "/desc");
	pmore(genbuf, TRUE);

	return C_FULL;
}


static time_t get_time(char *str)
{
	struct tm tm;
	int year;

	memset(&tm, 0, sizeof(tm));
	sscanf(str, "%4d.%02d.%02d",
	       &year, &(tm.tm_mon), &(tm.tm_mday));
	tm.tm_year = year - 1900;
	tm.tm_mon -= 1;
	return mktime(&tm);
}


static int set_vote(char *path, VOTE *vinfo)
{
	char filename[PATHLEN];

	/* sarek: 12/03/2000
	   原來vinfo->filename指向正確的path,
	   但在下面的memset()會被清除掉 */
	char orig_vinfo_filename[PATHLEN];
	strcpy(orig_vinfo_filename, vinfo->filename);

	move(1, 0);
	clrtobot();

     	memset(vinfo, 0, sizeof(VOTE));

	/* sarek: 12/03/2000 */
	strcpy(vinfo->filename, orig_vinfo_filename);

	outs("[請注意] <不作限制則按 Enter 略過>");

	if (!getdata_str(3, 0, "1) 投票名稱 : ", genbuf, sizeof(vinfo->title), XECHO, vinfo->title))
		return -1;
	strcpy(vinfo->title, genbuf);

	if (vinfo->start_time == 0)
		vinfo->start_time = time(0);
	strcpy(genbuf, Vtime(&(vinfo->start_time)));
	if (getdata_str(4, 0, "2) 投票開始(YYYY.mm.dd) : ", genbuf, 11, ECHONOSP, genbuf))
		vinfo->start_time = get_time(genbuf);

	memset(genbuf, 0, sizeof(genbuf));
	if (vinfo->end_time == 0)
		vinfo->end_time = time(0) + 86400;
	strcpy(genbuf, Vtime(&(vinfo->end_time)));
	if (getdata_str(5, 0, "3) 預計開票(YYYY.mm.dd) : ", genbuf, 11, ECHONOSP, genbuf))
		vinfo->end_time = get_time(genbuf);

	if (vinfo->tickets == 0)
		vinfo->tickets = 1;
	sprintf(genbuf, "%d", vinfo->tickets);
	if (getdata_str(6, 0, "4) 每人票數 : ", genbuf, 3, ECHONOSP, genbuf))
		vinfo->tickets = atoi(genbuf);
	if (vinfo->tickets <= 0 || vinfo->tickets > sizeof(MyBox.vbits) * 8)
		return -1;

	if (getdata_str(7, 0, "5) 上站來源(例如140.117) : ", genbuf, sizeof(vinfo->allow_ip), ECHONOSP,
		    vinfo->allow_ip))
	{
		strcpy(vinfo->allow_ip, genbuf);
	}

	sprintf(genbuf, "%d", vinfo->userlevel);
	if (getdata_str(8, 0, "6) 使用者等級(例如50) : ", genbuf, 4, ECHONOSP, genbuf))
		vinfo->userlevel = atoi(genbuf);

	strcpy(genbuf, "n");
	getdata_str(9, 0, "7) 已身份認證者才可投(y/n): ", genbuf, 2, ECHONOSP, genbuf);
	if (genbuf[0] == 'y')
		vinfo->ident = 7;
	else
		vinfo->ident = 0;

	if (vinfo->firstlogin != 0)
		strcpy(genbuf, Vtime(&(vinfo->firstlogin)));
	else
		genbuf[0] = '\0';
	if (getdata_str(10, 0, "8) 註冊日期(YYYY.mm.dd)：", genbuf, 11, ECHONOSP, genbuf))
		vinfo->firstlogin = get_time(genbuf);

	sprintf(genbuf, "%d", vinfo->numlogins);
	if (getdata_str(11, 0, "9) 上站次數 : ", genbuf, 7, ECHONOSP, genbuf))
		vinfo->numlogins = atoi(genbuf);

	sprintf(genbuf, "%d", vinfo->numposts);
	if (getdata_str(12, 0, "10) 張貼次數 : ", genbuf, 7, ECHONOSP, genbuf))
		vinfo->numposts = atoi(genbuf);

	setvotefile2(filename, path, vinfo->filename, "/desc");
	vedit(filename, NULL, NULL);

	return 0;
}


static int vcmd_edit(int ent, VOTE *vinfo, char *direct)
{
	if (!hasBMPerm)
		return C_NONE;

	if (set_vote(direct, vinfo) == -1)
		return C_FULL;

	if (substitute_record(direct, vinfo, sizeof(*vinfo), ent) == 0)
		return C_INIT;
	return C_FULL;
}


static int vcmd_delete(int ent, VOTE *vinfo, char *direct)
{
	if (!hasBMPerm)
		return C_NONE;

	msg(_msg_not_sure);
	if (igetkey() == 'y')
	{
		/* 刪除選舉資料 */
		delete_record(direct, sizeof(*vinfo), ent);
		if (get_num_records(direct, sizeof(char)) == 0)
			unlink(direct);

		/* 刪除選舉目錄 */
		setdotfile(genbuf, direct, vinfo->filename);
		myunlink(genbuf);
		return C_INIT;
	}
	return C_FULL;
}


/*box*/
static int vcmd_result(int ent, VOTE *vinfo, char *direct);
static int vcmd_enter(int ent, VOTE *vinfo, char *direct)
{
	char tmpdir[PATHLEN];
	int ca_ccur = 0, fd;
	unsigned long j;
	int num;

	if (vinfo->start_time > time(0))
	{
		showmsg("別急咩..投票還沒開始ㄡ~");
		return C_FULL;
	}

	if (time(0) > vinfo->end_time)
	{
		showmsg("投票活動已經結束了, 看看結果吧!");
		return vcmd_result(ent, vinfo, direct);
	}

	memset(&MyBox, 0, sizeof(MyBox));

	MyOffset = -1;
	/* 是否已投過票 */
	j = 1;
	num = 0;
	setvotefile2(genbuf, direct, vinfo->filename, "/box");
	if ((fd = open(genbuf, O_RDONLY)) > 0)
	{
		while (read(fd, &MyBox, sizeof(MyBox)) == sizeof(MyBox))
		{
			num++;
			if (!strcmp(MyBox.userid, curuser.userid))
			{
				MyOffset = j;
				break;
			}
			memset(&MyBox, 0, sizeof(MyBox));
			j++;
		}
		close(fd);
	}
	if (MyOffset == -1)
		MyOffset = j;

	/* 若離開時, userid 不為 '\0', 表示使用者有投入票箱的動作發生 */
	MyBox.userid[0] = '\0';
	/* 數出您已投了幾票 */
	for (j = 1, MyTickets = 0; j != 0; j <<= 1)
	{
		if (MyBox.vbits & j)
			MyTickets++;
	}

	/* check permission for voting */
	if (curuser.userlevel < vinfo->userlevel
	    || strncmp(uinfo.from, vinfo->allow_ip, strlen(vinfo->allow_ip))
	    || curuser.ident < vinfo->ident
	    || curuser.numlogins < vinfo->numlogins
	    || curuser.numposts < vinfo->numposts
	    || (vinfo->firstlogin && curuser.firstlogin > vinfo->firstlogin))
	{
		showmsg("抱歉, 此次投票活動有限制對象, 您無法參加!");
		return C_FULL;
	}

	/* 參加投票前, 顯示此次投票說明 */
	vcmd_desc(ent, vinfo, direct);

	TheTickets = vinfo->tickets;
	strcpy(TheTitle, vinfo->title);
	setvotefile2(tmpdir, direct, vinfo->filename, "/.CAND");

	cursor_menu(4, 0, tmpdir, cand_comms, sizeof(CAND), &ca_ccur,
		    cand_title, NULL /* cm_btitle */ , cand_entry, read_get, read_max,
		    NULL, 1, TRUE);

	/* 我投過票囉! */
	if (MyBox.userid[0])
	{
		/* 寫入票箱 */
		setdotfile(genbuf, tmpdir, "/box");
		if (num == 0)
			append_record(genbuf, &MyBox, sizeof(MyBox));
		else
			substitute_record(genbuf, &MyBox, sizeof(MyBox), MyOffset);
	}

	curbe->voting = FALSE;

	return C_LOAD;
}


static int count_box(char *path, VOTE *vinfo)
{
	FILE *fp;
	CAND cand;
	char fn_result[PATHLEN];
	int fd, i, num[32], n_users = 0, n_tickets = 0;
	unsigned long j;


	memset(num, 0, sizeof(num));
	/* 自票箱中數各得票數 */
	sprintf(genbuf, "%s/box", path);
	if ((fd = open(genbuf, O_RDONLY)) > 0)
	{
		while (read(fd, &MyBox, sizeof(MyBox)) == sizeof(MyBox))
		{
			n_users++;

			for (j = 1, i = 0; j != 0; j <<= 1, i++)
			{
				if (MyBox.vbits & j)
				{
					num[i] += 1;
					n_tickets += 1;
				}
			}
		}
		close(fd);
	}

	sprintf(genbuf, "%s/.CAND", path);
	if ((fd = open(genbuf, O_RDONLY)) < 0)
		return -1;

	sprintf(fn_result, "%s/result", path);
	if ((fp = fopen(fn_result, "w")) == NULL)
	{
		close(fd);
		return -1;
	}

	fprintf(fp, "[1;33;44m %-26.26s [1;37m%12s %10s - %10s %12s [m\n",
		"選舉名稱", "舉辦人", "投票開始", "開票時間", "每人可投票數");
	fprintf(fp, " %-26.26s %12s %10s - %10s %12d\n",
		vinfo->title, vinfo->owner,
		Vtime(&(vinfo->start_time)),
		Vtime(&(vinfo->end_time)),
		vinfo->tickets);

	fprintf(fp, "[7m 投票人限制：                 %15s %4s %6s %6s %12s[m\n",
		"上站來源", "等級", "上站數", "張貼數", "註冊時間");
	fprintf(fp, "                              %15s %4d %6d %6d %12s\n",
		*(vinfo->allow_ip) ? vinfo->allow_ip : "不限",
		vinfo->userlevel, vinfo->numlogins, vinfo->numposts,
		(vinfo->firstlogin) ? Vtime(&(vinfo->firstlogin)) : "不限");

	fprintf(fp, "[1;37;42m      %4s  %6s    %-55s [m\n",
		"編號", "票數", "名稱");
	/* 列印投票數結果 */
	for (i = 0; read(fd, &cand, sizeof(cand)) == sizeof(cand); i++)
		fprintf(fp, "      %4d：%6d    %s\n", i + 1, num[i], cand.item);

	fprintf(fp, "    總票數：%6d\n", n_tickets);
	fprintf(fp, "    總人數：%6d\n", n_users);

	close(fd);
	fclose(fp);
	chmod(fn_result, 0644);

	return 0;
}


static int vcmd_result(int ent, VOTE *vinfo, char *direct)
{
	char fn_result[PATHLEN], fname[PATHLEN];
	FILE *fpr, *fpw;
	struct stat st;


	/* 板主可以偷瞄投票結果 */
	if (!hasBMPerm && time(0) < vinfo->end_time)
	{
		showmsg("還沒到開票日喔!! 再等一下吧!");
		return C_FULL;
	}

	setvotefile2(fn_result, direct, vinfo->filename, "/result");
	if (!(stat(fn_result, &st) == 0 && st.st_size > 0
	    && st.st_mtime >= vinfo->end_time))
	{
		/* 統計票箱 */
		setdotfile(fname, direct, vinfo->filename);
		count_box(fname, vinfo);

		/* 合併意見表到選舉結果 */

		setvotefile2(fname, direct, vinfo->filename, "/mess");
		if ((fpr = fopen(fname, "r")) != NULL)
		{
			if ((fpw = fopen(fn_result, "a")) != NULL)
			{
				fprintf(fpw, "\n[7m 以下是網友們的意見                                                           [m\n\n");
				while (fgets(genbuf, sizeof(genbuf), fpr))
					fputs(genbuf, fpw);
				fclose(fpw);
			}
			fclose(fpr);
		}
	}
	pmore(fn_result, TRUE);

	return C_FULL;
}


static int vcmd_add(int ent, VOTE *vinfo, char *direct)
{
	VOTE vh_new;
	char path[PATHLEN], *p;

	if (!hasBMPerm)
		return C_NONE;

	getdata(b_line, 0, "確定嗎(y/n)? [n]: ", genbuf, 2, ECHONOSP | XLCASE);
	if (genbuf[0] != 'y')
		return C_FOOT;

	memset(&vh_new, 0, sizeof(vh_new));

	strcpy(vh_new.owner, curuser.userid);

	/* 建立選舉目錄 */
	strcpy(path, direct);
	p = strrchr(path, '/') + 1;
	do
	{
		sprintf(p, "V.%ld.A", time(0));
	}
	while (mkdir(path, 0700) != 0);
	strcpy(vh_new.filename, p);

	if (set_vote(path, &vh_new) == -1)
	{
		rmdir(path);
		return C_FULL;
	}

	append_record(direct, &vh_new, sizeof(vh_new));

	set_brdt_vote_mtime(CurBList->filename);
	curbe->voting = TRUE;

	/* 自動進入該選舉之選單: bug? */
	vcmd_enter(ent + 1, &vh_new, direct);
	return C_INIT;
}


static int vcmd_info(int ent, VOTE *vinfo, char *direct)
{
	show_info ^= 1;
	return C_FULL;
}


static int vcmd_help(int ent, VOTE *vinfo, char *direct)
{
	pmore("doc/VOTE_HELP", TRUE);
	return C_FULL;
}


struct one_key vote_comms[] =
{
	{'a', vcmd_add},
	{'h', vcmd_help},
	{'r', vcmd_enter},
	{'d', vcmd_delete},
	{'E', vcmd_edit},
	{'o', vcmd_result},
	{'i', vcmd_info},
	{'c', vcmd_desc},
	{0, NULL}
};


int v_board()
{
	char tmpdir[PATHLEN];
	int v_ccur = 0;
	extern int multi_logins;

#ifdef GUEST
	if (!strcmp(curuser.userid, GUEST))
		return C_NONE;
#endif

	/* multi-login */
	if (multi_logins > 1)
	{
		clear();
		outs(_msg_vote_1);
		pressreturn();
		return C_FULL;
	}

	setvotefile(tmpdir, CurBList->filename, NULL);

	/* 建立看板投票目錄 */
	mkdir(tmpdir, 0755);
	setvotefile(tmpdir, CurBList->filename, VOTE_REC);

	cursor_menu(4, 0, tmpdir, vote_comms, sizeof(VOTE), &v_ccur,
		    vote_title, NULL /* vote_btitle */ , vote_entry, read_get,
		    read_max, NULL, 1, TRUE);

	return C_LOAD;
}
#endif
