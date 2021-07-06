#ifndef GOTO_POINT_H
#define GOTO_POINT_H
#include "action_manager.h"
#include "FilePath.h"
#include <sstream>
#include <std_msgs/String.h>

class LabCruise : public CActionManager
{
public:
	LabCruise();
	~LabCruise();
    void SpeakQueue();
    void ChatQueue(const int KeyWordIndex);
    void CruiseQueue();
    void TempQueue(float amb, float obj);
};

#endif //