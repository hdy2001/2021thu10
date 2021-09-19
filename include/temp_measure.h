#ifndef GOTO_POINT_H
#define GOTO_POINT_H
#include "action_manager.h"
#include "FilePath.h"
#include <sstream>
#include <std_msgs/String.h>

class TempMeasure : public CActionManager
{
public:
	TempMeasure();
	~TempMeasure();
    void TempQueue(float amb, float obj);
};

#endif //
