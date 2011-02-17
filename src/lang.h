
#ifndef _BBS_LANG_H_
#define _BBS_LANG_H_

#define LANG_CHINESE 0
#define LANG_ENGLISH 1

struct LANG {
	time_t mtime;
	int msg[511]; 		/* used about 429	*/
	char pool[20480]; 	/* used about 16838 */
};	/* 22 k-bytes */


#define MsgInfo(n) (langshm->pool + langshm->msg[n])


#define	_msg_admin_1	MsgInfo(2)	/*	"(E)修改看板設定 (D)刪除看板 (P)整理看板 (Q)離開 ? [Q]: "	*/
#define	_msg_admin_2	MsgInfo(11)	/*	"英文板名 : "	*/
#define	_msg_admin_3	MsgInfo(12)	/*	"不合法板名 或 看板已存在."	*/
#define	_msg_admin_5	MsgInfo(13)	/*	"看板等級 (0 ~ 255) [0] : "	*/
#define	_msg_admin_9	MsgInfo(15)	/*	"資料設定不全, 無法存檔!"	*/
#define	_msg_admin_16	MsgInfo(8)	/*	"\n確定將使用者 '%s' 強制離線 (y/n) ? [n]: "	*/
#define	_msg_admin_17	MsgInfo(9)	/*	"\n\n共清除線上 %d 個 logins."	*/
#define	_msg_admin_18	MsgInfo(10)	/*	"所有人"	*/
#define	_msg_admin_bdesc	MsgInfo(16)	/*	"中文說明 : "	*/
#define	_msg_admin_blevel	MsgInfo(17)	/*	"看板等級 : "	*/
#define	_msg_admin_class	MsgInfo(18)	/*	"看板類別 : "	*/
#define	_msg_admin_owner	MsgInfo(19)	/*	"板    主 : "	*/
#define	_str_brdtype_ident	MsgInfo(21)	/*	"認證可張貼"	*/
#define	_str_brdtype_invisible	MsgInfo(22)	/*	"隱藏"	*/
#define	_str_brdtype_news	MsgInfo(23)	/*	"轉信"	*/
#define	_str_brdtype_nopostnum	MsgInfo(24)	/*	"不計張貼數"	*/
#define	_str_brdtype_unzap	MsgInfo(25)	/*	"不可ZAP"	*/
#define	_str_brdtype_crosspost	MsgInfo(26)	/*	"不可轉貼"	*/

#define	_msg_article_1	MsgInfo(34)	/*	"您欲刪除標記保留的文章前, 請先取消該標記保留屬性!"	*/
#define	_msg_article_2	MsgInfo(37)	/*	"<<整批標記>> 從第幾項開始 ? "	*/
#define	_msg_article_3	MsgInfo(38)	/*	"<<整批標記>> 到第幾項為止 ? "	*/
#define	_msg_article_5	MsgInfo(40)	/*	"[0;37;44m[r][y]:回應 [↓][→][Space][n]:下篇 [↑][p]:上篇 [m]:寄出 [d]:刪除 [←][q]:退出[0m"	*/
#define	_msg_article_6	MsgInfo(41)	/*	"<<刪除文章>> (m)刪除 (u)取消刪除 (c)都不做 ? [c]: "	*/
#define	_msg_article_7	MsgInfo(42)	/*	"<<刪除文章>> (m)刪除 (u)取消刪除 (r)刪除並寄回給原作者 (c)都不做 ? [c]: "	*/
#define	_msg_article_8	MsgInfo(43)	/*	"<<刪除文章>> 刪除後即無法救回, 確定嗎 ? [n] : "	*/
#define	_msg_article_9	MsgInfo(44)	/*	"收信人 [%s] 對嗎 ? (y/n) [y] :"	*/

#define	_msg_article_11	MsgInfo(28)	/*	"[信件刪除通知]"	*/

#define	_msg_article_13	MsgInfo(30)	/*	"<<整批轉寄>> (t)已標記的 (a)此篇? [a]: "	*/
#define	_msg_article_14	MsgInfo(31)	/*	"<<整批刪除>> (t)已標記的 (a)此篇? [a]: "	*/

#define	_msg_article_18	MsgInfo(35)	/*	"與第幾項交換 ? "	*/
#define	_msg_article_19	MsgInfo(36)	/*	"使用標題 (%s) ? (y/n) [y] : "	*/

#define	_msg_ent_new_title	MsgInfo(46)	/*	"新標題: "	*/
#define	_str_crosspost	MsgInfo(47)	/*	"[轉貼]"	*/
#define	_str_header_title	MsgInfo(48)	/*	"標題: "	*/

#define	_msg_board_1	MsgInfo(49)	/*	"\n\n(Z)ap Yank(I)n,(O)ut (^)跳到第一項,($)末一項 (/)搜尋 (TAB)一般/精華區 (H)說明\n[7m   %s 板名             News   等級 中文說明                     板主        [m"	*/
#define	_msg_board_3	MsgInfo(51)	/*	"[轉]"	*/
#define	_msg_board_4	MsgInfo(52)	/*	" (↑)(↓)游標 (→)(Enter)選擇 (←)退出 (P)(PgUp)上頁 (N)(PgDn)(Sp)下頁        [m"	*/
#define	_msg_board_5	MsgInfo(53)	/*	"請輸入您要選的英文板名 (按 [Space] 空白鍵可列出過濾的清單)\n"	*/
#define	_msg_board_6	MsgInfo(54)	/*	"選擇看板: "	*/
#define	_msg_board_7	MsgInfo(55)	/*	"請輸入英文板名: "	*/
#define	_msg_chat_1	MsgInfo(56)	/*	"<<選擇進入>> (1)聊天室(2)知心茶室 ? [1]: "	*/
#define	_msg_chat_2	MsgInfo(67)	/*	"知心茶室"	*/
#define	_msg_chat_3	MsgInfo(78)	/*	"興建中, 請稍待\n"	*/
#define	_msg_chat_4	MsgInfo(89)	/*	"\n\n進入 chatroom 失敗!"	*/
#define	_msg_chat_6	MsgInfo(98)	/*	"打 [1;33m/help[0m 可看使用說明\n"	*/
#define	_msg_chat_7	MsgInfo(99)	/*	"\n*** 現在這裡的客人 ***"	*/
#define	_msg_chat_8	MsgInfo(100)	/*	"綽號"	*/
#define	_msg_chat_9	MsgInfo(101)	/*	"BBS ID"	*/
#define	_msg_chat_10	MsgInfo(57)	/*	"\n*** 現在所有的客人 ***"	*/
#define	_msg_chat_11	MsgInfo(58)	/*	"所在頻道"	*/

