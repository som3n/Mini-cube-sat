# CubeSat Mini Project

## Overview

This project is designed for a CubeSat mini satellite system. It incorporates various sensors to monitor environmental conditions and communicate data. The system uses an Arduino microcontroller along with the following components:

- **DHT22**: For temperature and humidity measurements
- **BMP180**: For barometric pressure and altitude measurements
- **Bluetooth Module (HC-05)**: For wireless communication
- **9V Battery**: For power supply

## Components

1. **DHT22 Sensor**
   - Measures temperature and humidity.
   
2. **BMP180 Sensor**
   - Measures atmospheric pressure and calculates altitude.
   
3. **Bluetooth Module (HC-05)**
   - Enables wireless communication for data transmission.
   
4. **9V Battery**
   - Provides power to the Arduino and sensors.

## File Structure

- **`main.c`**: Arduino sketch for handling sensor data and Bluetooth communication.
- **`dht.h`**: Custom header file for DHT22 sensor.
- **`dht.cpp`**: Custom implementation for DHT22 sensor.
- **`process_info.cpp`**: C++ source file for process monitoring.
- **`ctop.py`**: Python script for system monitoring.
- **`install.sh`**: Installation script for setting up the environment and dependencies.

## Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/cubesat-mini.git
   cd cubesat-mini
   ```

2. **Run the Installation Script**

   Make sure you have root privileges (use `sudo` if necessary).

   ```bash
   sudo ./install.sh
   ```

   This script will:
   - Install necessary dependencies
   - Compile the C++ program
   - Make the Python script executable
   - Create a symlink for easy access to `ctop`

## Usage

### Arduino Code

1. **Upload Arduino Sketch**

   Open the Arduino IDE and upload the provided `main.c` code to your Arduino board.

   ```c
   #include <Wire.h>
   #include <Adafruit_Sensor.h>
   #include <DHT.h>
   #include <Adafruit_BMP085_U.h>
   #include <SoftwareSerial.h>

   #define DHTPIN 2
   #define DHTTYPE DHT22

   DHT dht(DHTPIN, DHTTYPE);
   Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified();
   SoftwareSerial btSerial(10, 11); // RX, TX

   void setup() {
     Serial.begin(9600);
     btSerial.begin(9600);
     dht.begin();
     if (!bmp.begin()) {
       Serial.println("Couldn't find the BMP180 sensor");
       while (1);
     }
   }

   void loop() {
     sensors_event_t event;
     dht.read();
     bmp.getEvent(&event);

     if (!isnan(dht.readTemperature()) && !isnan(dht.readHumidity()) && !isnan(event.pressure)) {
       float temperature = dht.readTemperature();
       float humidity = dht.readHumidity();
       float pressure = event.pressure;

       String data = "Temp: " + String(temperature) + " C, Humidity: " + String(humidity) + " %, Pressure: " + String(pressure) + " hPa";
       Serial.println(data);
       btSerial.println(data);
     } else {
       Serial.println("Failed to read from sensors!");
     }

     delay(2000);
   }
   ```

2. **Connect to Bluetooth**

   Use a Bluetooth terminal app to connect to the HC-05 module and view sensor data.

- **If the Arduino code is not working:**
  - Check sensor connections and ensure the correct library versions are installed.
  - Ensure you have uploaded the `main.c` sketch correctly to the Arduino board.

## Contributing

Feel free to fork the repository, make changes, and submit pull requests. Contributions are welcome!

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contact

For any questions or issues, please contact [thesomen123@gmail.com].

---

Replace placeholders such as repository URL, email address, and any other project-specific information with your actual details. This README file provides a comprehensive guide to setting up, using, and troubleshooting your CubeSat project.
