/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2017-2020, Waterplus http://www.6-robot.com
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the WaterPlus nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  FOOTPRINTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/
/* @author Zhang Wanjie                                             */
/* @author2 PanZhuoShi                                             */
//加了一个状态机，以实现语音控制进行不同的任务。

#include <ros/ros.h>
#include <std_msgs/String.h>
#include "goto_point.h"
// #include <String>
// #include <iostream>
// #include <csdtio>
const int ACTNUM = 5;

//modify this if needed
const int ActQueueLength = 15;

static CGotoPoint goto_point_script;

int flag = 0;
enum STATE
{
      WAIT_POINT=1, WAIT_ACT
} state;
std::string ActList[ACTNUM] = {"抓取", "拍照", "视频", "播放", "三维重建"};
std::string GoalName, ActName, StartName;

void KeywordCB(const std_msgs::String::ConstPtr &msg)
{
    switch(state){
        case WAIT_POINT:{
            std_msgs::String strListen;
            int pNum = 0;
            StartName = goto_point_script.ps[0].name;
            for(pNum = 0; pNum < goto_point_script.ps.size(); pNum++){
                GoalName = goto_point_script.ps[pNum].name;//  transfer to string , important!
                if(msg->data.find(GoalName) == 0){
                    strListen.data = goto_point_script.ps[pNum].name;
                    goto_point_script.SpeakGoalQueue(strListen);
                    goto_point_script.ShowActs();
                    break;
                }
            }
            if(pNum == goto_point_script.ps.size()) return;
            goto_point_script.Main();
            goto_point_script.Main();
            state = WAIT_ACT;
            break;
        }
        case WAIT_ACT:{
            std_msgs::String strListen;
            int aNum = 0;
            for(aNum = 0; aNum < ACTNUM; aNum++){
                ActName = ActList[aNum];
                if(msg->data.find(ActName) == 0){
                    goto_point_script.ActQueue(GoalName, ActName, StartName);
                    goto_point_script.ShowActs();
                    break;
                }
            }
            if(aNum == ACTNUM) return;
            for(int i = 0; i < ActQueueLength; i++){
                goto_point_script.Main();
            }   
            break;
        }
        default:{
            break;
        }
    }
    //goto_point_script.Reset();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "goto_point_script");
    ROS_INFO("[main] goto_point_script");
    goto_point_script.Init();
    goto_point_script.SpeakQueue();
    goto_point_script.ShowActs();
    goto_point_script.Main();
    goto_point_script.Main();
    state = WAIT_POINT;
    ros::NodeHandle n;
    ros::Rate r(10);
    ros::Subscriber cmd_sub = n.subscribe("/gosomewhere", 10, KeywordCB);
    ros::spin();
    return 0;
}