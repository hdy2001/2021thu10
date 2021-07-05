#ifndef ADD_POINT_H
#define ADD_POINT_H
#include "action_manager.h"

class CAddPoint : public CActionManager
{
public:
	CAddPoint();
	~CAddPoint();
    void Queue();
};

#endif //