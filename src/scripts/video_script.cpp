#include "video_script.h"

CVideoScript::CVideoScript()
{

}

CVideoScript::~CVideoScript()
{

}

void CVideoScript::Queue()
{

    stAct newAct;

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "拍摄视频 即将开始, 请说开始";
    newAct.nDuration = 6;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "开始";   
    newAct.nDuration = 3;    //识别时长
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的,即将开始拍摄,五,四,三,二,一";
    newAct.nDuration = 8;
    arAct.push_back(newAct);

    newAct.nAct = ACT_REC_VIDEO;
    newAct.strTarget = "/home/lct19/catkin_ws/src/wpb_home_apps/tools/record.avi";    //录制视频文件名
    newAct.nDuration = 30;   //录制时长(单位:秒)
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好了,我已经录好内容,现在开始播放";
    newAct.nDuration = 6;
    arAct.push_back(newAct);

    newAct.nAct = ACT_PLAY_VIDEO;
    newAct.strTarget = "/home/lct19/catkin_ws/src/wpb_home_apps/tools/record.avi";    //播放视频文件名
    newAct.nLoopPlay = 2;   //循环播放次数
    newAct.nDuration = 30;   //持续时间(单位:秒)
    arAct.push_back(newAct);

}
