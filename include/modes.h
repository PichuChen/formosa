
#ifndef _BBS_MODES_H
#define _BBS_MODES_H

/* Lots o' modes! */	/* see mode in struct user_info in bbs.h */

enum modes {	
	MMENU, /* "�D���" */
	XMENU, /* "�u����" */
/*
 GMENU, "�T�ֳ�"
 */
	ADMIN, /* "�޲z��" */
	BOARDS_MENU, /* "�ݪO���" */
	CLASS_MENU, /* "�������" */
	MAIL, /* "�H����" */
	READING, /* "Ū�G�i" */
	POSTING, /* "�K�G�i" */
	MODIFY, /* "�ק�峹" */
	RMAIL, /* "Ū�H" */
/*
 READNEW, "Ū�s�H"
 */
	SMAIL, /* "�H�H" */
	TMENU, /* "�͸ܿ��" */
	TALK, /* "���" */
	PAGE, /* "�I��a" */
	LUSERS, /* "�d�u�W�H" */
	LFRIENDS, /* "�ݦѪB��" */

	CHATROOM, /* "������ѫ�" */
	CHATROOM2, /* "���߯���" for nsysubbs */	
#if 0	
	IRCCHAT, /* "�ꤺ��Ѽs��" */
	LOCALIRC, /* "�󯸲�Ѽs��" */
#endif	
	SENDMSG, /* "�u�W�e�T��" */
/*
	ULDL, "����"
*/	
	QUERY, /* "�d�߬Y�H" */
	SELECT, /* "��ݪO" */
	EDITSIG, /* "�sñ�W��" */
	EDITPLAN, /* "�s�W����" */
	OVERRIDE, /* "�s�n�ͦW��" */
	BLACKLIST, /* "�s�a�ͦW��" */
	LOGIN, /* "ñ�줤" */

	LAUSERS, /* "�d�����H" */
/*
	MONITOR, "�ʬݤ�"
*/	
	CLIENT, /* "�D�q���\\����" */
	WEBBBS, /* "Web-BBS" */
/*
   NEW, "�s�ϥΪ̵��U"
 */
	VOTING, /* "�벼��" */
	EDITBMWEL, /* "�s�i�O�e��" */
	UNDEFINE /* "���w�q" */
};


#endif	/*_BBS_MODES_H */