#define	_msg_chat_16	MsgInfo(63)	/*	"\n*** 目前所有頻道 ***"	*/
#define	_msg_chat_17	MsgInfo(64)	/*	"名稱"	*/
#define	_msg_chat_18	MsgInfo(65)	/*	"主題"	*/
#define	_msg_chat_19	MsgInfo(66)	/*	"管理員"	*/
#define	_msg_chat_20	MsgInfo(68)	/*	"成員數"	*/
#define	_msg_chat_21	MsgInfo(69)	/*	"鎖碼"	*/

#define	_msg_chat_36	MsgInfo(85)	/*	"*** [1;32m開始接收 ID：【%s】所說的話[0m ***"	*/
#define	_msg_chat_37	MsgInfo(86)	/*	"*** [1;32m拒絕收聽 ID：【%s】所說的話[0m ***"	*/

#define	_msg_chat_41	MsgInfo(91)	/*	"您可以使用這些命令:\n  /help                   - 說明畫面              [/h]\n  /who                    - 本頻道成員            [/w]\n  /who <頻道名稱>         - 某頻道成員            [/w]\n  /whoall                 - 所有頻道成員          [/ws]\n  /join <頻道> <鎖碼密碼> - 加入某頻道            [/j]\n  /list                   - 列出所有頻道          [/l]\n  /msg <BBS ID> <悄悄話>  - 送 <悄悄話> 給 <BBS ID> [/m]\n  /pager                  - 切換 Pager            [/p]\n  /nick <綽號>            - 改綽號 <綽號>         [/n]\n  /me <重要的話>          - 請大家注意你的話      [/me]\n  /ignore <BBS ID>        - 拒聽某人的話          [/i]\n  /unignore <BBS ID>      - 接收某人的話          [/ui]\n  /clear                  - 清除畫面              [/c]"	*/
#define	_msg_chat_43	MsgInfo(93)	/*	"以下命令僅提供管理者使用:\n  /passwd <密碼>          - 設定本頻道密碼 [/ps]\n  /nopasswd               - 解除本頻道密碼 [/nps]\n  /topic <主題>           - 更改本頻道主題 [/t] \n  ctrl-d                  - 離開"	*/
#define	_msg_chat_44	MsgInfo(94)	/*	"*** 指定頻道不存在"	*/
#define	_msg_chat_45	MsgInfo(95)	/*	"*** 錯誤: 後面要加一句話"	*/
#define	_msg_chat_46	MsgInfo(96)	/*	"打 /help 可看說明畫面\n"	*/
#define	_msg_edit_5	MsgInfo(106)	/*	"(s)%s, (a)放棄, (t)存入暫存檔, 或 (e)繼續編輯? [s]: "	*/
#define	_msg_edit_6	MsgInfo(107)	/*	"送出"	*/
#define	_msg_edit_7	MsgInfo(108)	/*	"存檔"	*/
#define	_msg_edit_8	MsgInfo(109)	/*	"\n您有一個編輯失敗的備份檔 !!\n請問 (1)引入 (2)清掉備份 ? (1/2) [1] : "	*/
#define	_msg_edit_9	MsgInfo(110)	/*	"Type [Ctrl-Z]: help. [Ctrl-R]: save and continue edit."	*/
#define	_msg_include_which_sig	MsgInfo(111)	/*	"引入第幾個簽名檔"	*/
#define	_msg_no_include_sig	MsgInfo(112)	/*	"不引入"	*/
#define	_msg_no_use_sig	MsgInfo(113)	/*	"\n提醒您: 您已設定不再使用簽名檔!"	*/
#define	_msg_signature	MsgInfo(114)	/*	"簽名檔"	*/
#define	_msg_formosa_1	MsgInfo(132)	/*	"\n歡迎! 新伙伴, 請輸入您所希望的代號(一個英文名字)\n"	*/
#define	_msg_formosa_2	MsgInfo(143)	/*	"使用者代號 (user id) : "	*/
#define	_msg_formosa_3	MsgInfo(153)	/*	"\n請輸入至少 %d 個小寫字母, 不可有特殊符號, 空白, 數字, 不雅字眼\n"	*/
#define	_msg_formosa_4	MsgInfo(164)	/*	"\n您還是沒想好要使用的代號, 下次再來囉, 掰掰 ...\n"	*/
#define	_msg_formosa_5	MsgInfo(169)	/*	"\n此代號已被使用, 請換一個\n"	*/
#define	_msg_formosa_6	MsgInfo(170)	/*	"密碼(password, 4 - 8 個字) : "	*/
#define	_msg_formosa_7	MsgInfo(171)	/*	"\n密碼長度至少要 4 個字元\n"	*/
#define	_msg_formosa_8	MsgInfo(172)	/*	"\n請勿使用與 ID 相同或太過於簡單易猜的密碼\n"	*/
#define	_msg_formosa_9	MsgInfo(173)	/*	"再打一次密碼(check) : "	*/
#define	_msg_formosa_10	MsgInfo(133)	/*	"\n兩次輸入的密碼不一樣, 請重新設定.\n"	*/
#define	_msg_formosa_11	MsgInfo(134)	/*	"您的暱稱 (Name 中英文皆可) : "	*/
#define	_msg_formosa_12	MsgInfo(135)	/*	"電子郵件地址 : "	*/
#define	_msg_formosa_13	MsgInfo(136)	/*	"\r\n建新帳號失敗, 連線終結"	*/
#define	_msg_formosa_14	MsgInfo(137)	/*	"\n歡迎光臨 [1;37m%s[m, 目前線上有 [[1;33m%d[m/[1;32m%d[m] 人\n"	*/
#define	_msg_formosa_15	MsgInfo(138)	/*	"系統 (1,10,15) 分鐘的平均負荷分別為 %s\n"	*/
#define	_msg_formosa_16	MsgInfo(139)	/*	"\n\r[1;32m上限 %d 人, 請稍候再來"	*/
#define	_msg_formosa_17	MsgInfo(140)	/*	"\n抱歉, 你已打錯 %d 次, 下次再來吧!\n"	*/
#define	_msg_formosa_18	MsgInfo(141)	/*	"\n若想註冊新帳號, 請輸入 'new'"	*/
#define	_msg_formosa_19	MsgInfo(142)	/*	" (參觀請輸入 '%s') 第二連接埠為 Port 9001"	*/
#define	_msg_formosa_20	MsgInfo(144)	/*	"\n若想參觀請輸入 '%s'"	*/
#define	_msg_formosa_21	MsgInfo(145)	/*	"\n請輸入代號(user id) : "	*/
#define	_msg_formosa_22	MsgInfo(146)	/*	"\r\n本系統不接受新使用註冊 !!"	*/
#define	_msg_formosa_23	MsgInfo(147)	/*	"\r\n請以 guest 參觀用帳號進站."	*/
#define	_msg_formosa_25	MsgInfo(148)	/*	"請輸入密碼(password) : <請直接按 Enter 即可>  "	*/
#define	_msg_formosa_26	MsgInfo(149)	/*	"請輸入密碼(password) : "	*/
#define	_msg_formosa_27	MsgInfo(150)	/*	"密碼錯誤 !!\n"	*/
#define	_msg_formosa_28	MsgInfo(151)	/*	"要查看等級多少以上的使用者 ? [0] : "	*/
#define	_msg_formosa_29	MsgInfo(152)	/*	"代名"	*/
#define	_msg_formosa_30	MsgInfo(154)	/*	"全名"	*/
#define	_msg_formosa_31	MsgInfo(155)	/*	"上站數"	*/
#define	_msg_formosa_32	MsgInfo(156)	/*	"張貼數"	*/
#define	_msg_formosa_33	MsgInfo(157)	/*	"等級"	*/
#define	_msg_formosa_34	MsgInfo(158)	/*	"[37;45m--- 還有哦 ---[44m [q] or [←]:離開 , [→][n][Space]:下一頁        [m"	*/
#define	_msg_formosa_35	MsgInfo(159)	/*	"[37;44m註冊人數 %d 人, "	*/
#define	_msg_formosa_36	MsgInfo(160)	/*	"[37;44m統計人數 %d/%d 人, "	*/
#define	_msg_formosa_37	MsgInfo(161)	/*	"管理者 %d 人, 板主 %d 人"	*/
#define	_msg_formosa_38	MsgInfo(162)	/*	", (通過認證 %d 人)"	*/
#define	_msg_formosa_39	MsgInfo(163)	/*	"\n本站參觀用站號(guest)使用人數已額滿, 請您稍後再試.\n"	*/
#define	_msg_formosa_40	MsgInfo(165)	/*	"\n%d. Login PID:[%d] 來自 %s 是否刪除 (y/n) ? [n] : "	*/
#define	_msg_formosa_41	MsgInfo(166)	/*	"\n不能重覆 Login %d 次 !!"	*/
#define	_msg_formosa_42	MsgInfo(167)	/*	"[1;33m你有上次編輯失敗的檔案喔！！\n將在下次編輯時請您選擇是否引入[m"	*/
#define	_msg_formosa_44	MsgInfo(168)	/*	"帳號不存在 !!\n"	*/

