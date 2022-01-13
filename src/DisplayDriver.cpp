#include "DisplayDriver.hpp"


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
    U8G2_UC1701_MINI12864_1_4W_HW_SPI u8g2(U8G2_R0, U8_CS, U8_DC , U8_RST);
    #ifdef OAM
        #define device "Open Astro Mount"
    #else 
        #define device "Open Astro Tracker"
    #endif
#else

#endif

DisplayDriver::DisplayDriver() 
{

}

//startup function

void DisplayDriver::Begin()
{
    pixels.begin();
    u8g2.begin();
    u8g2.setContrast(255);
}

//loop function

void DisplayDriver::loop()
{
    u8g2.clearBuffer();					// clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
    u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
    u8g2.sendBuffer();					// transfer internal memory to the display
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(red, green, blue)); // encoder
    pixels.setPixelColor(1, pixels.Color(red, green, blue));
    pixels.setPixelColor(2, pixels.Color(red, green, blue));  //back light
    pixels.show(); 
}