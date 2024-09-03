#include "dht.h"
#include <Arduino.h>

DHT::DHT(uint8_t pin, uint8_t type) : _pin(pin), _type(type), _lastReading(0), _lastReadTime(0) {
    // Constructor
}

void DHT::begin() {
    pinMode(_pin, INPUT_PULLUP);
}

float DHT::readTemperature(bool isFahrenheit) {
    if (read()) {
        float temp = (_data[2] & 0x7F) * 256 + _data[3];
        temp /= 10.0;
        if (_data[2] & 0x80) {
            temp *= -1;
        }
        return isFahrenheit ? temp * 9.0 / 5.0 + 32 : temp;
    }
    return NAN;
}

float DHT::readHumidity() {
    if (read()) {
        return (_data[0] * 256 + _data[1]) / 10.0;
    }
    return NAN;
}

bool DHT::read() {
    uint32_t currentTime = millis();
    if (currentTime - _lastReadTime < 2000) {
        return true;
    }

    _request();

    if (_check()) {
        _lastReadTime = currentTime;
        return true;
    }
    return false;
}

void DHT::_request() {
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(18);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);
    pinMode(_pin, INPUT);
}

bool DHT::_check() {
    uint8_t i = 0, j;
    uint32_t timeout = millis() + 100;

    while (digitalRead(_pin) == LOW) {
        if (millis() > timeout) return false;
    }
    while (digitalRead(_pin) == HIGH) {
        if (millis() > timeout) return false;
    }
    while (i < 40) {
        timeout = millis() + 100;
        while (digitalRead(_pin) == LOW) {
            if (millis() > timeout) return false;
        }
        uint32_t t = micros();
        while (digitalRead(_pin) == HIGH) {
            if (millis() > timeout) return false;
        }
        if ((micros() - t) > 40) {
            _data[i / 8] |= (1 << (7 - (i % 8)));
        }
        i++;
    }
    return _data[0] + _data[1] + _data[2] + _data[3] == _data[4];
}
