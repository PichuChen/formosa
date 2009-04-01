
#include "bbs.h"
#include "csbbs.h"

struct PROTOCOL
{
	int num;
	char *keyword;
};

struct RESPOND_PROTOCOL
{
	int num;
	char *explain;
};


struct PROTOCOL fp[] =
{
	{HELLO, "HELLO"},
	{VERCHK, "VERCHK"},
	{LOGINNUM, "LOGINNUM"},
	{KILLPID, "KILLPID"},
	{_BBSNAME, "BBSNAME"},
	{BBSINFO, "BBSINFO"},
	{_ANNOUNCE, "ANNOUNCE"},
	{CHKANNOUNCE, "CHKANNOUNCE"},
	{SENDHELP, "SENDHELP"},
	{USERLOG, "USERLOG"},
	{CERTILOG, "CERTILOG"},
	{USERNEW, "USERNEW"},
	{ALOWNEW, "ALOWNEW"},
	{USERCHK, "USERCHK"},
	{_QUIT, "QUIT"},
	{MAILNUM, "MAILNUM"},
	{MAILHEAD, "MAILHEAD"},
	{MAILGET, "MAILGET"},
	{MAILPUT, "MAILPUT"},
	{MAILKILL, "MAILKILL"},
	{MAILGROUP, "MAILGROUP"},
	{MAILNEW, "MAILNEW"},
	{MAILUKILL, "MAILUKILL"},
	{MAILMAIL, "MAILMAIL"},
	{FORWARD, "FORWARD"},
	{LIST, "LIST"},
	{_ZAP, "ZAP"},
	{BRDWELCHK, "BRDWELCHK"},
	{BRDWELGET, "BRDWELGET"},
	{BRDWELPUT, "BRDWELPUT"},
	{BRDWELKILL, "BRDWELKILL"},
	{POSTIMP, "POSTIMP"},
	{POSTNUM, "POSTNUM"},
	{POSTHEAD, "POSTHEAD"},
	{POSTGET, "POSTGET"},
	{POSTPUT, "POSTPUT"},
	{POSTKILL, "POSTKILL"},
	{POSTMAIL, "POSTMAIL"},
	{POSTTRE, "POSTTRE"},
	{POSTUKILL, "POSTUKILL"},
	{POSTETITLE, "POSTETITLE"},
	{POSTEDIT, "POSTEDIT"},
	{POSTMPUT, "POSTMPUT"},
	{PLANGET, "PLANGET"},
	{PLANPUT, "PLANPUT"},
	{PLANKILL, "PLANKILL"},
	{SIGNGET, "SIGNGET"},
	{SIGNPUT, "SIGNPUT"},
	{SIGNKILL, "SIGNKILL"},
	{CHGPASSWD, "CHGPASSWD"},
	{CHGNAME, "CHGNAME"},
	{CHGEMAIL, "CHGEMAIL"},
	{USERGET, "USERGET"},
	{LISTUSER, "LISTUSER"},
	{_PAGE, "PAGE"},
	{_QUERY, "QUERY"},
	{TALKTO, "TALKTO"},
	{TALKSTOP, "TALKSTOP"},
	{TALKREP, "TALKREP"},
	{ISAY, "ISAY"},
	{IKEY, "IKEY"},
	{LISTFUSER, "LISTFUSER"},
	{SENDMESG, "SENDMESG"},
	{ALLMESG, "ALLMESG"},
	{FRIENDGET, "FRIENDGET"},
	{FRIENDPUT, "FRIENDPUT"},
	{CHAT, "CHAT"},
	{CHATSAY, "CHATSAY"},
	{CHATSTOP, "CHATSTOP"},
	{FILEPUT, "FILEPUT"},
	{FILEHEAD, "FILEHEAD"},
	{FILENUM, "FILENUM"},
	{FILEGET, "FILEGET"},
	{FILEKILL, "FILEKILL"},
	{MAKEDIR, "MAKEDIR"},
	{TERMOUT, "TERMOUT"}};