#define	_msg_ident_1	MsgInfo(174)	/*	"您要修改誰的確認等級："	*/
#define	_msg_ident_2	MsgInfo(185)	/*	"請輸入認證等級 (0 or 7) ? [0]: "	*/
#define	_msg_ident_3	MsgInfo(188)	/*	"您要查詢誰的真實資料 [ID]："	*/

#define	_msg_ident_7	MsgInfo(192)	/*	"您所輸入的 E-Mail 信箱位址可能為免費信箱, 恕不接受!"	*/
#define	_msg_ident_8	MsgInfo(193)	/*	"寄送認證信函失敗"	*/
#define	_msg_ident_9	MsgInfo(194)	/*	"系統已寄送出認證函. 請您務必至以下信箱將認證函回覆以便完成認證程序:\n%s"	*/
#define	_msg_ident_10	MsgInfo(175)	/*	"本站對認證資料絕對保密, 您要做身份認證嗎 ? [N]: "	*/
#define	_msg_ident_11	MsgInfo(176)	/*	"登錄認證資料失敗."	*/
#define	_msg_ident_12	MsgInfo(177)	/*	"請填入下列資料: "	*/
#define	_msg_ident_13	MsgInfo(178)	/*	" 請問您所填的為護照號碼嗎 (Y/N) ? : [N]"	*/
#define	_msg_ident_14	MsgInfo(179)	/*	"[1;36m 填寫護照號碼, 須寄護照影本, 請看 system-report 板精華區說明[m"	*/
#define	_msg_ident_15	MsgInfo(180)	/*	"[1;36m 填寫 xxx.bbs@[hostname], 須寄身份證影本, 請看 system-report 板精華區說明[m"	*/
#define	_msg_ident_16	MsgInfo(181)	/*	"申請日期：%s\n"	*/
#define	_msg_ident_17	MsgInfo(182)	/*	"\n以上資料都正確嗎 [N] ?"	*/
#define	_msg_ident_18	MsgInfo(183)	/*	"資料可能有誤"	*/
#define	_msg_ident_19	MsgInfo(184)	/*	"身份確認: %s"	*/
#define	_msg_ident_20	MsgInfo(186)	/*	"登錄失敗"	*/
#define	_msg_ident_21	MsgInfo(187)	/*	"\n本認證系統無法接受您輸入的 e-mail 位址!"	*/

#define	_msg_ident_item1	MsgInfo(195)	/*	"1 姓名(中文)："	*/
#define	_msg_ident_item2	MsgInfo(196)	/*	"2 家裡電話："	*/
#define	_msg_ident_item3	MsgInfo(197)	/*	"3 學校或公司電話(若無,可不填)："	*/
#define	_msg_ident_item4	MsgInfo(198)	/*	"4 通訊地址："	*/
#define	_msg_ident_item5	MsgInfo(199)	/*	"5 身份證字號："	*/
#define	_msg_ident_item6	MsgInfo(200)	/*	"6 戶籍申報地："	*/
#define	_msg_ident_item7	MsgInfo(201)	/*	"7 生日(yy/mm/dd)："	*/
#define	_msg_ident_item8	MsgInfo(202)	/*	"8 電子郵件信箱(請務必確實填寫正確)："	*/
#define	_msg_ident_item9	MsgInfo(203)	/*	"9 簡短介紹："	*/

