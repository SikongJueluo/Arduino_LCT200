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

#ifndef __LCT200_H__
#define __LCT200_H__

#include <Wire.h>
#include "LCT200Serial.h"


typedef struct LCT200_Config
{
    uint8_t Serial0_baud;
    uint8_t Serial1_baud;
    uint8_t I2C_Freq;
    uint8_t I2C_UART_Mode;
    uint8_t Dev_Mode;
    uint8_t Master_Addr;
    uint8_t Enable_ForceSend;
    uint8_t Signal0;
    uint8_t Signal1;
};


class LCT200{
protected:
    uint16_t _devAddr;
    TwoWire * _wire;

    LCT200_Config _config = {
        0x03, // Serial0_baud
        0x07, // Serial1_baud
        0x02,
        0x00,
        0x01,
        0x15,
        0x00,
        5,    // Signal0
        4     // Signal1
    };

public:
    bool begin(TwoWire &hWire, uint8_t address = 0x03);
    bool begin(TwoWire &hWire, uint8_t address, LCT200_Config *config);

    size_t writeConfig(LCT200_Config *config);

    int enableISR(uint8_t uart, uint8_t pin, void (*fun)());
    int readConfig(uint8_t data[11], uint16_t timeout = 1000);

    LCT200Serial Serial0, Serial1;
};


#endif 
