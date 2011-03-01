#include "bbs.h"
#include "tsbbs.h"
#include <sys/stat.h>

#define WRAPMARGIN (256)

struct textline
{
	struct textline *prev;
	struct textline *next;
	int memlen;
	int charlen;
	char data[2 * WRAPMARGIN];
};

BOOL ansi_mode = FALSE;

struct textline *firstline = NULL;
struct textline *lastline = NULL;

struct textline *currline = NULL;
int currpnt = 0;
int currpos = 0;
int shift = 0;	/* lthuang: 99/07 */

struct textline *top_of_win = NULL;
int curr_window_line;		/* the number of lines in the window */
BOOL redraw_everything;
int total_num_of_line = 0;

static void indigestion(int i)
{
	fprintf(stderr, "SERIOUS INTERNAL INDIGESTION CLASS %d\n", i);
}

static struct textline *back_line(register struct textline *pos, register int num)
{
	while (num-- > 0)
	{
		if (pos && pos->prev)
			pos = pos->prev;
		else
			break;
	}
	return pos;
}

static struct textline *forward_line(register struct textline *pos, register int num)
{
	while (num-- > 0)
	{
		if (pos && pos->next)
			pos = pos->next;
		else
			break;
	}
	return pos;
}

/*
 * get the number of this line in the current window
 */
static int getlineno()
{
	int cnt = 0;
	struct textline *p = currline;


	while (p != top_of_win)
	{
		if (p == NULL)
			break;
		cnt++;
		p = p->prev;
	}
	return cnt;
}

/*	kill ASCII space(' ')
	return the pointer of first none ' '
*/
static char *killsp(char *s)
{
	while (*s == ' ')
		s++;
	return s;
}

static struct textline *alloc_line()
{
	register struct textline *p;

	/* kmwang: For badident */
	extern BOOL IsRealSysop;
	if (IsRealSysop)
	{
		if (total_num_of_line > 8192)      /* lthuang: debug */
        	{
                	indigestion(3);
                	abort_bbs(0);
		}
	}
	else if (total_num_of_line > 2048)	/* lthuang: debug */
	{
		indigestion(3);
		abort_bbs(0);
	}

	p = (struct textline *) malloc(sizeof(*p));
	if (p == NULL)
	{
		indigestion(13);
		abort_bbs(0);
	}
	p->next = NULL;
	p->prev = NULL;
	p->data[0] = '\0';
	p->memlen = 0;
	p->charlen = 0;
	total_num_of_line++;
	return p;
}

/*
 * Appends p after line in list. Keeps up with last line as well.
 */
static void append(register struct textline *p, register struct textline *line)
{
	p->next = line->next;
	if (line->next)
		line->next->prev = p;
	else
		lastline = p;
	line->next = p;
	p->prev = line;
}

/*
 * delete_line deletes 'line' from the list and maintains the lastline, and
 * firstline pointers.
 */
static void delete_line(register struct textline *line)
{
	if (!line->next && !line->prev)
	{
		line->data[0] = '\0';
		line->memlen = 0;
		line->charlen = 0;
		return;
	}
	if (line->next)
		line->next->prev = line->prev;
	else
		lastline = line->prev;
	if (line->prev)
		line->prev->next = line->next;
	else
		firstline = line->next;
	total_num_of_line--;
	free(line);
}

/*
 * split splits 'line' right before the character pos
 */
static void split(register struct textline *line, register int pos,register int charpos)
{
	register struct textline *p;


	if (pos > line->memlen)
		return;
	p = alloc_line();
	p->memlen = line->memlen - pos;
	//int charpos = utf8strlen((unsigned char*)&line->data[pos]);
	p->charlen= line->charlen- charpos;
	line->memlen = pos;
	line->charlen= charpos;
	strcpy(p->data, (line->data + pos));
	line->data[pos] = '\0';
	append(p, line);
	if (line == currline && pos <= currpnt)		/* ? */
	{
		currline = p;
		currpnt -= pos;
		currpos = 0;
		curr_window_line++;
	}
	redraw_everything = TRUE;
}

/*
 * join connects 'line' and the next line.  It returns true if:
 *
 * 1) lines were joined and one was deleted
 * 2) lines could not be joined
 * 3) next line is empty
 *
 * returns false if:
 *
 * 1) Some of the joined line wrapped
 */
