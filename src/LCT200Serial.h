#ifndef __LCT200SERIAL_H__
#define __LCT200SERIAL_H__

#include <Wire.h>

class LCT200Serial{
protected:
    TwoWire * _wire;
    uint8_t _uart;
    uint16_t _devAddr;

public:
    bool begin(TwoWire &hWire, uint16_t address, uint8_t uart);

    size_t write(char ch);
    size_t print(uint8_t num);
    size_t print(const char * string);
    size_t print(const String & s);
    size_t print(const Printable & x);

    int available();
    int readBytes(uint8_t length, uint8_t *data, uint16_t timeout = 1000);
    int read();
};

#endif