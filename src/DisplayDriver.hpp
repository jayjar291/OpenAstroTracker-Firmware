#ifndef _Display_Driver_
#define _Display_Driver_
#include "../Configuration_local.hpp"
class Mount;
class DisplayDriver
{
private:
    Mount *_mount;
public:
    DisplayDriver(Mount *mount);
    void Begin();
    void loop();
};

#endif