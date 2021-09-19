#include "9_campus_script.h"
CCampusScript::CCampusScript()
{
    
}

CCampusScript::~CCampusScript()
{

}

void CCampusScript::Queue()
{
    stAct newAct;

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "智慧校园 项目开始";
    newAct.nDuration = 3;
    arAct.push_back(newAct);

    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "人";   //建议台词"机器人"
    newAct.nDuration = 5;    //识别时长
    arAct.push_back(newAct);
    
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "你好";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    newAct.nDuration = 1;
    arAct.push_back(newAct);
    

}
