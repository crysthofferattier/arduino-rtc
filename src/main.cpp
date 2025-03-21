#include <Arduino.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void startSerialMonitor();
void rtcModuleChecks();
void adjustRTC();
unsigned long getUnixTimeStamp();

unsigned long previousMillis = 0; // Stores the last time the Unix timestamp was printed
const long interval = 1000;       // 1 second interval to print the Unix timestamp

bool rtcTimeSet = false;

void setup()
{
  startSerialMonitor();
  rtcModuleChecks();
}

void loop()
{
  unsigned long currentMillis = millis(); // Get the current time in milliseconds

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= interval)
  {
    // Save the last time the timestamp was printed
    previousMillis = currentMillis;

    // Print the Unix timestamp
    Serial.println(getUnixTimeStamp());  
  }
}

/*!
    @brief  Set the date to the date and time of the compilation of the program

    @bug if Arduino is turned off the date and time will be set to the Date and Time from last compilation
*/
void adjustRTC()
{
  if (!rtcTimeSet)
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    rtcTimeSet = true;

    Serial.println("RTC time has been set to compilation time.");
  }
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
  unsigned long startMillis = millis(); // Record the start time for timeout
  unsigned long timeout = 5000;         // Set the timeout period (5 seconds)

  while (!rtc.begin())
  {
    Serial.println("Trying to locate RTC Module...");

    // Check if the timeout has occurred
    if (millis() - startMillis > timeout)
    {
      Serial.println("RTC Module not found after 5 seconds. Please check the connection.");
      while (true)
        ; // Stop the program
    }
  }

  // If the RTC was previously initialized, do not adjust the time again.
  if (rtc.now().year() < 2000) {  // If the RTC is not set (year < 2000), adjust time
    Serial.println("RTC time is invalid. Adjusting to compile time.");
    adjustRTC();
  } else {
    Serial.println("RTC time is valid. No adjustment needed.");
  }
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