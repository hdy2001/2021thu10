#include "temp_measure.h"
#include <string>

TempMeasure::TempMeasure(){

}

TempMeasure::~TempMeasure(){

}

void TempMeasure::TempQueue(float AmbTemp, float ObjTemp){
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