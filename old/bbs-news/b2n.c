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


/###################################################################
 # �{����
 ###################################################################/



/===================================================================
 = BNToNews() �o�H�� News
 ===================================================================/
int BNToNews(ln)
struct BNLink *ln;
{
	char ofile[80], path[80];
	int fd;



	sprintf(ofile, "%s/current/output", BBSNEWS_HOME);
	sprintf(ofile, "%s/output/", BBSNEWS_HOME);
	if(MakeDirList(

	sprintf(ofile, "%s/current/link", BBSNEWS_HOME);
	if(fd = open(ofile, O_RDONLY) > 0)
	{	/* �e�@���u�@�Q���_�A���B�z���� */
		char obuf[80];
		memset(obuf, 0, sizeof(obuf));
		if(read(fd, obuf, sizeof(obuf)) > 0)
		{
			char *p;
			if(p = strchr(obuf, '#'))
			{
				int fd2;
				FILE *fp;
				*p = '\0';
				sprintf(buf, "%s/output/%s", BBSNEWS_HOME, obuf);
	unlink(ofile);
	sprintf(buf, "%s/output/%s", BBSNEWS_HOME, ln->board);
	if(rename(genbuf, ofile))
	{
		fprintf(stderr, "[x] rename %s -> %s\n", genbuf, ofile);
		return -1;
	}
}

