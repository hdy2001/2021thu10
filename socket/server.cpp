#include "SocketMatTransmissionServer.h"
 
int main()
{
	SocketMatTransmissionServer socketMat;
	if (socketMat.socketConnect(6666) < 0)
	{
		return 0;
	}
 
	cv::Mat image;
	while (1)
	{
		if(socketMat.receive(image) > 0)
		{
			printf("recv image!\n");
			cv::imshow("",image);
			cv::waitKey(30);
		}
	}
 
	socketMat.socketDisconnect();
	return 0;
}
