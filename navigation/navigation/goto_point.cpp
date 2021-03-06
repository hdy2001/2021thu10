#include "goto_point.h"
CGotoPoint::CGotoPoint(){

}

CGotoPoint::~CGotoPoint(){

}

void CGotoPoint::SpeakQueue(){
    stAct newAct;
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "!机器人小智整装待发，请说一个导航点的名字。";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);
}

void CGotoPoint::SpeakGoalQueue(std_msgs::String &voice_cmd){
    stAct newAct;
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "!我将前往 "+ voice_cmd.data+" ，请问您需要我去做什么？";
    newAct.nDuration = 8;
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);
}

void CGotoPoint::ActQueue(const std::string GoalName, const std::string ActName, const std::string StartName){
    stAct newAct;
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "!我将前往 "+ GoalName +" 去进行" + ActName + "!";
    newAct.nDuration = 8;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = GoalName;
    arAct.push_back(newAct);
    // add your act code here and modify ActQueueLength 
    // like this
    if(ActName == "播放"){
        newAct.nAct = ACT_PLAY_VIDEO;
        newAct.strTarget = VideoPath + "notice.mp4";
        newAct.nLoopPlay = 1;
        newAct.nDuration = 7;
        arAct.push_back(newAct);
    }
    else if(ActName == "抓取"){
        //wait for implement
    }
    else if(ActName == "拍照"){
        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "1.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.0;
        newAct.fLinear_y = 0.0;
        newAct.fAngular_z = 1.57;
        arAct.push_back(newAct);

        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "2.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.0;
        newAct.fLinear_y = 0.0;
        newAct.fAngular_z = 1.57;
        arAct.push_back(newAct);

        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "3.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.0;
        newAct.fLinear_y = 0.0;
        newAct.fAngular_z = 1.57;
        arAct.push_back(newAct);

        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "4.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.0;
        newAct.fLinear_y = 0.0;
        newAct.fAngular_z = 0.0;
        arAct.push_back(newAct);
    }
    else if(ActName == "录制视频"){
        newAct.nAct = ACT_REC_VIDEO;
        newAct.nDuration = 5;
        newAct.strTarget = VideoPath + "Record.avi";
        arAct.push_back(newAct);
    }
    else if(ActName == "三维重建"){
        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "1.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.5;
        newAct.fLinear_y = 0.5;
        newAct.fAngular_z = 1.57;
        arAct.push_back(newAct);

        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "2.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.5;
        newAct.fLinear_y = 0.5;
        newAct.fAngular_z = 1.57;
        arAct.push_back(newAct);

        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "3.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.5;
        newAct.fLinear_y = 0.5;
        newAct.fAngular_z = 1.57;
        arAct.push_back(newAct);

        newAct.nAct = ACT_CAP_IMAGE;
        newAct.strTarget = ImagePath + "4.jpg";
        arAct.push_back(newAct);

        newAct.nAct = ACT_MOVE;
        newAct.fLinear_x = 0.0;
        newAct.fLinear_y = 0.0;
        newAct.fAngular_z = 0.0;
        arAct.push_back(newAct);
    }
    else{
        newAct.nAct = ACT_SPEAK;
        newAct.strTarget = "对不起，我不会执行这个动作！";
        newAct.nDuration = 5;
        arAct.push_back(newAct);
    }
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "完成任务，准备返回！";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = StartName;
    // newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "主人，我完成任务啦！";
    newAct.nDuration = 5;
    arAct.push_back(newAct);
}