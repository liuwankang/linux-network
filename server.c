#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<arpa/inet.h>
#include<netinet/in.h>


#define BUFF_LEN  1000
#define SERVER_PORT 10010

void fun1(int fd)
{
    int readlen = 0;
    char BUFF[BUFF_LEN + 1];
	memset(BUFF, 0, sizeof(BUFF));
	for(;;)
	{
		printf("--------------ready-------- \n");
		readlen = read(fd, BUFF, BUFF_LEN);
		if(readlen == 0)
            continue;
		else if(readlen == -1)
		{
			if(EINTR == errno || EAGAIN == errno)
			{
				continue;
			}
			else
			{
				printf("connet error\n");
				close(fd);
				break;
			}
		}
		printf("client %s\n", BUFF);
	}
	return;

}

int main()
{

	int socketfd, connetfd;
	int iRet = 0, iLen = 0;
	struct sockaddr_in stSock, stAcceptSock;
	memset(&stSock, 0, sizeof(stSock));
    memset(&stAcceptSock, 0, sizeof(stSock));
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(0 >=  socket)
		return -1;
	stSock.sin_family = AF_INET;
	stSock.sin_port = htons(SERVER_PORT);
	stSock.sin_addr.s_addr = inet_addr("127.0.0.1");
	iRet = bind(socketfd, (struct sockaddr *)&stSock,sizeof(stSock));
	if(iRet < 0)
	{
		printf("Bind error\n");
		return -1;
	}
	iRet = listen(socketfd, 2);
	if(iRet < 0)
	{
		printf("listening error\n");
		return -1;
	}
	printf("Listening...\n");
	connetfd = accept(socketfd, (struct sockaddr *)&stAcceptSock, &iLen);
	if(connetfd > 0)
	{
		printf("accept success\n");
		fun1(connetfd);
	}
	else
	{
		return -1;
	}
	return 0;
}



