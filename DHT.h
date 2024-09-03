#ifndef DHT_H
#define DHT_H

#include <Arduino.h>

#define DHT22 0

class DHT {
public:
    DHT(uint8_t pin, uint8_t type);
    void begin();
    float readTemperature(bool isFahrenheit = false);
    float readHumidity();
    bool read();

private:
    uint8_t _pin;
    uint8_t _type;
    uint8_t _data[5];
    bool _read();
    void _request();
    bool _check();
    uint8_t _lastReading;
    uint32_t _lastReadTime;
};

#endif
