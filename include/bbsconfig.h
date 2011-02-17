
#ifndef _BBS_CONFIG_H_
#define _BBS_CONFIG_H_

/*******************************************************************
 *    關於整個系統的定義
 *******************************************************************/
#define BBS_UID             9999        /* BBS user Run Time 系統 uid */
#define BBS_GID             999         /* BBS user Run Time 系統 gid */
#define MAXACTIVE           64         /* 線上容許人數 */
#define MAXBOARD            256
#ifndef HOMEBBS
/* a fallback in case we don't have the config.h */
#define HOMEBBS             "/home/bbs"
#endif

/*******************************************************************
 *    系統組態
 *******************************************************************/
#undef CHROOT_BBS                       /* 是否使用 chroot 以增加系統安全 */
#define LOGINASNEW                      /* 是否允許 new user */
#undef BBSLOG_MAIL                      /* 是否啟用對外送信記錄 */
#undef BBSLOG_IDLEOUT                   /* 是否啟用 IDLE 強制斷線記錄 */
#define BIT8                            /* 是否使用中文化 8 bits 系統*/
#define INCLUDE_DEPTH       3           /* 含括原文時, 保留幾層原文 */
#define TREASURE_DEPTH      10          /* 精華區最大階層深度 */
#define LEAST_IDLEN         (2)         /* userid 最短長度 */
#define GUEST               "guest"     /* 是否接受參觀用帳號進站 */
#define LOCAL_MAX_MSQ       (8)         /* 回顧訊息個數上限 */
#define MYCHARSET	    "big5"

/*******************************************************************
 *    關於認證
 *******************************************************************/
#define USE_IDENT                       /* 是否使用認證系統 */
#define EMAIL_LIMIT 1                   /* 是否限制未認證使用者寄站外信 */
#define PAGE_LIMIT  0                   /* 是否限制未認證使用者聊天/送訊息功能 */
#define SYSOP_BIN                       /* 是否線上查閱認證資料 */
#define USE_OVERRIDE_IN_LIST


/**************************************************************************
 *    關於一些功能使用的定義
 **************************************************************************/
#define USE_VOTE                        /* 是否使用投票系統 */
#define USE_MENUSHOW                    /* 是否使用秀圖界面 */
#undef USE_MULTI_LANGUAGE               /* 是否使用多國語言 */
#if 0
#define USE_THREADING					/* syhu: threading on/off */
#define THREADUNIT_SIZE		10			/* syhu:.THREADPOST 檔幾筆為一單位 */
#endif

/*************************************************************************
 *   以下只適用於 NSYSU     BBS (中山大學 BBS)
 *************************************************************************/
#if defined(ULTRABBS)|| defined(NSYSUBBS3) || defined(NSYSUBBS2) || defined(NSYSUBBS1) || defined(ANIMEBBS)
#define NSYSUBBS
#endif

#ifdef NSYSUBBS
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
# undef SYSOP_BIN
# undef LOCAL_MAX_MSQ
# define LOCAL_MAX_MSQ 20
/* kmwang: 打開進 mail 讀信時煩 user 的功能 */
# define MAILWARN
/* kmwang: 開啟 delete user 的功能 在 ULTRA 測試將信轉寄給 user 之功能*/
 #ifdef ULTRABBS
 # undef USE_DELUSER
/* kmwang: 支援 YSNP server */
 # define NP_SERVER
 # define USE_ALOHA
 # undef MAXACTIVE
 # define MAXACTIVE (256)
 #endif
#endif

#if defined(PHBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
# undef MAXACTIVE
# define MAXACTIVE 100
/*
# define BBSNAME     "phbbs"
# define BBSTITLE    "澎湖縣教育網路中心"
*/
#elif   defined(SSBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
# undef MAXACTIVE
# define MAXACTIVE 512
#elif   defined(KHBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
/*
# define BBSNAME     "khbbs"
# define BBSTITLE    "高雄市資訊教育網路 BBS 站"
*/
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
# undef MAXBOARD
# define MAXBOARD 384
# undef MAXACTIVE
# define MAXACTIVE 512
# define WEB_BOARD
# define CAPTURE_BOARD	"keepmessage"
/* 忽略 ID 的大小寫 */
//# define IGNORE_CASE
#elif   defined(STITBBS)
/*
# define BBSNAME     "shutebbs"
# define BBSTITLE    "樹德技術學院 BBS 站"
*/
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
#elif   defined(KGHSBBS)
# undef HOMEBBS
# define HOMEBBS "/apps/bbs"
/*
# define BBSNAME     "kghsbbs"
# define BBSTITLE    "高雄女中 BBS 站"
# define MENU_TITLE_COLOR1      "[1;37;45m"
# define MENU_TITLE_COLOR     "[1;33;45m"
*/
# undef MAXACTIVE
# define MAXACTIVE (256)
# define ACTFILE     "conf/actfile"
# define CHROOT_BBS
/*
#elif	defined(ULTRABBS)
# define BBSNAME     "ultrabbs"
# define BBSTITLE    "中山大學 Ultra BBS"
  */
# undef PAGE_LIMIT
# define PAGE_LIMIT 0
# define WEB_BOARD
#elif   defined(NSYSUBBS3)
/*
# define BBSNAME     "westbbs"
# define BBSTITLE    "中山大學 West BBS-西子灣站"
# define HAVE_HOSTLIST
*/
# define NP_SERVER
# define USE_ALOHA
# undef PAGE_LIMIT
# define PAGE_LIMIT 0
# undef MAXACTIVE
# define MAXACTIVE (2048)
# undef MAXBOARD
# define MAXBOARD 4096
/*
#elif defined(NSYSUBBS2)
# define BBSNAME     "southbbs"
# define BBSTITLE    "中山大學 South BBS-南風站"
# define MENU_TITLE_COLOR1      "[1;37;43m"
# define MENU_TITLE_COLOR     "[1;33;47m"
# undef MAXACTIVE
# define MAXACTIVE (600)
*/
#elif defined(ANIMEBBS)
# undef MAXACTIVE
# define MAXACTIVE (100)
/*
# define BBSNAME     "irradiance"
# define BBSTITLE    "光之大陸 ★ 伊莉琴斯"
# define MENU_TITLE_COLOR1      "[1;33;42m"
# define MENU_TITLE_COLOR     "[0;37;42m"
*/
#elif defined(NSYSUBBS1)
/*
# define BBSNAME     "formosabbs"
# define BBSTITLE    "中山大學 Formosa BBS-美麗之島"
  */
# undef MAXACTIVE
# define MAXACTIVE (4096)
# undef MAXBOARD
# define MAXBOARD (4096)
# undef PAGE_LIMIT
# define PAGE_LIMIT 1
# define CAPTURE_BOARD	"keepmessage"
# define WEB_BOARD
# define STRICT_IDENT
# undef USE_OVERRIDE_IN_LIST
/*# define USE_ALOHA*/
#endif


#endif /* _BBS_CONFIG_H_ */
