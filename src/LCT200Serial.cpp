#include <Arduino.h>
#include "LCT200Serial.h"

#define I2C_MAX_BUFFER_LENGTH 32

bool LCT200Serial::begin(TwoWire &hWire, uint16_t address, uint8_t uart) {
    _wire = &hWire;
    _devAddr = address;
    _uart = uart;
    return true;
}

// not recommanded
size_t LCT200Serial::write(char ch) {
    size_t count = 0;
    _wire->beginTransmission(_devAddr);
    _wire->write(_uart);
    count = _wire->write(ch);
    _wire->endTransmission();
    delay(4);
    return count;
}

size_t LCT200Serial::print(uint8_t num) {
    return write(num);
}

size_t LCT200Serial::print(const char * string) {
    size_t count = 0;
    uint16_t length = strlen(string);
    _wire->beginTransmission(_devAddr);
    _wire->write(_uart);
    _wire->endTransmission();
    for (int k = 0; k < length; k += min((int)length, I2C_MAX_BUFFER_LENGTH)) {
        _wire->beginTransmission(_devAddr);
        for (;count < length && count < k + I2C_MAX_BUFFER_LENGTH; count++)
            _wire->write(string[count]);
        _wire->endTransmission();
    }
    // delay(4);
    return count;
}

size_t LCT200Serial::print(const Printable& x) {
    size_t count = 0;
    _wire->beginTransmission(_devAddr);
    _wire->write(_uart);
    count = _wire->print(x);
    _wire->endTransmission();
    delay(4);
    return count;
}

size_t LCT200Serial::print(const String &s) {
    size_t count = 0;
    _wire->beginTransmission(_devAddr);
    _wire->write(_uart);
    count = _wire->print(s);
    _wire->endTransmission();
    delay(4);
    return count;
}

int LCT200Serial::available() {
    uint8_t str_len = 0;
    uint32_t t1 = millis();

    _wire->beginTransmission(_devAddr);
    _wire->write(_uart);
    _wire->endTransmission();
    _wire->requestFrom((uint8_t)_devAddr, 1);

    str_len = _wire->read();
    delay(4);
    return str_len;
}


int LCT200Serial::readBytes(uint8_t length, uint8_t *data, uint16_t timeout){
    uint8_t count = 0, str_len = 0;
    uint32_t t1 = millis();
    _wire->beginTransmission(_devAddr);
    _wire->write(_uart);
    _wire->endTransmission();
    for (int k = 0; k < length; k += min((int)length, I2C_MAX_BUFFER_LENGTH)) {
        _wire->requestFrom((uint8_t)_devAddr, (uint8_t)min((int)length - k, I2C_MAX_BUFFER_LENGTH));
        str_len = _wire->read();
        for (; _wire->available() && (timeout == 0 || millis() - t1 < timeout); count++) {
            data[count] = _wire->read();
        }
    }
    // check for timeout
    if (timeout > 0 && millis() - t1 >= timeout && count < length) return (-1); // timeout
    return str_len;
}

// not recommanded
int LCT200Serial::read() {
    uint8_t ch = 0, str_len = 0;
    str_len = readBytes(2, &ch, 2);
    if (str_len == -1) return str_len;
    return ch;
}
