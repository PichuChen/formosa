/*******************************************************************
 * NSYSU BBS <--> News Server �H���y�{��  v1.0
 *
 * �\��G
 *     1. �@�� bbs board ��h�� news groups ���ǫH��.
 *     2. �@�� news group ��h�� bbs boards ���ǫH��.
 *
 * Coder: �����    lmj@cc.nsysu.edu.tw
 *                  (wind.bbs@bbs.nsysu.edu.tw)
 *
 *******************************************************************/

#include "bbs-news.h"


/*******************************************************************
 * �ɤ��@���ܼư�
 *******************************************************************/
struct stat st;
char buf[4096];
char debug = 0;
time_t now, last_modify;
struct BNConf bnc;
struct BNLink bnl;


/###################################################################
 # �{����
 ###################################################################/



/===================================================================
 = BNCloseAll()
 ===================================================================/
void BNCloseAll()
{
	int fd;
	for(fd = 0; fd < 64; fd++)
		close(fd);
}



/===================================================================
 = BNGetToken �ھڤ��j�r���A���o�l�r��
 = �Ǧ^�G�U�@�Ӥl�r��
 ===================================================================/
char *BNGetToken(str, dep, sbuf, slen)
char *str, *dep, *sbuf;
int slen;
{
	*sbuf = '\0';
	if(*str && *dep)
	{
		char *pr = str, *pw = sbuf, *pe = sbuf + slen -1;
		while(strchr(dep, *pr))
			pr++;
		if(!(*pr))
			return (char *)NULL;
		for(; *pr && pw < pe; pr++, pw++)
			if(strchr(dep, *pr))
			{
				*pw = '\0';
				return pr;
			}
			else
				*pw = *pr;
		*pw = '\0';
		return pr;
	}
	return (char *)NULL;
}




/===================================================================
 = MakeDirList(dir, file) �� dir �ؿ����X�ɮצC��s��� file
 = �Ǧ^�G���X�X���C��
 ===================================================================/
int MakeDirList(dir, file)
char *dir, *file;
{
	DIR *dirp;
	struct dirent *d;
	FILE *fp;
	int cnt = 0;

	if(dir && *dir && (dirp = opendir(dir)))
	{
		if((fp = fopen(file, "w")))
		{
			readdir(dirp);
			readdir(dirp);
			while((d = readdir(dirp)))
				if(d->d_name[0])
				{
					fprintf(fp, "%s\n", d->d_name);
					cnt++;
				}
			fclose(fp);
		}
		closedir(dirp);
	}
	return cnt;
}


/===================================================================
 = BNInitDirs(BBSNEWS_HOME) �T�{�Ҧ��Ӧ����򥻥ؿ�
 ===================================================================/
int BNInitDirs(home)
char *home;
{
	char *dirs[] = {"current","input","output","olog","record",(char *)NULL};
	char i;

	for(i = 0; dirs[i]; i++)
	{
		sprintf(buf, "%s/%s", dirs[i]);
		if(stat(buf, &st) && mkdir(buf, 0755))
			return -1;
		else if(st.st_uid != BBS_UID)
			return -1;
	}
	return 0;
}





/===================================================================
 = BNMain() �D�n�j��
 ===================================================================/
int BNMain()
{
	int fd, cnt = 0;
	off_t cur;

	/* �}�l��Ū�]�w�� */
	if((fd = BNMakeConf()) < 0)
	{
		fprintf(stderr, "Error: �]�w��Ū�����~\n");
		sleep(1800);
		return 0;
	}
	cur = lseek(fd, 0, SEEK_SET);
	while(1)
	{
		if(read(fd, &bnl, sizeof(bnl)) != sizeof(bnl))
			break;
		if((bnl.flag & BNLINK_BOTH) || (bnl.flag & BNLINK_OUTPUT))
		{
			sprintf(buf, "%s/output/%s", BBSNEWS_HOME, bnl.board);
			if(!stat(buf, &st))
				BNToNews(&bnl);
		}
		if(bnl.flag & BNLINK_BOTH || bnl.flag & BNLINK_INPUT)
			BNToBBS(&bnl);
		cnt++;
	}
	close(fd);
	return (cnt ? 0 : -1);
}


/===================================================================
 = Main
 ===================================================================/
int main(argc, argv)
int argc;
char *argv[];
{
	int fd, sock;

	if(argc < 3)
	{
		printf("Usage: %s DefaultNewsServer TimerSeconds [debug]\n", argv[0]);
		exit(1);
	}
#if defined(CHROOT_BBS)
	if(chroot(HOMEBBS) || chdir("/"))
	{
		printf("Can't chroot to BBS Home\n");
		exit(1);
	}
#else
	if(chdir(HOMEBBS))
	{
		printf("BBS Home DIR is not exist!\n");
		exit(1);
	}
#endif
	if(stat(BBSNEWS_HOME, &st) || st.st_uid != BBS_UID)
	{
		printf("News Home DIR is not exist or owner is not bbs\n");
		exit(1);
	}
	if(setgid(BBS_GID) || setuid(BBS_UID))
	{
		printf("Can't setuid to bbs, please check user[bbs] & group[bbs] is exist\n");
		exit(1);
	}
	if(BNInitDirs(BBSNEWS_HOME))
	{
		printf("Can't init dirs, please check path and onwer is bbs\n");
		exit(1);
	}

	if(argc > 1 && !strcmp(argv[1], "debug"))
		debug++;

	if(fork())	/* �I������ */
		exit(0);

	/* ��l�� */
	now = time(0);
	sprintf(buf, "%s/%s", BBSNEWS_HOME, BBSNEWS_PID);
	if(fd = open(buf, O_RDWR|O_CREAT, 0644) > 0)
	{
		pid_t pid;
		memset(buf, 0, sizeof(buf));
		if(read(fd, buf, sizeof(buf)) > 0)
		{
			pid = atoi(buf);
			if(!kill(pid, 0))
			{
				printf("�w�g�s�b�@�� bbs-news process PID=[%d]\n", pid);
				exit(2);
			}
		}
		lseek(fd, 0, SEEK_SET);
		ftruncate(fd, 0);
		sprintf(buf, "%-d\n", getpid();
		write(fd, buf, strlen(buf));
		close(fd);
	}
	BNCloseAll();
	sprintf(buf, "%s/%s", BBSNEWS_HOME, BBSNEWS_LOG);
	if((fd = open(buf, O_CREAT|O_APPEND, 0644) >= 0)
	{
		if(fd != 2)
		{	/* �� log file �令�зǿ��~��X */
			dup2(fd, 2);
			close(fd);
		}
		fprintf(stderr, "\n\nStarting: PID=[%d] %s", getpid(),ctime(&now));
	}
	else
		exit(2);

	/* �]�w BNConf Struct */
	memset(bnc, 0, sizeof(bnc));
	strncpy(bnc.host, MYHOSTNAME, sizeof(bnc.host));
	strncpy(bnc.ip, MYHOSTIP, sizeof(bnc.ip));
	strncpy(bnc.name, BBSTITLE, sizeof(bnc.name));
	strncpy(bnc.server, argv[1], sizeof(bnc.server));
	bnc.timer = atoi(argv[2]);
	last_modify = time(0);
	/* ��l�Ƨ��� */

	/* �i�J�D�j�� */
	for(;;)
		if(BNMain())
			break;
		else
			sleep(bnc.timer);
	BNCloseAll();
	exit(3);
}
