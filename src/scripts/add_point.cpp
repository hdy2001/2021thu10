#include "add_point.h"
CAddPoint::CAddPoint(){

}
CAddPoint::~CAddPoint(){

}
void CAddPoint::Queue(){
    stAct newAct;
    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "请站在我前方，我将跟随您，说，设置导航点，我将在我当前的位置，设置导航点。";
    newAct.nDuration = 10;
    arAct.push_back(newAct);

    	

    newAct.nAct = ACT_FOLLOW;
    newAct.fFollowDist = 0.5;
    arAct.push_back(newAct);
    
    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "1";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "2";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "3";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "4";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "5";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "6";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "7";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "8";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "9";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "设置";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "10";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "好的，已经在此处设置导航点";
    newAct.nDuration = 5;
    arAct.push_back(newAct);
}
