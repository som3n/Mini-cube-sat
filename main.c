#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>

// Define sensor pins and parameters
#define DHTPIN 2        // Pin connected to DHT22
#define DHTTYPE DHT22   // DHT 22 (AM2302)

// Create sensor objects
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified();

void setup() {
  // Start serial communication with the Bluetooth module
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();

  // Initialize BMP180 sensor
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  // Read temperature and humidity from DHT22
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read pressure from BMP180
  sensors_event_t event;
  bmp.getEvent(&event);

  // Check if data is valid
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Send temperature and humidity to Bluetooth
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\n");

    // Send pressure data to Bluetooth
    if (event.pressure) {
      Serial.print("Pressure: ");
      Serial.print(event.pressure);
      Serial.println(" hPa");
    } else {
      Serial.println("Pressure data unavailable");
    }
  }

  // Delay before the next reading
  delay(2000);
}