static int join(register struct textline *line)
{
	register int ovfl;


	if (!line->next)
		return TRUE;
	if (*killsp(line->next->data) == '\0')
		return TRUE;
	ovfl = line->memlen + line->next->memlen - WRAPMARGIN;
	if (ovfl < 0)
	{
		strcat(line->data, line->next->data);
		line->memlen += line->next->memlen;
		line->charlen += line->next->charlen;
		delete_line(line->next);
		return TRUE;
	}
	else
	{
		register char *s;
		register struct textline *p = line->next;

		s = p->data + p->memlen - ovfl - 1;
		while (s != p->data && *s == ' ')
			s--;
		while (s != p->data && *s != ' ')
			s--;
		if (s == p->data)
			return TRUE;
		split(p, (s - p->data) + 1,(s - p->data) + 1);
		/* indicate one of the two line are longer than WRAPMARGIN */
		if (line->memlen + p->memlen >= WRAPMARGIN)
		{
			indigestion(0);
			return TRUE;
		}
		join(line);	/* ? */
		p = line->next;
		if (p->memlen >= 1 && p->memlen + 1 < WRAPMARGIN)	/* ? */
		{
			if (p->data[p->memlen - 1] != ' ')
			{
				strcat(p->data, " ");
				p->memlen++;
			}
		}
		return FALSE;
	}
}

static void insert_char(register int c)
{
	register int i;
	register char *s;
	register struct textline *p = currline;
	register BOOL wordwrap = TRUE;

#ifdef FTUTF8_LEN	
	static unsigned char UTF8_charremain = 0;
	static char* UTF8_startpointer = NULL;
#endif
	if (currpnt > p->memlen)
	{
		indigestion(18+100*currpnt+10000*p->memlen);
		return;
	}
	for (i = p->memlen; i >= currpnt; i--)
		p->data[i + 1] = p->data[i];
	
	p->memlen++;
#ifdef FTUTF8_LEN	

	
	p->data[currpnt] = c;
	currpnt++;
	if(~c & 0x80){//0xxxxxxx
		currpos++;
		p->charlen ++;
	}else if(~c & 0x40){//10xxxxxx
		UTF8_charremain --;
		if(UTF8_charremain > 0)
			return;
		else{
			int chlen =utf8charwidth((unsigned char*)UTF8_startpointer); 
			currpos += chlen;
			p->charlen += chlen;
		}
	}else if(~c & 0x20){//110xxxxx
		UTF8_startpointer = &(p->data[currpnt-1]);
		UTF8_charremain = 1;
		return;
	}else if(~c & 0x10){//1110xxxx
		UTF8_startpointer = &(p->data[currpnt-1]);
		UTF8_charremain = 2;
		return;
	}else if(~c & 0x08){//11110xxx
		UTF8_startpointer = &(p->data[currpnt-1]);
		UTF8_charremain = 3;
		return;
	}else{
	//not support
		return;
	
	}
#else	
	p->data[currpnt] = c;
	currpnt++;
#endif
	if (p->memlen < WRAPMARGIN)
		return;
	s = p->data + (p->memlen - 1);
	while (s != p->data && *s == ' ')
		s--;
	while (s != p->data && *s != ' ')
		s--;
	if (s == p->data)
	{
		wordwrap = FALSE;
		s = p->data + (p->memlen - 2);
	}
	split(p, (s - p->data) + 1,(s - p->data) + 1);
	p = p->next;
	if (wordwrap && p->memlen >= 1)
	{
		i = p->memlen;
		if (p->data[i - 1] != ' ')
		{
			p->data[i] = ' ';
			p->data[i + 1] = '\0';
			p->memlen++;
		}
	}
	while (!join(p))
	{
		p = p->next;
		if (p == NULL)
		{
			indigestion(2);
			break;
		}
	}
}

static void delete_char()
{
	register int i;


	if (currline->memlen == 0)
		return;
	if (currpnt >= currline->memlen)
	{
		indigestion(1);
		return;
	}
	int delrange = 0;
	do{
		//rt.icurr++;
		delrange++;
	}while(currline->data[currpnt + delrange] & 0x80 && ~currline->data[currpnt + delrange] & 0x40);

 
	// kill next one character.
	//memmove(buf+rt.icurr, buf+rt.icurr+delrange, rt.iend-rt.icurr);
	//rt.iend-=delrange;
	currline->charlen -= utf8charwidth(&currline->data[i]);
	for (i = currpnt; i != currline->memlen - delrange +1; i++)
		currline->data[i] = currline->data[i + delrange];
	currline->memlen-=delrange;
}

