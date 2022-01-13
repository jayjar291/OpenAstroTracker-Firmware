#pragma once

#include "../Configuration.hpp"
#include "EPROMStore.hpp"

#if USE_GPS == 1

    #if DEBUG_LEVEL & DEBUG_GPS
char gpsBuf[256];
int gpsBufPos = 0;
    #endif

long lastGPSUpdate = 0;
bool gpsAqcuisitionComplete(int &indicator)
{
    while (GPS_SERIAL_PORT.available())
    {
        int gpsChar = GPS_SERIAL_PORT.read();

    #if DEBUG_LEVEL & DEBUG_GPS
        if ((gpsBufPos < 254) && (gpsChar > 31))
        {
            gpsBuf[gpsBufPos++] = gpsChar;
        }
    #endif
        if (gpsChar == 36)
        {
            // $ (ASCII 36) marks start of message, so we switch indicator every message
            if (millis() - lastGPSUpdate > 500)
            {
                indicator     = adjustWrap(indicator, 1, 0, 3);
                lastGPSUpdate = millis();
            }
        }
        if (gps.encode(gpsChar))
        {
    #if DEBUG_LEVEL & DEBUG_GPS
            gpsBuf[gpsBufPos++] = 0;
            LOGV2(DEBUG_GPS, F("GPS: Sentence: [%s]"), gpsBuf);
            gpsBufPos = 0;
    #endif

            LOGV4(DEBUG_GPS,
                  F("GPS: Encoded. %l sats, Location is%svalid, age is %lms"),
                  gps.satellites.value(),
                  (gps.location.isValid() ? " " : " NOT "),
                  gps.location.age());
            // Make sure we got a fix in the last 30 seconds
            if ((gps.location.lng() != 0) && (gps.location.age() < 30000UL))
            {
                LOGV2(DEBUG_INFO, F("GPS: Sync'd GPS location. Age is %d secs"), gps.location.age() / 1000);
                LOGV3(DEBUG_INFO, F("GPS: Location: %f  %f"), gps.location.lat(), gps.location.lng());
                LOGV4(DEBUG_INFO, F("GPS: UTC time is %dh%dm%ds"), gps.time.hour(), gps.time.minute(), gps.time.second());


                DayTime utcNow = DayTime(gps.time.hour(), gps.time.minute(), gps.time.second());
                utcNow.addHours(mount.getLocalUtcOffset());
                mount.setLocalStartTime(utcNow);
                mount.setLocalStartDate(gps.date.year(), gps.date.month(), gps.date.day());
                mount.setLatitude(gps.location.lat());
                mount.setLongitude(gps.location.lng());

                mount.delay(500);

                return true;
            }
        }
    }
    return false;
}
#endif