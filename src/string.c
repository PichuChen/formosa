#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "ansi.h"
#include "cmsys.h"
#include "tsbbs.h"

#define CHAR_LOWER(c)  ((c >= 'A' && c <= 'Z') ? c|32 : c)
/* ----------------------------------------------------- */
/* 字串轉換檢查函數                                      */
/* ----------------------------------------------------- */
/**
 * 將字串 s 轉為小寫存回 t
 * @param t allocated char array
 * @param s
 */
void str_lower(char *t, const char *s)
{
    register unsigned char ch;

    do {
	ch = *s++;
	*t++ = CHAR_LOWER(ch);
    } while (ch);
}

/**
 * 移除字串 buf 後端多餘的空白。
 * @param buf
 */
void trim(char *buf)
{				/* remove trailing space */
    char           *p = buf;

    while (*p)
	p++;
    while (--p >= buf) {
	if (*p == ' ')
	    *p = '\0';
	else
	    break;
    }
}

/**
 * 移除 src 的 '\n' 並改成 '\0'
 * @param src
 */
void chomp(char *src)
{
    while(*src){
	if (*src == '\n')
	    *src = 0;
	else
	    src++;
    }
}

/* ----------------------------------------------------- */
/* ANSI 處理函數                                         */
/* ----------------------------------------------------- */
int strip_blank(char *cbuf, char *buf)
{
    for (; *buf; buf++)
	if (*buf != ' ')
	    *cbuf++ = *buf;
    *cbuf = 0;
    return 0;
}