static void join_currline()
{
	struct textline *p = currline;

	while (!join(p))
	{
		p = p->next;
		if (p == NULL)
		{
			indigestion(2);
			abort_bbs(0);
		}
	}
	redraw_everything = TRUE;
}

static void delete_currline()
{
	struct textline *p = currline->next;

	if (!p)
	{
		p = currline->prev;
		if (!p)
		{
			bell();
			return;
		}
		curr_window_line--;
	}
	if (currline == top_of_win)
		top_of_win = p;
	delete_line(currline);
	currline = p;
	redraw_everything = TRUE;
}

static void vedit_init()
{
	register struct textline *p;


	if (currline)
		return;
	p = alloc_line();
	firstline = p;
	lastline = p;
	currline = p;
	currpnt = 0;
	currpos = 0;
	top_of_win = p;
	curr_window_line = 0;
	redraw_everything = FALSE;
	total_num_of_line = 0;
	shift = 0;	/* lthuang: 99/07 */
}

/*
 * read text from file into editor buffer
 */
static void read_file(const char *filename)
{
	register int fd;
	unsigned char ch;

	vedit_init();
	if ((fd = open(filename, O_RDONLY)) < 0)
	{
		if ((fd = open(filename, O_WRONLY | O_CREAT, 0644)) > 0)
		{
			close(fd);
			return;
		}
		indigestion(4);
		abort_bbs(0);
	}

	while (read(fd, &ch, 1) > 0)
	{
		if (ch == '\t')
		{
			do
			{
				insert_char(' ');
			}
			while (currpnt & 0x7);
		}
#if	defined(BIT8)
		else if (isprint2(ch))
#else
		else if (isprint(ch))
#endif
			insert_char(ch);
		else if (ch == '\n')
			split(currline, currpnt,currpnt);
	}
	close(fd);
}



#define ABORT_EDITING   -1	/* lthuang: do not modify */
#define KEEP_EDITING 	-2
#define BACKUP_EDITING 	-3
#define FINISH_EDITING  0

static void backup_file(register char *bakfile)
{
	register FILE *fp;
	register struct textline *p;


	if ((fp = fopen(bakfile, "w")) == NULL)
	{
		indigestion(5);
		abort_bbs(0);
	}
	for (p = firstline; p != NULL; p = p->next)
	{
		if (p == lastline && p->data[0] == '\0')
			break;
		fprintf(fp, "%s\n", p->data);
	}
	fclose(fp);
	chmod(bakfile, 0600);	/* lthuang */
}


static void vedit_exit()
{
	register struct textline *p, *v;


	p = firstline;
	while (p != NULL)
	{
		v = p->next;
		free(p);
		p = v;
	}

	currline = NULL;
/*
 * lastline = NULL;
 * firstline = NULL;
 */
}


static int write_file(const char *filename, const char *saveheader, const char *bname)
{
	FILE *fpr, *fpw;
	char abort[2];

	sprintf(genbuf, _msg_edit_5, (saveheader) ? _msg_edit_6 : _msg_edit_7);
	getdata(0, 0, genbuf, abort, sizeof(abort), ECHONOSP | XLCASE);
	if (abort[0] == 'a' || abort[0] == 'A')
	{
		vedit_exit();
		outs("\nFile NOT saved\n");
		if (uinfo.mode == POSTING || uinfo.mode == SMAIL)	/* ? */
			unlink(filename);
		return ABORT_EDITING;
	}
	else if (abort[0] == 'e' || abort[0] == 'E')
		return KEEP_EDITING;
	else if (abort[0] == 't' || abort[0] == 'T')	/* lthuang */
	{
		vedit_exit();
		outs("\nWrite to buffers\n");
		return BACKUP_EDITING;
	}

	if ((fpw = fopen(filename, "w")) == NULL)
	{
		vedit_exit();
		outs("Error open, can not save\n");
		getkey();
		return ABORT_EDITING;
	}

	if (saveheader)
	{
/*
		write_article_header(fpw, curuser.userid, curuser.username, bname,
				     NULL, saveheader, NULL);
*/
#ifdef IGNORE_CASE
                write_article_header(fpw, strcasecmp(curuser.fakeuserid, curuser.userid)? curuser.userid:curuser.fakeuserid, uinfo.username, bname,
				     NULL, saveheader, NULL);
#else
                write_article_header(fpw, curuser.userid, uinfo.username, bname,
				     NULL, saveheader, NULL);
#endif
		fputs("\n", fpw);
	}

	sethomefile(genbuf, curuser.userid, UFNAME_EDIT);
	if ((fpr = fopen(genbuf, "r")) != NULL)
	{
		while (fgets(genbuf, sizeof(genbuf), fpr))
			fputs(genbuf, fpw);
		fclose(fpr);
	}
	fclose(fpw);
	outs("\nFile saved\n");
	vedit_exit();
	return FINISH_EDITING;
}


