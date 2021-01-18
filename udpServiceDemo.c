#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

const int BUFSIZE = 1024;
const int SERVICE_PORT = 6240;

int main(int argc, char **argv)
{
	// 创建套接字
	int sockServ = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockServ < 0)
	{
		perror("cannot create socket\n");
		exit(0);
	}
	struct sockaddr_in servAddr;
	memset((void *)&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVICE_PORT);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockServ, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
	{
		perror("bind failed");
		exit(0);
	}

	char buf[BUFSIZE];
	int recvLen;
	struct sockaddr_in cliAddr;
	socklen_t addrLen = sizeof(cliAddr);
	while (1)
	{
		printf("waiting on port %d\n", SERVICE_PORT);
		recvLen = recvfrom(sockServ, buf, BUFSIZE, 0, (struct sockaddr *)&cliAddr, &addrLen);
		printf("received %d bytes\n", recvLen);
		if (recvLen > 0)
		{
			buf[recvLen] = 0;
			printf("received message: \"%s\"\n", buf);
		}
	}
}
