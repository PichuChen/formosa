/* �o�� program(Client��) �O�ѨϥΪ̧�������q�H�b�����K�X */

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<fcntl.h>
#include<syslog.h>

void readResult();
void chkpass();

#define passwdlen 5
#define myProtocol 10

#define myidno "000310"   /* �o�OBBS �ϥΪ̪��q�H�N�X  */

#define SERV_TCP_PORT 3000
#define SERV_HOST_ADDR "163.15.251.10"
#define NTSE_TCP_PORT 7000
#define NTSE_HOST_ADDR "163.15.251.11"


void main()
{
	int sockfd;
	long serno;
	char se1[8];
	char oldpass[5],newpass1[5],newpass2[5];
	struct sockaddr_in serv_addr;

	int on=1;

	bzero((char *) &serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(SERV_HOST_ADDR);
	serv_addr.sin_port=htons(SERV_TCP_PORT);

	if ((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		exit(1);
		perror("client:");
	}

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
	{
		exit(1);
		perror("client:");
	}

	if (write(sockfd,myidno,strlen(myidno)+1)<0)  /* send my id */
	{
		printf("���K�X�o�Ϳ��~!!\n");
		close(sockfd);
		exit(1);
	}

	printf("�п�J�A���±K�X�]�|�X�^: ");
	gets(oldpass);

	if (write(sockfd,oldpass,strlen(oldpass)+1)<0)  /* send my id */
	{
		printf("���K�X�o�Ϳ��~!!\n");
		close(sockfd);
		exit(1);
	}

/* chkpass(sockfd); */
/*�ˬd�±K�X�O�_���T�� ,�����B�Ʊ檽���bBBS�ݤ��N�n, �ҥH������chkpass */

	printf("�п�J�A���s�K�X�]�|�X�^: ");
	gets(newpass1);

	while (strlen(newpass1)!=4)
	{
		printf("�s�K�X�������|�X !!\n");
	printf("�п�J�A���s�K�X�]�|�X�^: ");
	gets(newpass1);
	}

	printf("�A�T�{�@���s�K�X�]�|�X�^: ");
	gets(newpass2);

	if (ChangeNTPass(myidno,newpass1)!=1)
	{
		printf("���K�X�o�Ϳ��~(NT)!! \n");
		close(sockfd);
		exit(1);
	}

	if ( strcmp(newpass1,newpass2) != 0 )
	{
		printf("\n�⦸��J���s�K�X���P !\n");
		close(sockfd);
		exit(1);
	}


	if (write(sockfd,newpass1,strlen(newpass1))<0)
	{
		printf("���K�X�o�Ϳ��~(1)!! \n");
		close(sockfd);
		exit(1);
	}

	readResult(sockfd);
	close(sockfd);
	exit(1);
}


void chkpass(fd)
int fd;
{
	char ifsame[10];

	if (read(fd,ifsame,sizeof(ifsame))<0)
	{
		printf("���K�X�o�Ϳ��~!!\n");
		close(fd);
		exit(0);
	}

	if (strcmp("NO",ifsame)==0)
	{
		printf("��J�K�X���~!!\n");
		close(fd);
		exit(1);
	}

	if(strcmp("error",ifsame)==0)
	{
		printf("���K�X�o�Ϳ��~!!\n");
		close(fd);
		exit(1);
	}
}


void readResult(fd)
int fd;
{
	char Result[myProtocol];

	if ((read(fd,Result,sizeof(Result)))<0)
	{
		printf("���K�X�o�Ϳ��~(2)!!\n");
		exit(0);
	}

	if (strcmp("error",Result)==0)
		printf("���K�X�o�Ϳ��~(3)!!\n");
	else if (strcmp("good",Result)==0)
		printf("���K�X����!!\n");
}


/******* Send ID , password to NT Server for change *********/
int ChangeNTPass(idno,newpass)
char *idno,*newpass;

{
	int NTsockfd;
	struct sockaddr_in NTserv_addr;
	char Message[50];

	int on=1;

	bzero((char *) &NTserv_addr,sizeof(NTserv_addr));
	NTserv_addr.sin_family=AF_INET;
	NTserv_addr.sin_addr.s_addr=inet_addr(NTSE_HOST_ADDR);
	NTserv_addr.sin_port=htons(NTSE_TCP_PORT);

	if ((NTsockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		close(NTsockfd);
		return 0;
	}

	if (connect(NTsockfd,(struct sockaddr *) &NTserv_addr,sizeof(NTserv_addr))<0)
	{
		close(NTsockfd);
		return 0;
	}

	strcpy(Message,idno);
	strcat(Message," " );
	strcat(Message,newpass);


	if (write(NTsockfd,Message,strlen(Message)+1)<0)
	{
		close(NTsockfd);
		return 0;
	}
	else
	{
		close(NTsockfd);
		return 1;
	}
}
