#pragma once

#include "inc/Globals.hpp"

#include "Utility.hpp"
#include "DayTime.hpp"
#include "Mount.hpp"
#include "MeadeCommandProcessor.hpp"

#if USE_GPS == 1
//#include <SoftwareSerial.h>
#include <TinyGPS++.h>

//SoftwareSerial SoftSerial(GPS_SERIAL_RX_PIN, GPS_SERIAL_TX_PIN); // RX, TX
TinyGPSPlus gps;
#endif

// AZ/ALT Motor pins
#if AZIMUTH_ALTITUDE_MOTORS == 1
  // AZ/ALT Pins are defined based on driver type rather than _stepper type since the 28BYJ may be used with a TMC2209 or similar driver when modified to bipolar mode
  #if AZ_DRIVER_TYPE == DRIVER_TYPE_ULN2003
    #define AZmotorPin1  AZ_IN1_PIN    
    #define AZmotorPin3  AZ_IN2_PIN    
    #define AZmotorPin2  AZ_IN3_PIN    
    #define AZmotorPin4  AZ_IN4_PIN    
  #elif AZ_DRIVER_TYPE == DRIVER_TYPE_A4988_GENERIC || AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE || AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
    #define AZmotorPin1  AZ_STEP_PIN
    #define AZmotorPin2  AZ_DIR_PIN
  #endif
  #if ALT_DRIVER_TYPE == DRIVER_TYPE_ULN2003
    #define ALTmotorPin1  ALT_IN1_PIN 
    #define ALTmotorPin3  ALT_IN2_PIN 
    #define ALTmotorPin2  ALT_IN3_PIN 
    #define ALTmotorPin4  ALT_IN4_PIN     
  #elif ALT_DRIVER_TYPE == DRIVER_TYPE_A4988_GENERIC || ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_STANDALONE || ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART
    #define ALTmotorPin1  ALT_STEP_PIN
    #define ALTmotorPin2  ALT_DIR_PIN
  #endif

#endif
// End Stepper Definitions //////////////
/////////////////////////////////////////

/////////////////////////////////////////
// Driver definitions ///////////////////
#if (RA_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART) || (DEC_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART) || (AZ_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART) || (ALT_DRIVER_TYPE == DRIVER_TYPE_TMC2209_UART)
  #define R_SENSE 0.11f           // 0.11 for StepStick
#endif
// End Driver Definitions ///////////////
/////////////////////////////////////////

// Menu IDs
#define RA_Menu 1
#define DEC_Menu 2
#define HA_Menu 3
#define Heat_Menu 4
#define Calibration_Menu 5
#define Control_Menu 6
#define Home_Menu 7
#define POI_Menu 8
#define Status_Menu 9

// How many menu items at most?
#define MAXMENUITEMS 10

#if SUPPORT_GUIDED_STARTUP == 1
bool inStartup = true; // Start with a guided startup
#else
bool inStartup = false; // Start with a guided startup
#endif

// Serial control variables
bool okToUpdateMenu = true;   // Can be used to supress rendering the first line of the menu.
bool quitSerialOnNextButtonRelease = false; // Used to detect SELECT button to quit Serial mode.

// Global variables
bool isUnreachable = false;

// RA variables
int RAselect;

// DEC variables
int DECselect;

// HA variables
int HAselect;

//debugging
String inBT;