static void show_help_msg()
{
	move(b_line, 0);
	clrtoeol();
	move(b_line - 1, 0);
	clrtoeol();
	move(b_line, 10);
	standout();
	outs(_msg_edit_9);
	standend();
}


static void vedit_outs(char *s)
{
	int i;

	if (ansi_mode)
	{
		while (*s != '\0')
			outc(*s++);
		return;
	}

	i = 0;
	while (*(s + i) != '\0')
		i++;
	if (i < shift)
	{
		clrtoeol();
		return;
	}
	s += shift;
	i = t_columns - 1;
	while (*s != '\0' && i-- > 0)
	{
		if (*s == 0x1b)
			outc('*');
		else
			outc(*s);
		s++;
	}
}

static void display_buffer()
{
	register struct textline *p;
	register int i;

	clear();
	move(0, 0);
	for (p = top_of_win, i = 0; i < t_lines - 1; i++)
	{
		clrtoeol();
		if (p)
		{
			vedit_outs(p->data);
			outs("\n");
			p = p->next;
		}
		else
			outs("~\n");
	}
}

static void vedit_help()
{
	pmore(EDIT_HELP, TRUE);
	redraw_everything = TRUE;
}

/*
 * include signature: support multiple signatures
 */
static void do_article_sig(const char *wfile)
{
	int sig_no = 0, avalsig = 0, i;		/* default: don't include signature */
	FILE *fpr;
	static BOOL shownote = TRUE;

	if (curuser.flags[0] & SIG_FLAG)
	{
		if (shownote)
		{
			outs(_msg_no_use_sig);
			getkey();
			shownote = FALSE;
		}
		return;
	}

	sethomefile(genbuf, curuser.userid, UFNAME_SIGNATURES);
	if (!get_num_records(genbuf, sizeof(char)))
		return;
	if ((fpr = fopen(genbuf, "r")) == NULL)
		return;

	outs("\n");
	for (i = 0; i < (MAX_SIG_LINES * MAX_SIG_NUM) && fgets(genbuf, sizeof(genbuf), fpr); i++)
	{
		if (i % MAX_SIG_LINES == 0)
			prints("[1;36m[%s #%d][m\n", _msg_signature, ++avalsig);
		outs(genbuf);
	}
	fclose(fpr);
	prints("[m\n%s(1-%d,0:%s) ? [1]: ", _msg_include_which_sig, MAX_SIG_NUM, _msg_no_include_sig);

	sig_no = (getkey() - '0');
	if (sig_no > avalsig || sig_no < 0)
		sig_no = 1;
	if (sig_no != 0)
		include_sig(curuser.userid, wfile, sig_no);
}

