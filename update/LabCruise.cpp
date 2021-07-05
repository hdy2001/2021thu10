#include "LabCruise.h"
LabCruise::LabCruise(){

}

LabCruise::~LabCruise(){

}

void LabCruise::TempQueue(int AmbTemp, int ObjTemp){
    stAct newAct;
    std::string amb, obj;
    std::stringstream ss;
    ss<<AmbTemp;
    ss>>amb;
    ss<<ObjTemp;
    ss>>obj;
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "环境温度是：" + amb + "您的体温是：" + obj;
    newAct.nDuration = 10;
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);
}

void LabCruise::SpeakQueue(){
    stAct newAct;
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "您好, 我是自动化系迎新机器人小智，很高兴认识您。";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "共抗疫情，进入实验室请先测温";
    newAct.nDuration = 5;
    arAct.push_back(newAct);
}

void LabCruise::ChatQueue(const int KeyWordIndex){
    stAct newAct;

    switch(KeyWordIndex){
        case 0:{
            newAct.nAct = ACT_SPEAK;
            newAct.strTarget = "您好, 我是自动化系迎新机器人小智，很高兴认识您。";
            newAct.nDuration = 5;
            arAct.push_back(newAct);
            break;
        }
        case 1:{
            newAct.nAct = ACT_SPEAK;
            newAct.strTarget = "我的功能可多了，我可以带您参观自动化系的实验室。我还是老师的好帮手，"
            "可以帮老师到其他房间抓取物品，拍照，录制视频，播放通知，我还会用NERF算法，进行三维重建，怎么样，是不是很炫酷！";
            newAct.nDuration = 20;
            arAct.push_back(newAct);
            break;
        }
        case 2:{
            newAct.nAct = ACT_SPEAK;
            newAct.strTarget = "我的功能可多了，我可以带您参观自动化系的实验室。我还是老师的好帮手，"
            "可以帮老师到其他房间抓取物品，拍照，录制视频，播放通知，我还会用NERF算法，进行三维重建，怎么样，是不是很炫酷！";
            newAct.nDuration = 20;
            arAct.push_back(newAct);
            break;
        }
        case 3:{
            newAct.nAct = ACT_SPEAK;
            newAct.strTarget = "我的家在自动化系519实验室，如果我没有电了，记得把我送回家。";
            newAct.nDuration = 6;
            arAct.push_back(newAct);
            break;
        }
        default: break;
    }
    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);
}


void LabCruise::CruiseQueue(){
    stAct newAct;
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "自动导游即将开始，我将带领您参观自动化系部分实验室！";
    newAct.nDuration = 8;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "519";
    arAct.push_back(newAct);

    newAct.nAct = ACT_PLAY_VIDEO;
    newAct.strTarget = "/home/pzs/519.mp3";
    newAct.nLoopPlay = 1;
    newAct.nDuration = 22;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "520";
    arAct.push_back(newAct);

    newAct.nAct = ACT_PLAY_VIDEO;
    newAct.strTarget = "/home/pzs/520.mp3";
    newAct.nLoopPlay = 1;
    newAct.nDuration = 20;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "521";
    arAct.push_back(newAct);

    newAct.nAct = ACT_PLAY_VIDEO;
    newAct.strTarget = "/home/pzs/521.mp3";
    newAct.nLoopPlay = 1;
    newAct.nDuration = 20;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "自动导游即将结束，自动化系欢迎您的再次光临！";
    newAct.nDuration = 8;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "0";
    arAct.push_back(newAct);
}