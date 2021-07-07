#include <ros/ros.h>
#include <std_msgs/String.h>
#include "take_photo.h"
#include "SocketMatTransmissionClient.h"

static CTakePhoto take_photo_script;

SocketMatTransmissionClient socketMat;

void KeywordCB(const std_msgs::String::ConstPtr &msg)
{
    //ROS_WARN("[home_script_KeywordCB] - %s",msg->data.c_str());
    string strListen = msg->data;
    take_photo_script.strListen = strListen;
}

// void KeywordCB(const std_msgs::String::ConstPtr & msg)
// {
//     //ROS_WARN("[take_photo_script_KeywordCB] - %s",msg->data.c_str());
//     string strListen = msg->data;
//     take_photo_script.strListen = strListen;
// }

void ProcColorCB(const sensor_msgs::ImageConstPtr& msg)
{
     //ROS_INFO("[ProcColorCB - ]...");
    if(take_photo_script.nCurActCode != ACT_REC_VIDEO && take_photo_script.nCurActCode != ACT_CAP_IMAGE )
        return;

    cv_bridge::CvImagePtr cv_ptr;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }

    cv::Mat image = cv_ptr->image;

    if( take_photo_script.nCurActCode == ACT_REC_VIDEO && take_photo_script.pVW != NULL )
    {
        ROS_INFO("[rec video frame = %d]...", take_photo_script.nVideoFrameCount);
        *(take_photo_script.pVW) << image;
        take_photo_script.nVideoFrameCount ++;
    }

    //image_pub.publish(cv_ptr->toImageMsg());
 
    if(take_photo_script.nCurActCode == ACT_CAP_IMAGE)
    {
        imwrite(take_photo_script.strImage,cv_ptr->image);
        cv::Size dsize = Size(640, 480);
        cv::Mat img2 = Mat(dsize, CV_8UC3);
        resize(image, img2, dsize);
        socketMat.transmit(img2);
        take_photo_script.nVideoFrameCount ++;
    }
}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "take_photo_script");
    ROS_INFO("[main] take_photo_script");
    if (socketMat.socketConnect("127.0.0.1", 6666) < 0)
	{
        printf("socket connect fail!\n");
		return 0;
	}
    // cv::VideoCapture capture(0);
    take_photo_script.Init();
    take_photo_script.Queue();
    take_photo_script.ShowActs();

    ros::NodeHandle n;
    ros::Subscriber sub_sr = n.subscribe("/xfyun/iat", 10, KeywordCB);
    //ros::Subscriber rgb_sub = n.subscribe("/kinect2/qhd/image_color", 10, ProcColorCB);
    ros::Subscriber rgb_sub = n.subscribe("/kinect2/qhd/image_color", 10, ProcColorCB);

    ros::Rate r(10);
    ros::spinOnce();
    while (ros::ok())
    {
        take_photo_script.Main();
        ros::spinOnce();
        r.sleep();
    }
    socketMat.socketDisconnect();
    return 0;
}
