
#ifndef _BBS_CSBBS_H_
#define _BBS_CSBBS_H_

#include "bbs.h"
#include "protocol.h"
#include "libproto.h"
#include "conf.h"
#include "perm.h"

#include "csbbsproto.h"


/*************************************************************************
 *	�����Өt�Ϊ��w�q
 *************************************************************************/
#define MAX_MULTI_BOARDS 	10		/* �@���̦h�i�H�P�ɶK���O�� */

#define CSBBS_SERVER_PORT       7716

#define CLIENT_READ_TIMEOUT     600  /* 10 mins */
#define CLIENT_WRITE_TIMEOUT    300   /* 5 mins */

extern USEREC curuser;
extern USER_INFO uinfo;
extern USER_INFO *cutmp;

extern char    genbuf[];

extern char *GetToken(char *,char *,int);
extern char *Get_para_string(int);

extern char ufile_overrides[];

extern struct array friend_cache;

#endif /* _BBS_CSBBS_H_ */
