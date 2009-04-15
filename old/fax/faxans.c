
#include "faxans.h"
#include "serialno.h"

#define myProtocol 10


int
do_faxans_title(title, option)
char title[];
int option;
{
	if (title[0])
	{
		printxy(2, 0, _msg_article_19, title);
		if (igetkey() == 'n')
			title[0] = '\0';
	}
	if (title[0] == '\0' && option == 2)	/* Seraph */
	{
		if (!getdata(9, 0, _msg_faxans_2, title, TTLEN, DOECHO, NULL))
			return -1;
	}
#if 0
	if (title[0] == '\0' && option == 3)	/* Seraph */
	{
		if (!getdata(8, 0, _msg_faxans_3, title, TTLEN, DOECHO, NULL))
			return -1;
	}
#endif

	if (title[0] == '\0')
	{
		if (!getdata(2, 0, _msg_title, title, TTLEN, DOECHO, NULL))
			return -1;
	}
	return 0;
}


int
do_article_tofax(to)		/* Seraph */
char to[];
{
	char phone[8];


	if (!getdata(8, 0, _msg_faxans_5, phone, sizeof(phone), ECHONOSP, NULL))
		return -1;
	else
	{
		strcat(to, phone);
		strcat(to, "@cc.nsysu.edu.tw");
	}
	return 0;
}


#if 0
int
do_article_topage(to)		/* Seraph */
char to[];
{
	char phone[11];


	if (!getdata(7, 0, _msg_faxans_6, phone, sizeof(phone), ECHONOSP, NULL))
		return -1;
	else
	{
		strcat(to, phone);
		strcat(to, "@epager.incubator.nsysu.edu.tw");
	}
	return 0;
}
#endif


int
PrepareFaxAns(fname, to, title, option)
char *fname, *to, *title;
int option;
{
	int save_mmode = in_mail, save_umode = uinfo.mode, result;
	int fp;
	char fnameTmp[PATHLEN];
	char att_1[38];
	char *att_2 = "Content-Type: text/plain; charset=\"us-ascii\"\n";
	char *att_3 = "Content-Disposition: attachment; filename=\"efax.txt\"\n\n";
	char att_4[10];
	char att_5[14];

	if (option == 2)
	{
		if (do_article_tofax(to) == -1)
			return -1;
	}
#if 0
	else if (option == 3)
	{
		if (do_article_topage(to) == -1)
			return -1;
	}
#endif

	if (do_faxans_title(title, option) == -1)
		return -1;

	sprintf(fnameTmp, "tmp/bbs%05d", getpid());
	if (fname)
	{
		outs(_msg_include_ori);
		if (igetkey() != 'n')
			include_ori(fname, fnameTmp);
	}

	update_umode(SMAIL);
	in_mail = TRUE;		/* lthuang */
#if 0
	if (option != 3)
#endif
	sprintf(att_1, "--=====================_892784644==_\n");
	sprintf(att_4, "ID:%d\n", curuser.telecom);
	sprintf(att_5, "PASSWORD:1234\n");
	fp = open(fnameTmp, O_APPEND);
	write(fp, att_1, strlen(att_1));
	write(fp, att_2, strlen(att_2));
	close(fp);
	if (vedit(fnameTmp, title, NULL))
		result = -1;
	fp = open(fnameTmp, O_APPEND);
	write(fp, att_1, strlen(att_1));
	write(fp, att_2, strlen(att_2));
	write(fp, att_3, strlen(att_3));
	write(fp, "<BEGIN>\n", 8);
	write(fp, att_4, strlen(att_4));
	write(fp, att_5, strlen(att_5));
	write(fp, "<END>\n", 6);
	write(fp, att_1, strlen(att_1));
	write(fp, att_2, strlen(att_2));
	sprintf(att_1, "--=====================_892784644==_--\n");
	write(fp, att_1, strlen(att_1));
	close(fp);

	if (option == 2 && is_emailaddr(to))
	{
		char fnameNew[PATHLEN] = "\0";

		strcpy(fnameNew, fnameTmp);
		result = SendMail(-1, FALSE, fnameNew, curuser.userid,
					   to, title, 0);
	}
#if 0
	else if (option == 3 && is_emailaddr(to))
		result = SendMail_Internet(-1, NULL, curuser.userid, to, title);
#endif
	else
		result = SendMail(-1, FALSE, fnameTmp, curuser.userid, to, title,
		                  curuser.ident);
	in_mail = save_mmode;
	unlink(fnameTmp);
	update_umode(save_umode);
	return result;
}


/********************************************************
	�����q�H�\��
 ********************************************************/
