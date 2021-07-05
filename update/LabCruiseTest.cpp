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
#include <string>
#include <iostream>
#include "LabCruise.h"
const int KeyWordNum = 4;

// //modify this if needed
const int PointNum = 8;

static LabCruise LabCruiseScript;

// int flag = 0;
enum STATE
{
    WAIT=1, CHAT, CRUISE
} state;
std::string ChatKeyWordList[KeyWordNum] = {"你好", "能做什么", "哪些功能", "家"};

void KeywordCB(const std_msgs::String::ConstPtr &msg)
{
    switch(state){
        case WAIT:{
            if(msg->data.find("你好") == 0) {
                LabCruiseScript.ChatQueue(0);
                LabCruiseScript.ShowActs();
                LabCruiseScript.Main();
                LabCruiseScript.Main();
                state = CHAT;
            }
            break;
        }
        case CHAT:{
            if(msg->data.find("参观") == 0) {
                LabCruiseScript.CruiseQueue();
                LabCruiseScript.ShowActs();
                LabCruiseScript.Main();
                state = CRUISE;
            }
            int KeyWordIndex;
            for(KeyWordIndex = 0; KeyWordIndex < KeyWordNum; KeyWordIndex++){
                std::cout << "KeyWordIndex:" << KeyWordIndex << " " << msg->data.find(ChatKeyWordList[KeyWordIndex])<<endl;
                if(msg->data.find(ChatKeyWordList[KeyWordIndex]) >= 0 && msg->data.find(ChatKeyWordList[KeyWordIndex]) <= 100) break;
            }
            if(KeyWordIndex == KeyWordNum) return;
            LabCruiseScript.ChatQueue(KeyWordIndex);
            LabCruiseScript.ShowActs();
            LabCruiseScript.Main();
            LabCruiseScript.Main();
            break;
        }
        case CRUISE:{
            for(int j=0;j<20;j++) std::cout<< "CRUISING\n"<<endl;
            for( int pNum = 0; pNum < PointNum - 1; pNum++) LabCruiseScript.Main();
            break;
        }
        default:{
            break;
        }
    }  
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "LabCruiseScript");
    ROS_INFO("[main] LabCruiseScript");
    LabCruiseScript.Init();
    LabCruiseScript.SpeakQueue();
    LabCruiseScript.ShowActs();
    LabCruiseScript.Main();
    LabCruiseScript.Main();
    state = CHAT;
    ros::NodeHandle n;
    ros::Rate r(10);
    ros::Subscriber cmd_sub = n.subscribe("/gosomewhere", 10, KeywordCB);
    ros::spin();
    return 0;
}