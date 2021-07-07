/*M///
//
//  基于OpenCV和Socket的图像传输（接收）
//	
//	By 彭曾 , at CUST, 2016.08.07
//
//	website: www.pengz0807.com  email: pengz0807@163.com 
//	
//M*/
 
#ifndef __SOCKETMATTRANSMISSIONSEVER_H__
#define __SOCKETMATTRANSMISSIONSEVER_H__
 
#include "opencv2/opencv.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
using namespace cv;
 
#define PACKAGE_NUM 2
 
#define IMG_WIDTH 640
#define IMG_HEIGHT 480
 
#define BLOCKSIZE IMG_WIDTH*IMG_HEIGHT*3/PACKAGE_NUM
 
struct recvBuf
{
	char buf[BLOCKSIZE];
	int flag;
};
 
 
class SocketMatTransmissionServer
{
public:
	SocketMatTransmissionServer(void);
	~SocketMatTransmissionServer(void);
	int sockConn;
private:
	struct recvBuf data;
 
	int needRecv;
	int count;
 
public:
 
	// 打开socket连接
	// params :	PORT	传输端口
	// return : -1		连接失败
	//			1		连接成功
	int socketConnect(int PORT);
 
 
	// 传输图像
	// params : image	待接收图像
	//		image	待接收图像
	// return : -1		接收失败
	//			1		接收成功
	int receive(cv::Mat& image);
 
 
	// 断开socket连接
	void socketDisconnect(void);
};
 
#endif