static const char EscapeFlag[] = {
    /*  0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 10 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0,
    /* 20 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 30 */ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, /* 0~9 ;= */
    /* 40 */ 0, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, /* ABCDHIJK */
    /* 50 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 60 */ 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 0, 0, 2, 2, 0, 0, /* fhlm */
    /* 70 */ 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* su */
    /* 80 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 90 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* A0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* B0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* C0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* D0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* E0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* F0 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
#define isEscapeParam(X) (EscapeFlag[(int)(X)] & 1)
#define isEscapeCommand(X) (EscapeFlag[(int)(X)] & 2)

#if 0
/**
 * 根據 mode 來 strip 字串 src，並把結果存到 dst
 * @param dst
 * @param src (if NULL then only return length)
 * @param mode enum {STRIP_ALL = 0, ONLY_COLOR, NO_RELOAD};
 *             STRIP_ALL:  全部吃掉
 *             ONLY_COLOR: 只留跟顏色有關的 (ESC[*m)
 *             NO_RELOAD:  只留上面認識的(移位+色彩)
 * @return strip 後的長度
 */
int strip_ansi_str(char *dst, const char *src, enum STRIP_FLAG mode)
{
    register int    count = 0;

    for(; *src; ++src)
	if( *src != ESC_CHR ){
	    if( dst )
		*dst++ = *src;
	    ++count;
	}else{
	    const char* p = src + 1;
	    if( *p != '[' ){
		++src;
		if(*src=='\0') break;
		continue;
	    }
	    while(isEscapeParam(*++p));
	    if( (mode == NO_RELOAD && isEscapeCommand(*p)) ||
		(mode == ONLY_COLOR && *p == 'm' )){
		register int len = p - src + 1;
		if( dst ){
		    memmove(dst, src, len);
		    dst += len;
		}
		count += len;
	    }
	    src = p;
	    if(*src=='\0') break;
	}
    if( dst )
	*dst = 0;
    return count;
}
#endif

/**
 * query the offset of nth non-ANSI element in s
 * if string is less then nth, return missing blanks in negative value.
 */
int strat_ansi(int count, const char *s)
{
    register int mode = 0;
    const char *os = s;

    for (; count > 0 && *s; ++s)
    {
	// 0 - no ansi, 1 - [, 2 - param+cmd
	switch (mode)
	{
	    case 0:
		if (*s == ESC_CHR)
		    mode = 1;
		else
		    count --;
		break;

	    case 1:
		if (*s == '[')
		    mode = 2;
		else
		    mode = 0; // unknown command
		break;

	    case 2:
		if (isEscapeParam(*s))
		    continue;
		else if (isEscapeCommand(*s))
		    mode = 0;
		else
		    mode = 0;
		break;
	}
    }
    if (count > 0)
	return -count;
    return s - os;
}

int strlen_noansi(const char *s)
{
    // XXX this is almost identical to
    // strip_ansi(NULL, s, STRIP_ALL)
    register int count = 0, mode = 0;

    if (!s || !*s)
	return 0;

    for (; *s; ++s)
    {
	// 0 - no ansi, 1 - [, 2 - param+cmd
	switch (mode)
	{
	    case 0:
		if (*s == ESC_CHR)
		    mode = 1;
		else
		    count ++;
		break;

	    case 1:
		if (*s == '[')
		    mode = 2;
		else
		    mode = 0; // unknown command
		break;

	    case 2:
		if (isEscapeParam(*s))
		    continue;
		else if (isEscapeCommand(*s))
		    mode = 0;
		else
		    mode = 0;
		break;
	}
    }
    return count;
}

/* ----------------------------------------------------- */
/* DBCS 處理函數                                         */
/* ----------------------------------------------------- */

void strip_nonebig5(unsigned char *str, int maxlen)
{
  int i;
  int len=0;
  for(i=0;i<maxlen && str[i];i++) {
    if(32<=str[i] && str[i]<128)
      str[len++]=str[i];
    else if(str[i]==255) {
      if(i+1<maxlen)
	if(251<=str[i+1] && str[i+1]<=254) {
	  i++;
	  if(i+1<maxlen && str[i+1])
	    i++;
	}
      continue;
    } else if(str[i]&0x80) {
      if(i+1<maxlen)
	if((0x40<=str[i+1] && str[i+1]<=0x7e) ||
	   (0xa1<=str[i+1] && str[i+1]<=0xfe)) {
	  str[len++]=str[i];
	  str[len++]=str[i+1];
	  i++;
	}
    }
  }
  if(len<maxlen)
    str[len]='\0';
}

/**
 * DBCS_RemoveIntrEscape(buf, len): 去除 DBCS 一字雙色字。
 * (deprecated)
 */
int DBCS_RemoveIntrEscape(unsigned char *buf, int *len)
{
    register int isInAnsi = 0, isInDBCS = 0;
    int l = 0, i = 0, oldl, iansi = 0;

    if (len) l = *len; else l = strlen((const char*)buf);
    oldl = l;

    for (i = 0; i < l; i++)
    {
	if (buf[i] == ESC_CHR && !isInAnsi)
	{
	    // new escape
	    isInAnsi = 1;
	    iansi = i;
	    continue;
	}

	// character
	if (isInAnsi)
	{
	    // closing ANSI section?
	    switch (isInAnsi)
	    {
	    case 1: // normal ANSI
		if (buf[i] == '[')
		    isInAnsi = 2;
		else
		    isInAnsi = 0; // unknown command
		break;

	    case 2:
		if (isEscapeParam(buf[i]))
		    break;
		else
		    isInAnsi = 0;
		break;
	    }
	    if (isInAnsi == 0 && isInDBCS && i+1 < l)
	    {
		// interupting ANSI closed, let's modify the string
		int sz = i + 1 - iansi; // size to move
		memmove(buf+iansi, buf+i+1, l-i-1);
		l -= sz;
		i = iansi-1; // for the ++ in loop
	    }
	} else if (isInDBCS) {
	    // not ANSI but in DBCS. finished one char.
	    isInDBCS = 0;
	} else if (buf[i] >= 0x80) {
	    // DBCS lead.
	    isInDBCS = 1;
	} else {
	    // normal character.
	}
    }

    if(len) *len = l;
    return (oldl != l) ? 1 : 0;
}

/**
 * DBCS_Status(dbcstr, pos): 取得字串中指定位置的 DBCS 狀態。
 */
int DBCS_Status(const char *dbcstr, int pos)
{
    int sts = DBCS_ASCII;
    const unsigned char *s = (const unsigned char*)dbcstr;

    while(pos >= 0)
    {
	if(sts == DBCS_LEADING)
	    sts = DBCS_TRAILING;
	else if (*s >= 0x80)
	{
	    sts = DBCS_LEADING;
	} else {
	    sts = DBCS_ASCII;
	}
	s++, pos--;
    }
    return sts;
}

/**
 * DBCS_strcasestr(pool, ptr): 在字串 pool 中尋找 ptr (只忽略英文大小寫)
 */
char *DBCS_strcasestr(const char* pool, const char *ptr)
{
    int i = 0, i2 = 0, found = 0,
        szpool = strlen(pool),
        szptr  = strlen(ptr);

    for (i = 0; i <= szpool-szptr; i++)
    {
        found = 1;

        // compare szpool[i..szptr] with ptr
        for (i2 = 0; i2 < szptr; i2++)
        {
            if (pool[i + i2] > 0)
            {
                // ascii
                if (ptr[i2] < 0 ||
		    tolower(ptr[i2]) != tolower(pool[i+i2]))
                {
		    // printf("break on ascii (i=%d, i2=%d).\n", i, i2);
                    found = 0;
                    break;
                }
            } else {
                // non-ascii
                if (ptr[i2]   != pool[i+i2] ||
                    ptr[i2+1] != pool[i+i2+1])
                {
		    // printf("break on non-ascii (i=%d, i2=%d).\n", i, i2);
                    found = 0;
                    break;
                }
		i2 ++;
            }
        }

        if (found)
	    return (char *)pool+i;

        // next iteration: if target is DBCS, skip one more byte.
        if (pool[i] < 0)
            i++;
    }
    return NULL;
}

/* ----------------------------------------------------- */
/* 字串檢查函數：英文、數字、檔名、E-mail address        */
/* ----------------------------------------------------- */

int invalid_pname(const char *str)
{
    const char           *p1, *p2, *p3;

    p1 = str;
    while (*p1) {
	if (!(p2 = strchr(p1, '/')))
	    p2 = str + strlen(str);
	if (p1 + 1 > p2 || p1 + strspn(p1, ".") == p2) /* 不允許用 / 開頭, 或是 // 之間只有 . */
	    return 1;
	for (p3 = p1; p3 < p2; p3++)
	    if (!isalnum(*p3) && !strchr("@[]-._", *p3)) /* 只允許 alnum 或這些符號 */
		return 1;
	p1 = p2 + (*p2 ? 1 : 0);
    }
    return 0;
}

/*
 * return	1	if /^[0-9]+$/
 * 		0	else, 含空字串
 */
int is_number(const char *p)
{
    if (*p == '\0')
	return 0;

    for(; *p; p++) {
	if (*p < '0' || '9' < *p)
	    return 0;
    }
    return 1;
}