m_sendfax()			/* email to fax *//* Seraph */
{
	char strTo[STRLEN] = "\0", strTitle[STRLEN] = "\0";
	int result;


	move(3, 0);
	clrtobot();
	outs(_msg_faxans_7);
	strTo[0] = (strTitle[0] = '\0');
/*
	strcat(strTo, "8867");
*/
	result = PrepareFaxAns(NULL, strTo, strTitle, 2);
	in_mail = FALSE;
	move(b_line - 1, 0);
	clrtoeol();
	if (result == -1)
		outs(_msg_faxans_8);
	else
		outs(_msg_faxans_9);

	pressreturn();
	return M_FULL;
}


#if 0
m_callpager()			/* email to pager *//* Seraph */
{
	char strTo[STRLEN] = "\0", strTitle[STRLEN] = "\0";
	int result;


	move(3, 0);
	clrtobot();
	outs(_msg_faxans_10);
	strTo[0] = (strTitle[0] = '\0');
	strcat(strTo, "886");
	result = PrepareFaxAns(NULL, strTo, strTitle, 3);
	in_mail = FALSE;
	move(b_line - 1, 0);
	clrtoeol();
	if (result == -1)
		outs(_msg_faxans_11);
	else
		outs(_msg_faxans_12);

	pressreturn();
	return M_FULL;
}
#endif


m_vmachine()			/* Seraph */
{
	int sockfd;
	char bbsid[IDLEN + 6];
	struct sockaddr_in serv_addr;


	if (haveNo())
	{
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
		serv_addr.sin_port = htons(SERV_TCP_PORT);

		if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			exit(1);
			perror("client:");
		}

		if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		{
			exit(1);
			perror("client:");
		}

		/* send my id */
		strcpy(bbsid, curuser.userid);
		strcat(bbsid, ".bbs\0");
		if (write(sockfd, bbsid, strlen(bbsid) + 1) < 0)
		{
			outs("write to server error\n");
			exit(1);
		}

		readResult(sockfd);
		close(sockfd);
	}
	pressreturn();
	return M_FULL;

}


#if 0
int
haveNo()
{
	FILE *fd;
	char line[MAXLEN_REC], Faxnum[FAXNO_MAXLEN], ID[MAXLEN_BBSID];
	int j, k, h = 0;


	if ((fd = fopen("IDMapNO", "r")) != NULL)
	{
		fseek(fd, 0L, SEEK_SET);
		while (fgets(line, MAXLEN_REC, fd) != NULL)
		{
			for (j = 0; j < strlen(line); j++)
			{
				if (line[j] != ' ')
				{
					ID[j] = line[j];
					if (!strcmp(ID, curuser.userid))
					{
						h = 0;
						for (k = strlen(ID) + 1; k < strlen(line); k++)
						{
							Faxnum[h++] = line[k];
							Faxnum[h] = '\0';
							move(3, 0);
							outs("�P�±z�ϥκ����q�H���s�\\��!");
							outs("\n�P�ɤ]�бz�H���˵��z���ӤH�����ǯu/��������!\n");
							outs("\n�����z�A�z�ҥӽЪ��N���O : ");
							outs(Faxnum);
							outs("\n\n�ӤH�����ǯu�����X:�]�����^����������������]�����^��������������\n");
							outs("�ӤH�������������X:�]�����^����������������]�����^��������������");
						}
						fclose(fd);
						return (0);
					}
				}
				else
				{
					ID[j] = '\0';
					break;
				}
			}
		}
	}
	fclose(fd);
	return (1);
}
#endif


int
haveNo()
{
	if (curuser.telecom)
	{
		move(3, 0);
		prints(_msg_faxans_13, curuser.telecom);
		return 0;
	}
	return 1;
}


readResult(fd)
int fd;
{
	char str1[FAXNO_MAXLEN];
	if (read(fd, str1, FAXNO_MAXLEN) < 0)
	{
		outs(_msg_faxans_14);
		exit(0);
	}
	if (strcmp(str1, "Rerr") == 0)
		outs("\nTry to get number Error\n\n");
	else if (strcmp(str1, "Sorry") == 0)
		outs(_msg_faxans_15);
	else if (strcmp(str1, "Nocon") == 0)
		outs("\nYou are not permitted to connect NTIS server.\n\n");
	else
	{

#if 0
		writeToMap(str1);	/* write map file */
#endif
		curuser.telecom = atoi(str1);	/* lthuang */

		move(3, 0);
		prints(_msg_faxans_16, str1);
	}
}


#if 0
writeToMap(str)
char *str;
{
	int wf;
	char faxno[10], record[20];


	if ((wf = open("IDMapNO", O_APPEND | O_CREAT | O_WRONLY, 0600)) == -1)
	{
		printf("can't open Mapfile to write!\n");
		exit(0);
	}
	else if (lockf(wf, F_LOCK, 0) == 0)
	{
		sprintf(faxno, " %s\n", str);
		strcpy(record, curuser.userid);
		strcat(record, faxno);
		if (write(wf, record, strlen(record)) == -1)
			printf("write error\n");
		lockf(wf, F_ULOCK, 0);
		close(wf);
	}
}


