/*M///
//
//  基于OpenCV和Socket的图像传输（接收）
//	
//	By 彭曾 , at CUST, 2016.08.07 
//
//	website: www.pengz0807.com  email: pengz0807@163.com 
//	
//M*/
 
 
#include "SocketMatTransmissionServer.h"
 
SocketMatTransmissionServer::SocketMatTransmissionServer(void)
{
}
 
 
SocketMatTransmissionServer::~SocketMatTransmissionServer(void)
{
}
 
 
int SocketMatTransmissionServer::socketConnect(int PORT)
{
	int server_sockfd = socket(AF_INET,SOCK_STREAM, 0);
 
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(PORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 
	if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
	{
		perror("bind");
		return -1;
	}
 
	if(listen(server_sockfd,5) == -1)
	{
		perror("listen");
		return -1;
	}
 
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
 
	sockConn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
	if(sockConn<0)
	{
		perror("connect");
		return -1;
	}
	else
	{
		printf("connect successful!\n");
		return 1;
	}
	
	close(server_sockfd);
}
 
 
void SocketMatTransmissionServer::socketDisconnect(void)
{
	close(sockConn);
}
 
int SocketMatTransmissionServer::receive(cv::Mat& image)
{
	int returnflag = 0;
	cv::Mat img(IMG_HEIGHT, IMG_WIDTH, CV_8UC3, cv::Scalar(0));
	needRecv = sizeof(recvBuf);
	count = 0;
	memset(&data,0,sizeof(data));
 
	for (int i = 0; i < PACKAGE_NUM; i++)
	{
		int pos = 0;
		int len0 = 0;
 
		while (pos < needRecv)
		{
			len0 = recv(sockConn, (char*)(&data) + pos, needRecv - pos, 0);
			if (len0 < 0)
			{
				printf("Server Recieve Data Failed!\n");
				break;
			}
			pos += len0;
		}
 
		count = count + data.flag;
 
		int num1 = IMG_HEIGHT / PACKAGE_NUM * i;
		for (int j = 0; j < IMG_HEIGHT / PACKAGE_NUM; j++)
		{
			int num2 = j * IMG_WIDTH * 3;
			uchar* ucdata = img.ptr<uchar>(j + num1);
			for (int k = 0; k < IMG_WIDTH * 3; k++)
			{
				ucdata[k] = data.buf[num2 + k];
			}
		}
 
		if (data.flag == 2)
		{
			if (count == PACKAGE_NUM + 1)
			{
				image = img;
				returnflag = 1;
				count = 0;
			}
			else
			{
				count = 0;
				i = 0;
			}
		}
	}
	if(returnflag == 1)
		return 1;
	else
		return -1;
}
