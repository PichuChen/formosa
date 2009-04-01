/*
 * ��ܩҦ��ݪO�M��
 */

#include "bbs.h"


int
board_cmp (a, b)
     struct boardheader *a, *b;
{
	return (strcasecmp (a->filename, b->filename));
}

int
print_title ()
{
	printf (
	      "     �ݪO�W��     �O�D                     ���O   ����ԭz\n"
		       "---------------------------------------------------------------------------\n");
}


int
print_board (bhp)
     BOARDHEADER *bhp;
{
	printf ("%d\t%ld\t%s%s\t%s\t%s\t%s%s\n",
		bhp->bid,
		bhp->ctime,
		(bhp->brdtype & BRD_PRIVATE) ? "#" : "",
		bhp->filename,
		(bhp->owner[0] > ' ') ? bhp->owner : "�L�O�D",
		(bhp->brdtype & BRD_NEWS) ? "��" : "����",
		bhp->title,(bhp->passwd[0] != '\0') ? "[�K�X]" : "");

}



int
main (argc, argv)
     int argc;
     char *argv[];
{
	int inf;
	BOARDHEADER bh;


	if (argc == 2)
	{
		if ((inf = open (argv[1], O_RDONLY)) > 0)
		{
			print_title ();
			while (read (inf, &bh, BH_SIZE) == BH_SIZE)
			{
				print_board (&bh);
			}
			close (inf);
		}
	}
	else
	{
		print_title ();
		resolve_brdshm ();
		apply_brdshm (print_board);
	}
}