#define	_msg_list_4	MsgInfo(217)	/*	"[排序方法]"	*/
#define	_msg_list_5	MsgInfo(218)	/*	"\n %s %s  [使用者] %s  [總人數] %-4d  [好友數] %d \n (f)好友 (t)聊天 (a,d)交友 (u)查詢 (w,l)送,回訊息 (m)寄信 (TAB)排序 (s)更新"	*/
#define	_msg_list_6	MsgInfo(219)	/*	" 聊天選單使用說明\n-----------------------------------------------------------------------------\n 基本功\能鍵\n   [↑] [p]     往上移一行     [Ctrl-B] [PgUp]      翻上一頁\n   [↓] [n]     往下移一行     [Ctrl-F] [PgDn] [Sp] 翻下一頁\n   [←] [e]     離開聊天選單   [##]                 跳到第幾項\n   [Home]       跳到第一項     [$] [End]            跳到末一項\n\n 特殊功\能鍵\n   [s]          重新顯示列表   [f]                  列出線上好友/全部網友\n   [m]          寄信給網友     [u] [Enter][→]      查詢網友資料\n   [/]          找尋           [TAB]                切換排序方式\n   [x]          閱\讀個人信件   [a] [d]              增加/刪除好友名單\n"	*/
#define	_msg_list_7	MsgInfo(220)	/*	"\n 交談專用鍵\n   [t]          跟他／她聊天   [Ctrl-P]             切換呼喚鈴開關\n   [w]          線上送訊息     [Ctrl-R] [l]         回顧線上訊息\n"	*/
#define	_msg_list_9	MsgInfo(222)	/*	"請輸入搜尋字串："	*/
#define	_msg_list_12	MsgInfo(207)	/*	"線上好朋友列表"	*/
#define	_msg_list_13	MsgInfo(208)	/*	"線上使用者列表"	*/
#define	_msg_list_14	MsgInfo(209)	/*	"\n[7m   編號 英文代名     %-20s %-15s %cP %-9s 閒置(分)[0m\n"	*/
#define	_msg_list_16	MsgInfo(210)	/*	"中文代稱"	*/
#define	_msg_list_17	MsgInfo(211)	/*	"來自"	*/
#define	_msg_list_18	MsgInfo(212)	/*	"狀態"	*/
#define	_msg_list_19	MsgInfo(213)	/*	"...使用者進站中..."	*/
#define	_msg_list_20	MsgInfo(215)	/*	" (↑)(↓)游標 (→)(Enter)查詢 (Ctrl-P)切換呼叫鈴 (h)說明  %s [m"	*/

#define	_msg_ask_group_add	MsgInfo(228)	/*	"選項: [a]加入 [d]刪除 [f]好友 [e]完成 [q]放棄 : [e] "	*/

#define	_msg_checkfwdemailaddr	MsgInfo(230)	/*	"\n請先修改個人資料, 在 e-mail 欄位填上您要轉寄的位址.\n才能啟動此設定\n\n例如: \n   myuserid@myhost.mydomain"	*/
#define	_msg_checkfwdemailaddr_fail	MsgInfo(231)	/*	"\n個人資料 e-mail 欄位設定錯誤, 勿填寫本站位址, 請重新設定."	*/
#define	_msg_checkfwdemailaddr_nsysu	MsgInfo(232)	/*	"\n若要使用自動轉寄服務, 個人資料 e-mail 欄位請勿填寫中山BBS站"	*/
#define	_msg_delete	MsgInfo(233)	/*	"刪除: "	*/
#define	_msg_m_forward_desc	MsgInfo(234)	/*	" (個人信箱新信是否[自動轉寄]至您的[電子郵箱])"	*/

#define	_msg_m_new_command_prompt	MsgInfo(237)	/*	"<<讀新信>> (r)回信 (d)刪除 (n)下一封 (e)離開? [n] : "	*/

#define	_msg_m_new_nomore	MsgInfo(239)	/*	"沒有新信了 !!"	*/
#define	_msg_m_new_read_prompt	MsgInfo(240)	/*	"寄信人 : %s\n標題 : %s\n(y)讀取此封 (n)下一封 (q)離開 ? [y] : "	*/
#define	_msg_mail_1	MsgInfo(241)	/*	"寄(回)給 [%s] ? (y/n) [y] : "	*/
#define	_msg_mail_2	MsgInfo(242)	/*	"寄(回)給 : "	*/
#define	_msg_mail_3	MsgInfo(14)	/*	"個人信件列表"	*/
#define	_msg_mail_group_max_prompt	MsgInfo(243)	/*	"\n群組寄信人數上限: %d"	*/
#define	_msg_mail_to_all_friend	MsgInfo(244)	/*	"寄信給所有好友"	*/
#define	_msg_max_group	MsgInfo(245)	/*	"[寄信給多人] 人數上限: %d"	*/
#define	_msg_max_mail_warning	MsgInfo(246)	/*	"\n目前信箱內有 [1m%d[m 封信件, 已經超過限制.\n因此無法讀新信, 請將信件量刪至 [1m%d[m 封再離開\n否則下次您有新的信件到達時, 將無法存入信箱中.[m"	*/
#define	_msg_receiver	MsgInfo(247)	/*	"收信人: "	*/
#define	_msg_main_1	MsgInfo(248)	/*	"\r\n\r\n抱歉，您的位址 %s 不能使用本站\r\n"	*/
#define	_msg_main_2	MsgInfo(249)	/*	"\r\n\r\n☆ %s ☆\r\n\r\r\n\r"	*/
#define	_msg_title_func	MsgInfo(250)	/*	"看板：%-16.16s [m"	*/
#define	_msg_menu_2	MsgInfo(251)	/*	" (↑)(↓)游標 (→)(Enter)選擇 (←)(Q)上層 (Tab)展開公告   %s [m"	*/
#define	_msg_more_1	MsgInfo(253)	/*	"[1;37;45m--More--(%d%%)p.%d [0;44m [→]:下一頁,[↓]:下一列,[B]:上一頁,[←][q]:離開             [m"	*/
#define	_msg_abort	MsgInfo(254)	/*	"放棄."	*/
#define	_msg_board_normal	MsgInfo(257)	/*	"[一般區]"	*/
#define	_msg_board_treasure	MsgInfo(258)	/*	"[精華區]"	*/