struct RESPOND_PROTOCOL fp_err[] =
{
	{VER_OK, "�������T"},
	{VER_GETNEW, "�ثe�w���s����, ��ĳ�ϥθ��s����"},
	{USERID_NOT_EXIST, "�ϥΪ̱b�����s�b"},
	{USERID_EXIST, "�ϥΪ̱b���w�s�b"},
	{HAVE_NEW_MAIL, "���s�H!!"},
	{NOT_SAY_HELLO, "�|�����۩I"},
	{NOT_WELCOME, "�藍�_!!�����w��"},
	{NOT_ENTER, "�ϥΪ̩|���E�J"},
	{VER_NOT, "��������!! �Шϥθ��s����"},
	{NO_ANNOUNCE, "�L���i�ƶ�"},
	{NEWUSER_FAIL, "���U����"},
	{NOT_ALLOW_NEW, "�����\\�s�b�����U"},
	{NO_MORE_USER, "�ϥΪ̤H�ƹF�W��"},
	{PASSWORD_ERROR, "�K�X���~"},
	{PASSWORD_3_ERROR, "�K�X���~�T��,�j�����u"},
	{MAIL_NOT_EXIST, "���ʫH�󤣦s�b"},
	{MAIL_NOT_ALLOW, "�����\\�H�X�H��"},
	{NO_ANY_BOARD, "�S����G�i��"},
	{BOARD_NOT_EXIST, "�������s�b"},
	{BOARD_NOT_ALLOW, "�����\\��ܦ��G�i��"},
	{NO_BOARD_WELCOME, "�L�i���e��"},
	{NOT_SELECT_BOARD, "�|����ܧG�i��"},
	{POST_NOT_EXIST, "���ʧG�i���s�b"},
	{NOT_POST, "�D�iŪ���G�i"},
	{POST_NOT_ALLOW, "�����\\�i�K�G�i"},
	{NO_PLAN, "�L�p����"},
	{NO_SIGN, "�Lñ�W��"},
	{NOT_ALLOW_PAGE, "��西�B�󤣭㥴�Z�����A"},
	{NOT_ALLOW_TALK, "��西�B�󤣯౵���͸ܪ����A"},
	{USER_NOT_ONLINE, "���H���b�u�W"},
	{NOT_ALLOW_REQ, "��������ܭn�D"},
	{PID_NOT_EXIST, "��pid���b�u�W"},
	{NO_FRIEND, "�L�ͤH�W��"},
	{UNKNOW_CMD, "�S�����R�O !!!"},
	{SYNTAX_ERROR, "�y�k���~"},
	{USER_NOT_LOGIN, "�ϥΪ̩|��ñ�J"},
	{WORK_ERROR, "�u�@����"},
	{KILL_NOT_ALLOW, "�����\\�R��"},
	{LEVEL_TOO_LOW, "�ϥΪ̵��ŤӧC"},
	{OK_CMD, "OK!!"},
	{TALK_EXIT, "��ܪ����}"},
	{CHAT_EXIT, "���} Chat room"},
	{CHAT_CLS, "�M���ù�"},
	{FILE_NOT_EXIST, "�ɮװϤ��s�b"},
	{UPLOAD_NOT_ALLOW, "�ɮפW�Ǥ����\""},
	{FILE_IN_SITE, "�ɮצb����"},
	{FILE_OUT_SITE, "�ɮצb���~"},
	{NOT_SELECT_TREA, "�|����ܺ�ذ�"}};


int
GetKeywordNo(keyword)
char *keyword;
{
	int i;

	strupr(keyword);	/* unix don't have strupr, I program it */
	for (i = 0; i < (sizeof(fp) / sizeof(struct PROTOCOL)); i++)
	{
		if (!strcmp(keyword, fp[i].keyword))
			return fp[i].num;
	}
	return -1;
}

RespondProtocol(respno)
int respno;
{
	int i;

	for (i = 0; i < (sizeof(fp_err) / sizeof(struct RESPOND_PROTOCOL)); i++)
	{
		if (fp_err[i].num == respno)
			inet_printf("%d\t%s \r\n", respno, fp_err[i].explain);
	}
}
