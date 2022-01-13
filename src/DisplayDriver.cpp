#include "DisplayDriver.hpp"
#include "Utility.hpp"
#include "../Version.h"
#include "Mount.hpp"

#if DISPLAY_TYPE == DISPLAY_TYPE_MINI12864
    #include "Adafruit_NeoPixel.h"
    #include "U8g2lib.h"
    #include "SPI.h"
    //NEO Pixel
    Adafruit_NeoPixel pixels(NUMPIXELS, PixelPIN, NEO_GRB + NEO_KHZ800);
    //display info pins defined by MKS GEN L V2.1
    #define encA    31
    #define encB    33
    #define encBtn  35
    #define U8_DC 16
    #define U8_CS 17
    #define U8_RST 23
    #define fontName u8g2_font_5x7_tf
    #define fontX 5
    #define fontY 9
    #define offsetX 1
    #define offsetY 0
    #define U8_Width 128
    #define U8_Height 64
    U8G2_UC1701_MINI12864_F_4W_HW_SPI u8g2(U8G2_R0, U8_CS, U8_DC , U8_RST);
    #ifdef OAM
        #define device "Open Astro Mount"
    #else 
        #define device "Open Astro Tracker"
    #endif
#else

#endif
Mount *_mount; 
int counter = 0;
DisplayDriver::DisplayDriver(Mount *mount) 
{
    _mount = mount;
}

void StatusInfo() {
  u8g2.drawFrame(0,0,128,64);
    u8g2.drawStr(25,10,device);
    u8g2.drawHLine(1,14,128);
    u8g2.drawStr(2,23," RA:");
    u8g2.drawStr(2,31,"DEC:");
    u8g2.drawStr(30,23,_mount->RAString(PRINT_STRING | CURRENT_STRING).c_str()); //RA
    u8g2.drawStr(30,31,_mount->DECString(PRINT_STRING | CURRENT_STRING).c_str()); //DEC
    u8g2.drawHLine(1,33,128);
    u8g2.drawStr(2,42," LAT:");
    u8g2.drawStr(2,50,"LONG:");
    u8g2.drawStr(30,42,"24");
    u8g2.drawStr(30,50,"24");
    u8g2.drawStr(40,42,"H");
    u8g2.drawStr(40,50,"°");
    u8g2.drawStr(45,42,"24");
    u8g2.drawStr(45,50,"24");
    u8g2.drawStr(55,42,"M");
    u8g2.drawStr(55,50,"'");
    u8g2.drawStr(60,42,"24");
    u8g2.drawStr(60,50,"24");
    u8g2.drawStr(70,42,"S");
    u8g2.drawStr(70,50,"\"");
    u8g2.drawStr(25,50,"-");
    u8g2.drawHLine(1,53,128);
    u8g2.drawStr(2,62,"Free Mem:");
    u8g2.drawStr(50,62,String(freeMemory()).c_str());
    if (_mount->isSlewingTRK())
    {
        u8g2.drawStr(95,27,"TRK");
    }
    #if USE_GPS > 0
    u8g2.drawStr(95,46,"GPS");
    #endif
    u8g2.drawStr(90,62,String(VERSION).c_str());
}

//startup function

void DisplayDriver::Begin()
{
    pixels.begin();
    u8g2.begin();
    u8g2.setContrast(255);
    u8g2.setFont(fontName);
}

//loop function

void DisplayDriver::loop()
{
    if (counter == 0)
    {
        u8g2.clearBuffer();	
        StatusInfo();	// write something to the internal memory
        u8g2.sendBuffer();
        counter++;
    } else {
        counter++;
        if (counter > 1000)
        {
            counter = 0;
        }
    }
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(red, green, blue)); // encoder
    pixels.setPixelColor(1, pixels.Color(red, green, blue));
    pixels.setPixelColor(2, pixels.Color(red, green, blue));  //back light
    pixels.show(); 
}