#define	_msg_ent_userid	MsgInfo(261)	/*	"輸入英文代名: "	*/
#define	_msg_err_boardname	MsgInfo(262)	/*	"看板名稱錯誤"	*/
#define	_msg_err_userid	MsgInfo(263)	/*	"\n使用者代號錯誤."	*/
#define	_msg_fail	MsgInfo(264)	/*	"失敗."	*/
#define	_msg_finish	MsgInfo(266)	/*	"完成."	*/
#define	_msg_in_processing	MsgInfo(268)	/*	"處理中, 請稍候 ..."	*/
#define	_msg_include_ori	MsgInfo(269)	/*	"\n是否引入原文 (y/n/r) ? [y]: "	*/
#define	_msg_message_fail	MsgInfo(270)	/*	"送出訊息失敗."	*/
#define	_msg_message_finish	MsgInfo(271)	/*	"送出訊息完成."	*/
#define	_msg_no_board_exist	MsgInfo(272)	/*	"讀不到任何看板 !!\n"	*/
#define	_msg_not_choose_board	MsgInfo(273)	/*	"尚未選定看板"	*/
#define	_msg_not_sure	MsgInfo(274)	/*	"==>> 確定嗎 (y/n) ? [n] : "	*/
#define	_msg_not_sure_modify	MsgInfo(275)	/*	"==>> 確定要修改嗎 (y/n) ? [n] : "	*/
#define	_msg_off	MsgInfo(276)	/*	"關閉"	*/
#define	_msg_on	MsgInfo(277)	/*	"開啟"	*/
#define	_msg_press_enter	MsgInfo(278)	/*	"                         [1;37;44m   請按 [Enter] 鍵繼續   [m"	*/
#define	_msg_sorry_email	MsgInfo(279)	/*	"抱歉, 目前不提供未認證使用者的網路 e-mail 服務."	*/
#define	_msg_sorry_ident	MsgInfo(280)	/*	"抱歉, 自88年9月1日起未通過身份認證的使用者不開放使用此功\能."	*/
#define	_msg_sorry_newuser	MsgInfo(216)	/*	"等級 20 以下且未通過身份認證者不開放此功能."	*/
#define	_msg_title	MsgInfo(281)	/*	"標題： "	*/
#define	_msg_to_nth	MsgInfo(282)	/*	"跳至第幾項: "	*/
#define	_msg_you_have_mail	MsgInfo(283)	/*	" 您有新信! "	*/
#define	_msg_bm_limit_assist	MsgInfo(285)	/*	"已有三位板主助手." 	*/
#define	_msg_bm_manage_about	MsgInfo(286)	/*	"板主須知：\n\n    您所指定的板主助手名額上限為\"三位\"，且由於板主助手對該看板與板主\n擁有相等之佈告與精華區文章整理權力，故將其視為板主代理人，而板主亦須\n為所選出之板主助手行為負連帶責任，因此請慎重決定人選。"	*/
#define	_msg_bm_manage_cmd_full	MsgInfo(287)	/*	"(E)編輯進板畫面, (D)刪除進板畫面, 或 (M)編輯板主助手名單 ? [E]: "	*/
#define	_msg_bm_manage_cmd_part	MsgInfo(288)	/*	"(E)編輯進板畫面, 或 (D)刪除進板畫面 ? [E]: "	*/
#define	_msg_bm_manage_edit_bmas	MsgInfo(289)	/*	"[編輯板主助手名單] 名單上的人將擁有本板主權限 (請小心使用)\n"	*/
#define	_msg_cannot_check_board_list	MsgInfo(290)	/*	"讀不到任何看板"	*/
#define	_msg_cannot_post_in_treasure	MsgInfo(291)	/*	"\n精華區張貼請用轉貼選項(t)\n或在閱\讀狀態下張貼\n"	*/
#define	_msg_choose_add	MsgInfo(292)	/*	"(A)增加一個名字, 或 (E)離開? [E]: "	*/
#define	_msg_choose_add_delete	MsgInfo(293)	/*	"(A)增加一個名字, (D)刪除一個名字, 或 (E)離開? [E]: "	*/
#define	_msg_display_assistant	MsgInfo(294)	/*	"以下為本板板主助手群名單, 協助板主處理板務:\n"	*/
#define	_msg_exceed	MsgInfo(295)	/*	"[1;33m您所選取的範圍超過了總篇數[0m"	*/
#define	_msg_mail_fail	MsgInfo(296)	/*	"寄信失敗"	*/
#define	_msg_mail_finish	MsgInfo(297)	/*	"寄信完成"	*/
#define	_msg_mailpost_reply	MsgInfo(298)	/*	"回覆到 (1)看板 或 (2)原文作者信箱 (3)以上皆是? [1]: "	*/
#define	_msg_no_ident_send_tonews	MsgInfo(299)	/*	"\n抱歉, 未通過認證使用者無法將文章送至站外."	*/
#define	_msg_no_tag_found	MsgInfo(300)	/*	"請先將文章標記."	*/
#define	_msg_none	MsgInfo(301)	/*	"(沒人)\n"	*/
#define	_str_marker	MsgInfo(284)	/*	"㊣"	*/

#define	_msg_post_1	MsgInfo(302)	/*	"將游標移到目錄再按(G)，便可轉入該子目錄"	*/
#define	_msg_post_2	MsgInfo(307)	/*	"<<轉入子目錄>>: (c)opy 複製 (m)ove 搬移後刪除 ? [c]: "	*/
#define	_msg_post_3	MsgInfo(308)	/*	"<<轉入精華區>>: (c)opy 複製 (m)ove 搬移後刪除 ? [c]: "	*/
#define	_msg_post_4	MsgInfo(309)	/*	"轉入後合併為一篇 (y/n) ? [n]: "	*/
#define	_msg_post_5	MsgInfo(310)	/*	"精華區最多只可開 %d 層, 不要太貪心啦 !"	*/
#define	_msg_post_6	MsgInfo(311)	/*	"目錄名稱: "	*/
#define	_msg_post_7	MsgInfo(312)	/*	"確定建立目錄 '[1;36m%s[m' 嗎 (y/n) ? [n] : "	*/
#define	_msg_post_8	MsgInfo(313)	/*	"以下是為本板服務的板主助手群:\n\n"	*/
#define	_msg_post_9	MsgInfo(314)	/*	"<<標識所有文章>> 為 (y)已讀過(n)未讀過(q)放棄 ? [q]:  "	*/
#define	_msg_post_10	MsgInfo(303)	/*	"從第幾項開始 ? "	*/
#define	_msg_post_11	MsgInfo(304)	/*	"到第幾項為止 ? "	*/
#define	_msg_post_12	MsgInfo(305)	/*	"[44m[整批標記欲轉精華區文章]: 依篇數號碼範圍[0m"	*/
#define	_msg_post_13	MsgInfo(306)	/*	"寄往站外或國外請直接填 E-mail 電子郵件信箱 (例如: user@pc.campus.zone)"	*/
#define	_msg_post_fail	MsgInfo(315)	/*	"張貼失敗."	*/
#define	_msg_post_finish	MsgInfo(316)	/*	"張貼完成."	*/
#define	_msg_post_on_normal	MsgInfo(317)	/*	"\n張貼在 '%s' 看板"	*/
#define	_msg_post_on_treasure	MsgInfo(318)	/*	"\n張貼在 '%s' 精華區"	*/
#define	_msg_post_rule	MsgInfo(319)	/*	"[44m標記範圍不得超過 [%d] 篇[0m"	*/
#define	_msg_postperm_reason_guest	MsgInfo(320)	/*	"\n抱歉, guest 帳號無法張貼於本板!\n"	*/
#define	_msg_postperm_reason_ident	MsgInfo(321)	/*	"\n抱歉, 本板目前只接受通過認證之使用者張貼!!"	*/
#define	_msg_postperm_reason_level	MsgInfo(322)	/*	"\n抱歉, 您的等級 [%d] 不到本板 [%s] 等級 [%d], 不能張貼在本板\n"	*/
#define	_msg_postperm_reason_treasure	MsgInfo(323)	/*	"抱歉, 只有本板板主 才能在精華區張貼 !!"	*/
#define	_msg_send_tonews_yesno	MsgInfo(324)	/*	"\n此篇是否要送上 News 轉信 (y/n) ? [y]: "	*/
#define	_msg_treasure_cnvt	MsgInfo(325)	/*	"<<轉入精華區>>:(n)轉一篇 (t)轉標記 (c)都不做 ? [c]: "	*/
#define	_msg_treasure_cnvt_dir	MsgInfo(326)	/*	"<<將標記文章轉入>>:(t)目錄 (.)上層 (c)都不做? [c]:"	*/
#define	_msg_backward	MsgInfo(328)	/*	"上"	*/
#define	_msg_forward	MsgInfo(329)	/*	"下"	*/
#define	_str_combined_treasure_title	MsgInfo(327)	/*	"[整理] 已標記文章"	*/

