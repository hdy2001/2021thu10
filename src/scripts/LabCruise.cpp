#include "LabCruise.h"
LabCruise::LabCruise(){

}

LabCruise::~LabCruise(){

}

void LabCruise::TempQueue(float AmbTemp, float ObjTemp){
    stAct newAct;
    std::string Amb, Obj;
    std::stringstream ssAmb, ssObj;
    ssAmb<<AmbTemp;
    ssAmb>>Amb;
    // amb.erase(4);
    ssObj<<ObjTemp;
    ssObj>>Obj;
    // obj.erase(4);

    if( ObjTemp <= 37.3){
        newAct.nAct = ACT_SPEAK;
        newAct.strTarget = "环境温度是：" + Amb + "度, 您的体温是：" + Obj + "度, 体温正常！";
        newAct.nDuration = 10;
        arAct.push_back(newAct);
    }
    else{
        newAct.nAct = ACT_SPEAK;
        newAct.strTarget = "您的体温是：" + Obj + "度, 体温异常！";
        newAct.nDuration = 10;
        arAct.push_back(newAct);

        newAct.nAct = ACT_PLAY_VIDEO;
        newAct.strTarget = AudioPath + "jbVoice.mp3";
        newAct.nDuration = 1;
        arAct.push_back(newAct);
    }
    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);
}

void LabCruise::SpeakQueue(){
    stAct newAct;

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);


    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "您好, 我是自动化系迎新机器人小智，很高兴认识您。";
    newAct.nDuration = 6;
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

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
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
    newAct.strTarget = "1";
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "2";
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "519";
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "519,电力电子与运动控制实验室主要为电力电子技术和运动控制系统等课程服务。本实验室自行设计和开发实验平台19套，并引进了大量具有先进技术的自动化设备和网络控制平台，如ControlLogix控制器、工业变频器等。";
    newAct.nDuration = 20;
    arAct.push_back(newAct);
    
    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "继续";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "3";
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "520";
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "520,控制理论实验室主要承担国家级精品课《自动控制理论》课程实验，同时开设了独立实验课程《控制理论专题实验》。实验室主要设备有自行研制的模拟仿真实验箱、自行研制的小功率随动控制系统、直线倒立摆和旋转运动控制系统等。";
    newAct.nDuration = 20;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "继续";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "521";
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "521,“传感器与检测”分室主要从事传感器和各种参数检测技术以及现场总线技术的教学和研究。实验室多年来得到德国P+F公司在传感器和AS-i总线实验设备方面的捐赠。";
    newAct.nDuration = 20;
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);


    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "自动导游即将结束，自动化系欢迎您的再次光临！";
    newAct.nDuration = 8;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "home";
    arAct.push_back(newAct);
}
