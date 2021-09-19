#ifndef TAKE_PHOTO_H_
#define TAKE_PHOTO_H_
#include "action_manager.h"

class CTakePhoto : public CActionManager
{
public:
    CTakePhoto();
    ~CTakePhoto();
    void Queue();
};
#endif //take_photo