#define	_msg_read_2	MsgInfo(340)	/*	"板主：%-12.12s"	*/
#define	_msg_read_3	MsgInfo(345)	/*	"\n(h)說明 (Ctrl-p)張貼 (s)換看板 (Tab)精華區切換 (</>)(a/A)搜尋 ([/])主題閱讀\n(d)刪除 (m)寄出 (E)修改編輯 (b)進板畫面 ($)最後 (v)投票 (x)轉貼 (U)查詢發信人\n[7m   編號     發信人         日期     標題                                      [m"	*/
#define	_msg_read_4	MsgInfo(346)	/*	"[目錄]"	*/
#define	_msg_read_7	MsgInfo(349)	/*	" <<本篇已被 %s 刪除>>"	*/
#define	_msg_read_10	MsgInfo(331)	/*	"\n本層精華區無佈告.\n\n若要張貼第一篇, 請使用轉貼選項(t)"	*/
#define	_msg_read_11	MsgInfo(332)	/*	"沒有資料記載....\n"	*/
#define	_msg_read_12	MsgInfo(333)	/*	"您的信箱中沒有信件\n"	*/
#define	_msg_read_13	MsgInfo(334)	/*	"\n本板無佈告.\n\n您現在要張貼第一篇嗎 (y/n) ? [y]: "	*/
#define	_msg_read_14	MsgInfo(335)	/*	" [r][→]:讀 [↓][n]:下篇 [↑][p]:上篇 [m]:寄出 [d]:刪除 [←][q]:退出          [m"	*/
#define	_msg_read_15	MsgInfo(336)	/*	"要跳到第幾項 : "	*/
#define	_msg_read_16	MsgInfo(337)	/*	"向%s搜尋作者 [%s]: "	*/
#define	_msg_read_17	MsgInfo(338)	/*	"向%s搜尋標題 [%s]: "	*/
#define	_msg_read_18	MsgInfo(339)	/*	"標記(1)同標題(2)同作者 ? [1]: "	*/
#define	_msg_read_20	MsgInfo(341)	/*	"作者: "	*/
#define	_msg_read_21	MsgInfo(342)	/*	"處理中, 請稍候 ..."	*/
#define	_msg_read_22	MsgInfo(343)	/*	"共標記 %d 篇."	*/
#define	_msg_read_23	MsgInfo(344)	/*	"往%s已無符合條件的文章."	*/
#define	_msg_stuff_1	MsgInfo(352)	/*	"[31;42m------------(●【個人小檔案】●)-------------[m"	*/
#define	_msg_stuff_2	MsgInfo(363)	/*	"[1;37;44m       總張貼數 == [33m%-6d                    [m"	*/
#define	_msg_stuff_3	MsgInfo(364)	/*	"[1;37;44m       上站次數 == [33m%-6d                    [m"	*/
#define	_msg_stuff_4	MsgInfo(365)	/*	"[1;37;44m   上次來的時刻 == [33m%-26s[m"	*/
#define	_msg_stuff_5	MsgInfo(366)	/*	"[1;37;44m   上次來的地方 == [33m%-26s[m"	*/
#define	_msg_stuff_6	MsgInfo(367)	/*	"[1;37;44m   這次來的時刻 == [33m%-26s[m"	*/
#define	_msg_stuff_7	MsgInfo(368)	/*	"[1;37;44m   這次來的地方 == [33m%-26s[m"	*/
#define	_msg_stuff_8	MsgInfo(369)	/*	"[31;42m (● 現在時間是 %-24s ●) [m"	*/
#define	_msg_stuff_9	MsgInfo(370)	/*	"[1;33;45m 您呆置過久, 已自動離線 [m\n"	*/
#define	_msg_stuff_10	MsgInfo(353)	/*	"[1;36;45m  請按 [33m<Enter>[36m 之後離線  [m\n"	*/
#define	_msg_stuff_11	MsgInfo(354)	/*	"[1;33;45m   ＊ 是否離開本系統 (Y/N) :   [m"	*/
#define	_msg_stuff_14	MsgInfo(357)	/*	"選擇錯誤. 沒有找到符合的."	*/
#define	_msg_stuff_15	MsgInfo(358)	/*	"[1;37;44m                            雪 泥 鴻 爪 ， 雁 去 留 痕                        \n[m"	*/
#define	_msg_stuff_16	MsgInfo(359)	/*	"請留言（至多三行），按[Enter]結束：\n"	*/
#define	_msg_stuff_17	MsgInfo(360)	/*	"(S)存檔觀看(E)重新編輯(Q)放棄留言？[S]"	*/
#define	_msg_stuff_18	MsgInfo(361)	/*	"[7m%s(%s)%.*s於%s到此一遊[m"	*/
#define	_msg_stuff_19	MsgInfo(362)	/*	"[1;37;44m   順手塗鴉，心情隨筆(Y/N)[n] :   [m"	*/
#define	_msg_talk_1	MsgInfo(458)	/*	"[7m [q]:離開 [d]:清除所有訊息 [m"	*/
#define	_msg_talk_2	MsgInfo(382)	/*	"呼喚鈴 : (1)一個人靜靜 (2)好友 (3)好友或已認證 (4)所有人, 請選擇: "	*/
#define	_msg_talk_5	MsgInfo(414)	/*	"個人資料查詢："	*/
#define	_msg_talk_6	MsgInfo(423)	/*	"\n%s (%s), 等級 %d, 上站 %d 次, 張貼 %d 篇"	*/
#define	_msg_talk_7	MsgInfo(424)	/*	", [1;36m已完成身份認證 [m"	*/
#define	_msg_talk_8	MsgInfo(425)	/*	", [1;33m未完成身份認證 [m"	*/
#define	_msg_talk_9	MsgInfo(426)	/*	"\n上次上站時間 %s 來自 %s"	*/
#define	_msg_talk_12	MsgInfo(374)	/*	"\n電子郵件信箱: %s"	*/
#define	_msg_talk_13	MsgInfo(375)	/*	"\n---- 個人信件自動轉寄開啟,"	*/
#define	_msg_talk_14	MsgInfo(376)	/*	"\n---- 信箱中還有新信還沒看,"	*/
#define	_msg_talk_15	MsgInfo(377)	/*	"\n---- 信箱中的信件都看過了,"	*/
#define	_msg_talk_16	MsgInfo(378)	/*	"\n目前正在線上：%s %s"	*/
#define	_msg_talk_17	MsgInfo(379)	/*	"\n目前不在線上, "	*/
#define	_msg_talk_18	MsgInfo(380)	/*	"請按任意鍵查詢名片檔..."	*/
#define	_msg_talk_19	MsgInfo(381)	/*	"\n沒有名片檔."	*/
#define	_msg_talk_20	MsgInfo(383)	/*	"<請輸入使用者代號>"	*/
#define	_msg_talk_21	MsgInfo(384)	/*	"要查詢誰 ? "	*/
#define	_msg_talk_22	MsgInfo(385)	/*	"<請輸入英文代名> (按空白鍵可顯示並過濾線上使用者)\n"	*/
#define	_msg_talk_23	MsgInfo(386)	/*	"對象是: "	*/
#define	_msg_talk_24	MsgInfo(387)	/*	"對方已離線."	*/
#define	_msg_talk_27	MsgInfo(390)	/*	"正在對 %s 搖鈴囉, 請稍待片刻..\n按 Ctrl-D 可以中斷\n"	*/
#define	_msg_talk_28	MsgInfo(391)	/*	"再搖一次鈴.\n"	*/
#define	_msg_talk_29	MsgInfo(392)	/*	"對方已離線."	*/
#define	_msg_talk_30	MsgInfo(394)	/*	"--- ** 訊息: %s 想跟您聊聊"	*/
#define	_msg_talk_31	MsgInfo(395)	/*	"您想與來自 %s 的 %s 聊聊嗎 ?\n(Yes/No/Query) [Q]: "	*/
#define	_msg_talk_32	MsgInfo(396)	/*	"對方正巧中止呼叫, 故無法聯繫!"	*/
#define	_msg_talk_33	MsgInfo(397)	/*	"您要我告訴他的理由是[1]:"	*/
#define	_msg_talk_34	MsgInfo(398)	/*	"[您的回答]: "	*/
#define	_msg_talk_35	MsgInfo(399)	/*	"[7m<<< 談心雅室 >>> ↑ %s and ↓ %s (%-20.20s)[m"	*/
#define	_msg_talk_36	MsgInfo(400)	/*	"您確定要結束談話嗎 (y/n) ? [N]: "	*/
#define	_msg_talk_37	MsgInfo(401)	/*	"送出訊息: "	*/
#define	_msg_talk_38	MsgInfo(402)	/*	"確定送給 %s 嗎 (y/n) ? [y]: ";	*/
#define	_msg_talk_39	MsgInfo(403)	/*	"參觀用帳號不可交談."	*/

