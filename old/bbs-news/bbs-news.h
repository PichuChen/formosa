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

#include "bbs.h"

/*******************************************************************
 * �ŧi�P�w�q
 *******************************************************************/
#define BBSNEWS_HOME	"news"
#define BBSNEWS_CONF	"bbs-news.conf"
#define BBSNEWS_PIDFILE	"bbs-news.pid"
#define BBSNEWS_LOG		"bbs-news.log"
#define BBSNEWS_BIN		"bin/bbs-news"

struct BNLink {
	char board[BNAMELEN+4];
	char group[80];
	long id;
	char flag;
	char server[80];
};

struct BNConf {
	char host[80]; 
	char ip[16]; 
	char name[80];
	char server[80]; 
	time_t timer;
};

struct BNLinkList {
	struct BNLink bnl;
	struct BNLink *next;
};

/* These Flags are for BNLink.flag */
#define BNLINK_BOTH		0
#define BNLINK_INPUT	1
#define BNLINK_OUTPUT	2


