#define MAX_KEYWORD_LEN 12
#define MAX_PARAMETER   80
/*#define KEYWORD_DELIMITER       " \t\r\n"*/

/********************* command protocol number list *********************/
#define HELLO           10              /* ���� Client �ϥΪ̬O�_���w�� */
#define VERCHK          11              /* ���� Client �{������ */
#define _BBSNAME        12              /* ���o BBS ���W */
#define BBSINFO         13              /* ���o�@�� BBS ���x��T */
#define _ANNOUNCE       15              /* ���o���i�ƶ� */
#define CHKANNOUNCE		16				/* ���o���i�̫�ק��� */
#define LOGINNUM		17				/* ���o�{�b�Ҧ����u�Wlog */
#define KILLPID			18				/* �屼�ۤv�h�l��login */
#define SENDHELP        19              /* ���o�D�U���e */

#define USERLOG         20              /* ñ�J�t��   */
#define USERNEW         21              /* ���U�s�b�� */
#define ALOWNEW         22              /* ���լO�_�i���U�s�b�� */
#define USERCHK         23              /* ���ըϥΪ̱b���O�_�s�b */
#define CERTILOG		24				/* �Hcertification�覡login */
#define _QUIT           29              /* ���} */

#define MAILNUM         30              /* ���o�p�H�H���`�� */
#define MAILHEAD        31              /* ���o�H����Y */
#define MAILGET         32              /* ���o�H�󤺮e */
#define MAILPUT         33              /* �e�H�󵹬Y��User */
#define MAILKILL        34              /* �R���@�ʫH�� */
#define MAILGROUP       35              /* �H�e�H�󵹤@�s�H */
#define MAILNEW 		36				/* �߬d�s�H */
#define MAILUKILL       37              /* �����R���H�� */
#define MAILMAIL        38              /* ��H�H�� */
#define FORWARD			39				/* �۰���H�H��*/

#define LIST            40              /* �C�X�Ҧ��G�i���� */
#define BOARD           41              /* ��ܤu�@���G�i��W�� */
#define _ZAP            42              /* �����ΤޤJ�G�i�� */
#define BRDWELCHK		44				/* �i���e���̫�ק��� */
#define BRDWELGET       45              /* ���o�i���e�� */
#define BRDWELPUT       46              /* �ק�i���e�� */
#define BRDWELKILL      47              /* �R���i���e�� */

#define POSTNUM         50              /* ���o�ӧG�i�椺�峹�`�� */
#define POSTHEAD        51              /* ���o�峹���Y */
#define POSTGET         52              /* ���o�峹���e */
#define POSTPUT         53              /* �K�G�i */
#define POSTKILL        54              /* �R���@�ʧG�i */
#define POSTMAIL        55              /* ��H�@�ʧG�i */
#define POSTTRE         56              /* ��K�ܺ�ذ� */
#define POSTUKILL       57              /* �����R���G�i */
#define POSTETITLE      58              /* �ק���D */
#define POSTEDIT        59              /* �ק�G�i */
#define POSTMPUT        49              /* �K�G�i�ܦh�ӧG�i�� */
#define POSTIMP			48				/* �аO�����n�G�i */

#define PLANGET         60              /* ���o�p���ɤ��e */
#define PLANPUT         61              /* �ק�p���� */
#define PLANKILL        62              /* �R���p���� */
#define SIGNGET         63              /* ���oñ�W�ɤ��e */
#define SIGNPUT         64              /* �ק�ñ�W�� */
#define SIGNKILL        65              /* �R��ñ�W�� */
#define CHGPASSWD       66              /* �ק�K�X */
#define USERGET 		67				/* ���o�ϥΪ̰򥻸�� */
#define CHGNAME         68              /* �ק�ʦW */
#define CHGEMAIL        69              /* �ק�E-Mail */

#define FILEPUT			70				/* �e�W�@���ɮ� */
#define FILEHEAD		71				/* ���o�ɮװϼ��D */
#define FILENUM			72				/* ���o�ɮװϼƥ� */
#define FILEGET			73				/* ���o�ɮפ��e */
#define FILEKILL		74				/* �R���ɮ� */

#define ALLMESG			79				/* ���o�Ҧ��u�W�T�� */
#define SENDMESG		80				/* �e�T�����O�H */
#define LISTUSER        81              /* �C�X�u�W�ϥΪ� */
#define _PAGE           82              /* ������ܭn�D���� */
#define _QUERY          83              /* �d�ߨϥΪ̸�� */
#define TALKTO          84              /* �o�X��ܭn�D */
#define TALKSTOP        85              /* ������ */
#define TALKREP         86              /* �^����ܭn�D */
#define ISAY            87              /* ��ܤ��e */
#define IKEY            88              /* ��ܫ��� */
#define LISTFUSER       89              /* �C�X�u�W�ͤH */

#define FRIENDGET       90              /* ���o�n�ͦW�� */
#define FRIENDPUT       91              /* �ק�n�ͦW�� */

#define CHAT            95              /* �i�J Chat room */
#define CHATSAY         96              /* ���e */
#define CHATSTOP        97              /* ���} Chat room */

