# Arduino RTC Project

This project reads the current Unix timestamp from a DS3231 Real-Time Clock (RTC) module and prints it to the Serial Monitor every second. It ensures non-blocking behavior by using `millis()` instead of `delay()`, allowing other tasks to run concurrently without waiting.

## Features

- **RTC Module**: Uses the DS3231 Real-Time Clock module to keep track of the current time.
- **Unix Timestamp**: The program prints the current Unix timestamp (seconds since 1st January 1970).
- **Non-blocking Operation**: The program uses `millis()` to print the timestamp every second without blocking other tasks.
- **RTC Initialization**: The RTC time is set to the compilation time on the first power-up or reset.
- **Timeout Mechanism**: A timeout mechanism ensures that the program doesn't hang indefinitely if the RTC module is not found.

## Components

- **Arduino Board**: Any Arduino board (e.g., Uno, Nano, etc.)
- **DS3231 RTC Module**
- **Jumper Wires**
- **Breadboard (optional)**

## Wiring

Connect the DS3231 RTC module to your Arduino using the following pin configuration:

| DS3231 Pin | Arduino Pin |
|-------------|-------------|
| VCC         | 5V          |
| GND         | GND         |
| SDA         | A4 (for Uno/Nano) |
| SCL         | A5 (for Uno/Nano) |

For other Arduino boards, check the specific pins for I2C communication (SDA, SCL).

## Code Overview

The Arduino program does the following:

1. **Initialize Serial Communication**: The program starts by setting up serial communication at 9600 baud to communicate with the Serial Monitor.
2. **Check RTC Module**: It checks whether the DS3231 RTC module is connected. If not, it will print an error message and stop the program.
3. **Adjust RTC**: The RTC time is set to the time when the program was compiled using the `__DATE__` and `__TIME__` macros.
4. **Print Unix Timestamp**: The program prints the Unix timestamp every second to the Serial Monitor.
5. **Non-blocking Behavior**: Using `millis()`, the program prints the timestamp without blocking other processes.

### Code Workflow:

1. **`startSerialMonitor()`**: Initializes serial communication.
2. **`rtcModuleChecks()`**: Ensures that the RTC module is connected. It tries to find the RTC for 5 seconds, after which it stops and prints an error message if the module is not found.
3. **`adjustRTC()`**: Sets the RTC time to the time of compilation (using `__DATE__` and `__TIME__`).
4. **`getUnixTimeStamp()`**: Fetches the current Unix timestamp (seconds since January 1, 1970) from the RTC.
5. **`loop()`**: Prints the Unix timestamp every second to the Serial Monitor.

## How to Use

1. **Connect the RTC Module**: Wire the DS3231 RTC module to your Arduino as described in the Wiring section above.
2. **Upload the Code**: Upload the provided Arduino code to your board using the Arduino IDE.
3. **Open the Serial Monitor**: After uploading the code, open the Serial Monitor at 9600 baud. You should start seeing the Unix timestamp printed every second.
4. **RTC Module**: The RTC will be initialized with the compile time (when the program was compiled), and it will continue keeping time even when the Arduino is powered off and back on.

## Troubleshooting

1. **RTC Module Not Found**: If the program prints "RTC Module not found!", check your wiring, ensure that the RTC is properly connected to the correct pins (SDA, SCL), and ensure the I2C address is correctly set in the library.
2. **Timeout**: If the RTC module is not detected within 5 seconds, the program will stop and display a message. Check the connections and I2C address, and ensure that the module is powered correctly.

## License

This project is open-source and released under the [MIT License](https://opensource.org/licenses/MIT).
