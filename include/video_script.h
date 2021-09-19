#ifndef VIDEO_SCRIPT_H
#define VIDEO_SCRIPT_H
#include "action_manager.h"

class CVideoScript : public CActionManager
{
public:
	CVideoScript();
	~CVideoScript();
    void Queue();
};

#endif // Video_SCRIPT_H