int vedit(const char *filename, const char *saveheader, char *bname)
{
	int ch, foo;
	int lastcharindent = -1;
	BOOL firstkey = TRUE;
	char bakfile[PATHLEN];
	int old_rows = t_lines, old_columns = t_columns;

	sethomefile(bakfile, curuser.userid, UFNAME_EDIT);

	if ((saveheader || uinfo.mode == EDITPLAN || uinfo.mode == EDITBMWEL)
	    && isfile(bakfile)	/* lthuang */
#ifdef GUEST
	 && strcmp(curuser.userid, GUEST)
#endif
	 )
	{
		clear();
		outs(_msg_edit_8);
		if (getkey() != '2')
			mycp(bakfile, filename);
	}
	if (!isfile(filename))
		unlink(bakfile);
	if (saveheader)
		do_article_sig(filename);

	read_file(filename);

	top_of_win = firstline;
	currline = firstline;
	curr_window_line = 0;
	currpnt = 0;

	ansi_mode = FALSE;

	clear();
	display_buffer();

	move(curr_window_line, currpos);
	while ((ch = getkey()) != EOF)
	{
		if (firstkey)
		{
			firstkey = FALSE;
			show_help_msg();
		}
		if (talkrequest)	/* lthuang */
		{
			backup_file(bakfile);
			talkreply();
			pressreturn();
			ch = CTRL('G');		/* redraw screen */
		}
		else if (msqrequest)	/* lthuang */
		{
			msqrequest = FALSE;
			msq_reply();
#if 0
			ch = CTRL('G');
#endif
		}
		if (old_rows != t_lines || old_columns != t_columns)
		{
			static const char *msg_resized = "[1;34;47m螢幕大小已改變, 按(Ctrl-G)回到頁首![m";

			old_rows = t_lines;
			old_columns = t_columns;

			top_of_win = firstline;
			currline = top_of_win;
			curr_window_line = 0;
			currpnt = 0;
			shift = 0;
			redraw_everything = TRUE;
			move(t_lines / 2, (t_columns - strlen(msg_resized)) / 2);
			outs(msg_resized);
			while (getkey() != CTRL('G'));
		}
		else if (ch < 0x100 && isprint2(ch))
		{
			insert_char(ch);
			lastcharindent = -1;
		}
		else{
			int charwidthremain;
			switch (ch)
			{
			case KEY_UP:
				if (lastcharindent == -1)
					lastcharindent = currpos;
				if (!currline->prev)
				{
					bell();
					break;
				}
				curr_window_line--;
				currline = currline->prev;
				currpos = (currline->charlen > lastcharindent) ? lastcharindent : currline->charlen;
				currpnt = 0;
				charwidthremain = currpos;
				if(currpos == 0){
					currpnt = 0;
					break;
				}
				while(currpnt < currline->memlen){
					charwidthremain -=utf8charwidth(&currline->data[currpnt]);
					if( charwidthremain <= 0 ){
						break;
					}
					do{						
						currpnt++;
					}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
				}
				if(charwidthremain == 0){//not between DBCS
					do{						
						currpnt++;
					}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
					
				}else{				
					currpos--;
				}
				break;
			case KEY_DOWN:
				if (lastcharindent == -1)
					lastcharindent = currpos;
				if (!currline->next)
				{
					bell();
					break;
				}
				curr_window_line++;
				currline = currline->next;
				currpos = (currline->charlen > lastcharindent) ? lastcharindent : currline->charlen;
				currpnt = 0;
				charwidthremain = currpos;
				if(currpos == 0){
					currpnt = 0;
					break;
				}
				while(currpnt < currline->memlen){
					charwidthremain -=utf8charwidth(&currline->data[currpnt]);
					if( charwidthremain <= 0 ){
						break;
					}
					do{						
						currpnt++;
					}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
				}
				if(charwidthremain == 0){//not between DBCS
					do{						
						currpnt++;
					}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
					
				}else{				
					currpos--;
				}
				break;
			default:
				lastcharindent = -1;
				switch (ch)
				{
				case CTRL('T'):
					top_of_win = back_line(lastline, b_lines - 2);
					currline = lastline;
					curr_window_line = getlineno();
					currpnt = 0;
					redraw_everything = TRUE;
					break;
				case CTRL('S'):
					top_of_win = firstline;
					currline = top_of_win;
					curr_window_line = 0;
					currpnt = 0;
					redraw_everything = TRUE;
					break;
				case '\t':
					do
					{
						insert_char(' ');
					}
					while (currpnt & 0x7);
					break;
				case CTRL('U'):
				case CTRL('V'):
					insert_char(0x1b);
					break;
				case CTRL('C'):
					insert_char(0x1b);
					insert_char('[');
					insert_char('m');
					break;
				case KEY_RIGHT:
				case CTRL('F'):
					if (currline->memlen == currpnt)
					{
						if (!currline->next)
							bell();
						else
						{
							currpnt = 0;
							currpos = 0;
							curr_window_line++;
							currline = currline->next;
						}
					}
					else{
						currpos += utf8charwidth(&currline->data[currpnt]);
						do{
							currpnt++;
						}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
					}
					break;
				case KEY_LEFT:
				case CTRL('B'):
					if (currpnt == 0)
					{
						if (!currline->prev)
							bell();
						else
						{
							currline = currline->prev;
							currpnt = currline->memlen;
							currpos = currline->charlen;
							curr_window_line--;
						}
					}
					else{
						do{
							currpnt--;
						}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
						
						currpos -= utf8charwidth(&currline->data[currpnt]);
						
					}
					break;
				case CTRL('G'):
					clear();
					redraw_everything = TRUE;
					break;
				case CTRL('Z'):
					vedit_help();
					break;
				case KEY_PGUP:
				case CTRL('P'):
					top_of_win = back_line(top_of_win, b_lines - 2);
					currline = top_of_win;
					currpnt = 0;
					curr_window_line = 0;
					redraw_everything = TRUE;
					break;
				case KEY_PGDN:
				case CTRL('N'):
					top_of_win = forward_line(top_of_win, b_lines - 2);
					currline = top_of_win;
					currpnt = 0;
					curr_window_line = 0;
					redraw_everything = TRUE;
					break;
				case KEY_HOME:
				case CTRL('A'):
					currpnt = 0;
					break;
				case KEY_END:
				case CTRL('E'):
					currpnt = currline->memlen;
					break;
				case CTRL('R'):
#if 0
					backup_file(bakfile);
#endif
					msq_reply();
#if 0
					redraw_everything = TRUE;	/* lthuang */
#endif
					break;
				case CTRL('Q'):
					ansi_mode = TRUE;
					display_buffer();
					pressreturn();
					ansi_mode = FALSE;
					display_buffer();
					break;
				case CTRL('X'):
				case CTRL('W'):
					backup_file(bakfile);
					clear();
					foo = write_file(filename, saveheader, bname);
					if (foo == BACKUP_EDITING)
						return foo;
					else if (foo != KEEP_EDITING)
					{
						unlink(bakfile);
						return foo;
					}
					redraw_everything = TRUE;	/* lthuang */
					break;
				case '\r':
				case '\n':
					split(currline, currpnt, currpos);
					/* lthuang: reduce the times of backup */
					if (total_num_of_line % 7 == 0)
						backup_file(bakfile);
					break;
				case '\177':
				case CTRL('H'):
					if (currpnt == 0)
					{
						if (!currline->prev)
						{
							bell();
							break;
						}
						curr_window_line--;
						currline = currline->prev;
						currpnt = currline->memlen;
						currpos = currline->charlen;
						if (*killsp(currline->next->data) == '\0') {
							delete_line(currline->next);
							redraw_everything = TRUE;
						} else {
							join_currline();
						}
						if (curr_window_line == -1) {
							curr_window_line = 0;
							top_of_win = currline;
							rscroll();
						}
						break;
					}
					do{
						currpnt--;
					}while(currline->data[currpnt] & 0x80 && ~currline->data[currpnt] & 0x40);
					currpos -= utf8charwidth((unsigned char*)&currline->data[currpnt] );
					
					delete_char();
					break;
				case CTRL('D'):
					if (currline->memlen == currpnt)
						join_currline();
					else
						delete_char();
					break;
				case CTRL('Y'):
					currpnt = 0;
					currline->memlen = 0;
					delete_currline();
					break;
				case CTRL('K'):
					if (currline->memlen == 0)
						delete_currline();
					else if (currline->memlen == currpnt)
						join_currline();
					else
					{
						currline->memlen = currpnt;
						currline->data[currpnt] = '\0';
					}
					break;
				default:
					break;
				}
				break;
			}
		}
		if (curr_window_line == -1)
		{
			curr_window_line = 0;
			if (!top_of_win->prev)
			{
				indigestion(6);
				bell();
			}
			else
			{
				top_of_win = top_of_win->prev;
				rscroll();
			}
		}
		if (curr_window_line == t_lines - 1)
		{
			curr_window_line = t_lines - 2;
			if (!top_of_win->next)
			{
				indigestion(7);
				bell();
			}
			else
			{
				top_of_win = top_of_win->next;
				scroll();
			}
		}

		/* lthuang: 99/07 */
		if (currpnt - shift >= t_columns - 1)
		{
			shift = (currpnt / (t_columns - 1)) * (t_columns - 1) - 1;
			redraw_everything = TRUE;
		}
		else if (currpnt - shift < 0)
		{
			shift = 0;
			redraw_everything = TRUE;
		}

		if (redraw_everything)
		{
			display_buffer();
			redraw_everything = FALSE;
		}
		else
		{
			move(curr_window_line, 0);
			clrtoeol();	/* lthuang */
			vedit_outs(currline->data);
		}

		move(curr_window_line, currpos - shift);	/* lthuang: 99/07 */
	}
	if (uinfo.mode == POSTING || uinfo.mode == SMAIL)
		unlink(filename);
	return ABORT_EDITING;
}
