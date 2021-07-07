#include "SocketMatTransmissionClient.h"
 

int main()
{
	SocketMatTransmissionClient socketMat;
	if (socketMat.socketConnect("127.0.0.1", 6666) < 0)
	{
		return 0;
	}
	
	// cv::VideoCapture capture(0);
	cv::Mat image = imread("/home/pzs/catkin_ws/Image/map.jpg");
	cv::Size dsize = Size(640, 480);
	cv::Mat img2 = Mat(dsize, CV_8UC3);
	resize(image, img2, dsize);
	while (1)
	{
		// if (!capture.isOpened())
		// 	return 0;
 
		// capture >> image;
 
		if (img2.empty())
			return 0;
 
		socketMat.transmit(img2);
	}
 
	socketMat.socketDisconnect();
	return 0;
}