#define	_msg_talk_42	MsgInfo(407)	/*	"對方不希望被打擾."	*/
#define	_msg_talk_46	MsgInfo(410)	/*	"以下是最近一次所收到訊息, 現在要回嗎 (y/n) ? [n]:"	*/
#define	_msg_talk_47	MsgInfo(411)	/*	"尚未收到任何訊息..."	*/
#define	_msg_talk_48	MsgInfo(412)	/*	"(Ctrl-R 回訊息, 或 Enter 鍵返回)"	*/
#define	_msg_talk_57	MsgInfo(422)	/*	"所有好友"	*/
#define	_msg_talk_refusal_1	MsgInfo(427)	/*	"抱歉, 現在正忙著, 改天再聊好嗎 ?"	*/
#define	_msg_talk_refusal_2	MsgInfo(428)	/*	"抱歉, 待會再找您聊, O.K ?"	*/
#define	_msg_talk_refusal_3	MsgInfo(429)	/*	"抱歉, 正和某人聊天中...."	*/
#define	_msg_talk_refusal_4	MsgInfo(430)	/*	"抱歉, 我的打字速度太慢, 怕你睡著...."	*/
#define	_msg_talk_refusal_5	MsgInfo(431)	/*	"抱歉, 我不太喜歡 TALK 哩 !!"	*/
#define	_msg_talk_refusal_6	MsgInfo(432)	/*	"抱歉, 先來封信自我介紹吧 !!"	*/
#define	_msg_talk_refusal_7	MsgInfo(433)	/*	"抱歉, 累積點經驗再來吧 !!"	*/
#define	_msg_talk_refusal_8	MsgInfo(434)	/*	"其它"	*/