#define MAKEDIR			100				/* �إߺ�ذϥؿ�*/

#define TERMOUT			110  			/* Run Slave Terminal BBS */


/******************** respond protocol number list ********************/
#define VER_OK                  611             /* �������T */
#define VER_GETNEW              612             /* �ثe�w���s����, ��ĳ�ϥθ��s���� */
#define BBSNAME_IS              613             /* (�^��BBS ���W) */
#define	ANN_TIME				614				/* �񯸤��i�̫�ק��� */

#define USERID_NOT_EXIST        621             /* �ϥΪ̱b�����s�b */
#define USERID_EXIST            622             /* �ϥΪ̱b���w�s�b */

#define MAIL_NUM_IS             631             /* (�Ǧ^�ʥ�ƥ�) */
#define HAVE_NEW_MAIL			632				/* ���s�H!! */

#define POST_NUM_IS				641				/* (�Ǧ^�G�i�ƥ�) */

#define NOT_SAY_HELLO           711             /* �|�����۩I!! */
#define NOT_WELCOME             712             /* �藍�_!!�����w�� */
#define NOT_ENTER               713             /* �ϥΪ̩|���E�J */
#define VER_NOT                 714             /* ��������!! �Шϥθ��s���� */
#define NO_ANNOUNCE             716             /* �L���i�ƶ� */

#define NEWUSER_FAIL            721             /* ���U���� */
#define NOT_ALLOW_NEW           722             /* �����\\�s�b�����U */
#define NO_MORE_USER			723				/* �ϥΪ̤H�ƹF�W�� */
#define PASSWORD_ERROR          724             /* �K�X���~ */
#define PASSWORD_3_ERROR        725             /* �K�X���~�T��,�j�����u */

#define MAIL_NOT_EXIST          731             /* ���ʫH�󤣦s�b */
#define MAIL_NOT_ALLOW          739             /* �����\\�H�X�H�� */


#define NO_ANY_BOARD            741             /* �S����G�i�� */
#define BOARD_NOT_EXIST         742             /* �������s�b */
#define BOARD_NOT_ALLOW         743             /* �����\\��ܦ��G�i�� */
#define NO_BOARD_WELCOME        745             /* �L�i���e�� */

#define NOT_SELECT_BOARD        751             /* �|����ܧG�i�� */
#define POST_NOT_EXIST          752             /* ���ʧG�i���s�b */
#define NOT_POST				753				/* �D�@��G�i */
#define POST_NOT_ALLOW          759             /* �����\\�i�K�G�i */

#define NO_PLAN                 761             /* �L�p���� */
#define NO_SIGN                 763             /* �Lñ�W�� */

#define NOT_ALLOW_PAGE          780             /* ��西�B�󤣭㥴�Z�����A */
#define NOT_ALLOW_TALK          781             /* ��西�B�󤣯౵���͸ܪ����A */
#define USER_NOT_ONLINE         782             /* ���H���b�u�W */
#define NOT_ALLOW_REQ           783             /* ��������ܭn�D */
#define PID_NOT_EXIST			784				/* ��pid���b�u�W */

#define NO_FRIEND               785             /* �L�ͤH�W�� */

#define UNKNOW_CMD              790             /* �S���R�O */
#define SYNTAX_ERROR            791             /* �y�k���~ */
#define USER_NOT_LOGIN          792             /* �ϥΪ̩|��ñ�J */
#define WORK_ERROR              793             /* �u�@���� */
#define KILL_NOT_ALLOW          794             /* �����\\�R�� */
#define LEVEL_TOO_LOW           795             /* �ϥΪ̵��ŤӧC */

#define OK_CMD                  800             /* OK!! */

#define TALK_REQUEST            900             /* ��ܭn�D */
#define SHE_SAY                 901             /* ��ܤ��e */
#define SHE_KEY                 902             /* ��ܫ��� */
#define TALK_EXIT               903             /* ��ܪ����} */
#define TALK_PORT               904				/* �^�����port */
#define MSG_REQUEST				905				/* ���T���L�� */
#define	TERM_PORT				906				/* Slave Term BBS waiting Port*/


#define CHAT_MSG                910             /* Chat room ���e */
#define CHAT_CHG_NICKNAME       911             /* �ק� Chat room nick name */
#define CHAT_EXIT               912             /* ���} Chat room */
#define CHAT_CLS                913             /* �M���ù� */

#define PAGER_CHANGE            920             /* �ק� Pager */

#define FILE_NOT_EXIST			950				/* �ɮװϤ��s�b */
#define UPLOAD_NOT_ALLOW		951				/* �ɮפW�Ǥ����\ */
#define FILE_IN_SITE			952				/* �ɮצb���� */
#define FILE_OUT_SITE			953				/* �ɮצb���~ */
#define ORI_FILENAME			954				/* ��l�ɦW */
#define OUT_FILE				955				/* �����ɸ�� */
#define END_FILE				956				/* �W�ǧ��������T�� */

#define NOT_SELECT_TREA			1000			/* �S���b��ذϤ�*/
