/*
    LCT200 Library is a Arduino Library for OurEDA ESPWifi Shield.
    Copyright (C) 2024  SikongJueluo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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