#define	_msg_vote_1	MsgInfo(435)	/*	"\n您目前有多重上線, 請您以最先的一個上線來進來投票."	*/
#define	_msg_vote_7	MsgInfo(448)	/*	"每人只可投 %d 票喔!"	*/
#define	_msg_vote_10	MsgInfo(436)	/*	"您確定要離開編輯嗎 ? [n]: "	*/
#define	_msg_vote_11	MsgInfo(437)	/*	"限制IP為 %s 方可投票, 抱歉!!"	*/
#define	_msg_vote_12	MsgInfo(438)	/*	"投票時間未到, 抱歉!!"	*/
#define	_msg_vote_13	MsgInfo(439)	/*	"投票時間已過, 抱歉!!..."	*/
#define	_msg_vote_14	MsgInfo(440)	/*	"投票等級為%3d, 抱歉!!..."	*/
#define	_msg_vote_15	MsgInfo(441)	/*	"開票時間尚未到, 不提供查詢!"	*/
#define	_msg_vote_17	MsgInfo(443)	/*	"\n(→)(Enter)選擇投票 (←)(Q)離開 (c)選舉說明 (i)顯示設定 (o)開票結果 (h)說明\n(a)增加選舉/候選項目 (d)刪除選舉/候選項目 (E)修改選舉/候選項目\n"	*/
#define	_msg_vote_18	MsgInfo(444)	/*	"     投票總人數 : %d"	*/
#define	_msg_vote_22	MsgInfo(449)	/*	"刪除完畢!"	*/
#define	_msg_vote_23	MsgInfo(450)	/*	"\n抱歉, 目前尚無舉辦任何投票!!"	*/
#define	_msg_vote_25	MsgInfo(452)	/*	"您要新增板投票嗎 ? [y]: "	*/
#define	_msg_vote_26	MsgInfo(453)	/*	"請先選擇您所管理的板子...."	*/
#define	_msg_vote_27	MsgInfo(454)	/*	"您要修改板投票嗎 ? [n]: "	*/
#define	_msg_vote_31	MsgInfo(459)	/*	"投票項目未完成"	*/
#define	_msg_vote_32	MsgInfo(460)	/*	"無投票時間"	*/
#define	_msg_vote_33	MsgInfo(461)	/*	"無投票標題"	*/
#define	_msg_vote_34	MsgInfo(462)	/*	"無法存檔, 請按任一鍵繼續."	*/
#define	_msg_vote_35	MsgInfo(463)	/*	"存檔完畢, 請按任意鍵離開."	*/
#define	_msg_vote_37	MsgInfo(465)	/*	"請輸幾日後開始[即刻開始請按Enter]: "	*/
#define	_msg_vote_38	MsgInfo(466)	/*	"請輸幾日後結束[至少1日]: "	*/
#define	_msg_vote_39	MsgInfo(467)	/*	"您要刪除板投票嗎 ? [n]: "	*/
#define	_msg_vote_holdlist9	MsgInfo(482)	/*	"[[1;36ms[m] 儲存投票. "	*/

#define	_msg_xyz_1	MsgInfo(442)	/*	"======== 註冊編號 : %5u ====================="	*/
#define	_msg_xyz_2	MsgInfo(265)	/*	"======== 使用者個人資料 ======================="	*/
#define	_msg_xyz_3	MsgInfo(205)	/*	"代名 (userid) : %s"	*/
#define	_msg_xyz_6	MsgInfo(371)	/*	"註冊日期 : %s"	*/
#define	_msg_xyz_7	MsgInfo(419)	/*	"暱稱 (username) : %s"	*/
#define	_msg_xyz_8	MsgInfo(418)	/*	"電子郵箱 : %s"	*/
#define	_msg_xyz_9	MsgInfo(348)	/*	"上站總數 : %d"	*/
#define	_msg_xyz_10	MsgInfo(445)	/*	"張貼總數 : %d"	*/
#define	_msg_xyz_11	MsgInfo(447)	/*	"使用等級 : %d"	*/
#define	_msg_xyz_13	MsgInfo(456)	/*	"請輸入舊密碼 (確認身份): "	*/
#define	_msg_xyz_14	MsgInfo(457)	/*	"\n抱歉, 輸入錯誤的舊密碼三次, 強迫離線.\n"	*/
#define	_msg_xyz_15	MsgInfo(446)	/*	"\n密碼錯誤. 請再試一次! (只能錯三次)."	*/
#define	_msg_xyz_16	MsgInfo(252)	/*	"目前系統時間 : %s"	*/
#define	_msg_xyz_19	MsgInfo(267)	/*	"信件總數 : %d"	*/
#define	_msg_xyz_22	MsgInfo(255)	/*	"\n簽名檔大於 %d Bytes, 將自動截掉超過部份"	*/
#define	_msg_xyz_23	MsgInfo(214)	/*	"(E)編輯 或 (D)刪除 ? [E]: "	*/
#define	_msg_xyz_24	MsgInfo(206)	/*	"\n檔案刪除完成."	*/
#define	_msg_xyz_27	MsgInfo(420)	/*	"自動轉寄 : %s"	*/
#define _msg_xyz_28	MsgInfo(115)	/*	"編輯壞人名單, 讓名單上的人不能打擾你\n"	*/
#define	_msg_xyz_29	MsgInfo(105)	/*	"編輯好朋友名單, 名單上的人隨時都能找你談話\n"	*/
#define	_msg_xyz_30	MsgInfo(103)	/*	"擔任板主 : "	*/
#define	_msg_xyz_31	MsgInfo(259)	/*	"密    碼 : "	*/
#define	_msg_xyz_36	MsgInfo(204)	/*	"請選擇欲更改項目編號, 或按 [Enter] 結束 : "	*/
#define	_msg_xyz_38	MsgInfo(102)	/*	"再次確認 : "	*/
#define	_msg_xyz_39	MsgInfo(104)	/*	"密碼不一致, 請重新輸入."	*/
#define	_msg_xyz_52	MsgInfo(236)	/*	"[1;37;46m                         訪  客  留  言  板                              [m\n\n"	*/
#define	_msg_xyz_53	MsgInfo(235)	/*	"[1;37;45m請按[Q]鍵結束, 或按[X]鍵表示以後不再看留言板, 或任意鍵翻下頁...[0m"	*/
#define	_msg_xyz_34	MsgInfo(229)	/*	"== 語言設定 ==\n"	*/
#define	_msg_xyz_35	MsgInfo(1)	/*	"請選擇您要使用的語言 : "	*/
#define	_msg_xyz_57	MsgInfo(50)	/*	"選擇簽名檔 (0/1/2/3) [0]放棄: "	*/
#define	_msg_xyz_58	MsgInfo(45)	/*	"選擇您所要編輯的簽名檔 (1/2/3): "	*/
#define	_msg_xyz_61	MsgInfo(5)	/*	"中文 (Big5)"	*/
#define	_msg_xyz_62	MsgInfo(3)	/*	"English (英文)"	*/


#endif /* _BBS_LANG_H_ */