m_fax()				/* v-fax */
{
	int inbox, num, cnt;
	FILEHEADER *fheads;


	in_mail = FALSE;
	cnt = get_num_records(ufile_mail, FH_SIZE);
	fheads = (FILEHEADER *) malloc(FH_SIZE * cnt);
	if (fheads == NULL)
		return -1;
	clear();
	while (strstr(fheads->title, "Fax to Mail Services"))
		num++;
	move(3, 0);
	prints(_msg_faxans_17, num);
	pressreturn();
	return M_FULL;
}


m_answer()			/* v-ans */
{
	int inbox, num, cnt;
	FILEHEADER *fheads;


	in_mail = FALSE;
	cnt = get_num_records(ufile_mail, FH_SIZE);
	fheads = (FILEHEADER *) malloc(FH_SIZE * cnt);
	if (fheads == NULL)
		return -1;

	clear();
	while (strstr(fheads->title, "Voice to Mail Services"))
		num++;
	move(3, 0);
	prints(_msg_faxans_18, num);
	pressreturn();
	return M_FULL;
}
#endif


void
getResult(fd)
int fd;
{
	char Result[myProtocol];


	if ((read(fd, Result, sizeof(Result))) < 0)
	{
		printf("���K�X�o�Ϳ��~(2)!!\n");
		exit(0);
	}

	if (strcmp("error", Result) == 0)
		printf("���K�X�o�Ϳ��~(3)!!\n");
	else if (strcmp("good", Result) == 0)
		printf("���K�X����!!\n");
}


/******* Send ID , password to NT Server for change *********/
int
ChangeNTPass(idno, newpass)
unsigned int idno;
char *newpass;
{
	int NTsockfd;
	struct sockaddr_in NTserv_addr;
	char Message[50];

	bzero((char *) &NTserv_addr, sizeof(NTserv_addr));
	NTserv_addr.sin_family = AF_INET;
	NTserv_addr.sin_addr.s_addr = inet_addr(NTSE_HOST_ADDR);
	NTserv_addr.sin_port = htons(NTSE_TCP_PORT);

	if ((NTsockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		close(NTsockfd);
		return 0;
	}

	if (connect(NTsockfd, (struct sockaddr *) &NTserv_addr, sizeof(NTserv_addr)) < 0)
	{
		close(NTsockfd);
		return 0;
	}

	write(NTsockfd, &idno, sizeof(curuser.telecom) + 1);

	strcat(Message, " ");
	strcat(Message, newpass);


	if (write(NTsockfd, Message, strlen(Message) + 1) < 0)
	{
		close(NTsockfd);
		return 0;
	}
	else
	{
		close(NTsockfd);
		return 1;
	}
}


void
mod_telepass()
{
	int sockfd;
	char oldpass[5], newpass1[5], newpass2[5];
	struct sockaddr_in serv_addr;

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
	serv_addr.sin_port = htons(SERV_TCP_PORT);

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		exit(1);
		perror("client:");
	}

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		exit(1);
		perror("client:");
	}

	if (write(sockfd, (char *) &curuser.telecom, sizeof(curuser.telecom)) < 0)	/* send my id */
	{
		printf("���K�X�o�Ϳ��~!!\n");
		close(sockfd);
		exit(1);
	}

	printf("�п�J�A���±K�X�]�|�X�^: ");
	gets(oldpass);

	if (write(sockfd, oldpass, strlen(oldpass) + 1) < 0)	/* send my id */
	{
		printf("���K�X�o�Ϳ��~!!\n");
		close(sockfd);
		exit(1);
	}

	printf("�п�J�A���s�K�X�]�|�X�^: ");
	gets(newpass1);

	while (strlen(newpass1) != 4)
	{
		printf("�s�K�X�������|�X !!\n");
		printf("�п�J�A���s�K�X�]�|�X�^: ");
		gets(newpass1);
	}

	printf("�A�T�{�@���s�K�X�]�|�X�^: ");
	gets(newpass2);

	if (ChangeNTPass(curuser.telecom, newpass1) != 1)
	{
		printf("���K�X�o�Ϳ��~(NT)!! \n");
		close(sockfd);
		exit(1);
	}

	if (strcmp(newpass1, newpass2) != 0)
	{
		printf("\n�⦸��J���s�K�X���P !\n");
		close(sockfd);
		exit(1);
	}


	if (write(sockfd, newpass1, strlen(newpass1)) < 0)
	{
		printf("���K�X�o�Ϳ��~(1)!! \n");
		close(sockfd);
		exit(1);
	}

	getResult(sockfd);
	close(sockfd);
	exit(1);
}


