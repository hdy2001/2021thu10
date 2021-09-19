#ifndef GOTO_POINT_H
#define GOTO_POINT_H
#include "action_manager.h"
#include <std_msgs/String.h>

class CGotoPoint : public CActionManager
{
public:
	CGotoPoint();
	~CGotoPoint();
    void SpeakGoalQueue(std_msgs::String &voice_cmd);
    void ActQueue(const std::string GoalName, const std::string ActName, const std::string StartName);
    void SpeakQueue();
};

#endif //