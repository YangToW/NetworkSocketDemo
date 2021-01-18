/*
    udp套接字编程客户端代码
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

const int BUFLEN 2048
const int MSG_NUM 5
const int SERVICE_PORT 6240
const char * const SERVICE_IP "127.0.0.1"

int main(int argc, char **argv)
{
    // 创建一个套接字，并检测是否创建成功
    int sockCli = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockCli == -1)
    {
        perror("cannot create socket");
		exit(0);
    }
	printf("created socket, fd: %d\n", fd);
	// 命名套接字，在客户端这是非必须的
	// 对套接字命名的意思是指将该套接字关联一个IP地址和端口号，可以使用系统调用bind来实现。
	struct sockaddr_in cliAddr;
	memset((void *)&cliAddr, 0, sizeof(cliAddr));
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_port = htons(0); // 通常客户端无须指定特定的端口，由操作系统分配
	cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// cliAddr.sin_addr.s_addr = inet_addr("127.0.0.1")
	
	if (bind(sockCli，(struct sockaddr *)&cliAddr, sizeof(cliAddr)) < 0)
	{
		perror("bind failed");
		exit(0);
	}

	// 构造服务器的地址
	struct sockaddr_in servAddr;
	memset((char *)&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVICE_PORT);
	if (!inet_aton(SERVICE_IP, &servAddr.sin_addr))
	{
		perror("bad address");
	}

	// 客户向服务器发送消息
	char buf[BUFLEN];
	int slen = sizeof(servAddr);
	for (i = 0; i < MSG_NUM; i++)
	{
		printf("Sending packet %d to %s port %d\n", i, SERVICE_IP, SERVICE_PORT);
		sprintf(buf, "This is packet %d", i);
		sendLen = send(sockCli, buf, strlen(buf), 0, (struct sockaddr *)&servAddr, slen);
		if (sendLen == -1)
		{
			perror("sendto");
		}
	}	
	close(sockCli);
	exit(0);
}
