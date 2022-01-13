#pragma once
#include "b_setup.hpp"
#include "c72_menuHA_GPS.hpp"

#if SUPPORT_SERIAL_CONTROL == 1
    #include "f_serial.hpp"
#endif

void loop()
{
    #ifdef ESP32
    serialLoop();
    #endif
    Display_Driver.loop();
}