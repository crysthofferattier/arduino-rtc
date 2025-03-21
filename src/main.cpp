#include <Arduino.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void startSerialMonitor();
void rtcModuleChecks();
void adjustRTC();
unsigned long getUnixTimeStamp();

void setup()
{
  startSerialMonitor();
  rtcModuleChecks();
}

void loop()
{
  Serial.println(getUnixTimeStamp());

  delay(1000);
}

/*!
    @brief  Set the date to the date and time of the compilation of the program

    @bug if Arduino is turned off the date and time will be set to the Date and Time from last compilation
*/
void adjustRTC()
{
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

/**
 * @brief Initialize serial communication at 9600 bits per second (baud).
 */
void startSerialMonitor()
{
  Serial.begin(9600);
  Serial.println("Initialzing Serial Monitor...");

  while (!Serial)
    ;

  Serial.println("Serial Monitor connected!");
}

/**
 * @brief Check I2C for the DS3231 and test succesful connection
 * also adjust date
 *
 * @see adjustRTC() function
 */
void rtcModuleChecks()
{
  if (!rtc.begin())
  {
    Serial.println("RTC Module not found!");
    while (true)
      ;
  }

  adjustRTC();
}

/**
 * @brief Return Unix time: seconds since 1 Jan 1970.
 *
 * @return number of seconds since the Unix epoch (January 1, 1970).
 */
unsigned long getUnixTimeStamp()
{
  return rtc.now().unixtime();
}