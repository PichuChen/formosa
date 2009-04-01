
#include "bbs.h"

#define VLEN 41

typedef struct
{
	int order;		/* order */
	char dirname[12];	/* directory (M.XXXXXXXXX.A)  */
	char title[VLEN];	/* title */
	char TotalCandidate;	/* total candidates */
	char MaxTicket;		/* max tickets */
	time_t StartTime;	/* �}�l�벼�ɶ� */
	time_t EndTime;		/* �벼�I��ɶ� */
	char AllowIP[20];	/* �ѥ[�벼���W���ӷ����� */
	unsigned int userlevel;	/* �ѥ[�벼�����ŭ���� */
}
voteheader;


void
main (argc, argv)
     int argc;
     char *argv[];
{
	int fd;
	voteheader vote;
	int num_of_vote;

	if (argc != 2)
	{
		printf ("usage: %s [filename]\n", argv[0]);
		exit (1);
	}

	if ((fd = open (argv[1], O_RDONLY)) < 0)
	{
		printf ("cannot open %s\n", argv[1]);
		exit (1);
	}

	read (fd, &num_of_vote, sizeof (int));
	printf ("num_of_vote: %d\n", num_of_vote);

	while (read (fd, &vote, sizeof (vote)) == sizeof (vote))
	{
		printf ("order    : %d\n", vote.order);
		printf ("dirname  : %s\n", vote.dirname);
		printf ("title    : %s\n", vote.title);
		printf ("TotalCand: %d\n", vote.TotalCandidate);
		printf ("MaxTicket: %d\n", vote.MaxTicket);
		printf ("StartTime: %s", ctime (&vote.StartTime));
		printf ("EndTime  : %s", ctime (&vote.EndTime));
	}
	close (fd);
}
