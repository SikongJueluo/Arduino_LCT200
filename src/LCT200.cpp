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

#include "LCT200.h" 
#include <Arduino.h>

#define baudRate 9600
#define I2C_MAX_BUFFER_LENGTH 32

bool LCT200::begin(TwoWire &hWire, uint8_t address, LCT200_Config *config) {
    _devAddr = address;
    _wire = &hWire;

    _wire->begin();

    // Serial.println("I2C begin successfully!");
    
    pinMode(config->Signal0, OUTPUT);
    pinMode(config->Signal1, OUTPUT);
    digitalWrite(config->Signal0, HIGH);
    digitalWrite(config->Signal1, HIGH);
    delay(100);

    if (writeConfig(config) != 11)
        return false;

    LCT200::Serial0.begin(hWire, address, 0);
    LCT200::Serial1.begin(hWire, address, 1);

    pinMode(config->Signal0, INPUT_PULLUP);
    pinMode(config->Signal1, INPUT_PULLUP);

    return true;
}

bool LCT200::begin(TwoWire &hWire, uint8_t address) {
    return begin(hWire, address, &_config);
}

size_t LCT200::writeConfig(LCT200_Config *config) {

    memcpy(&_config, config, 9 * sizeof(uint8_t));
    
    uint8_t config_str[11] = {
        0xFB,
        0x08,
        0x00,
        config->Serial0_baud,
        config->Serial1_baud,
        config->I2C_Freq,
        config->I2C_UART_Mode,
        config->Dev_Mode,
        config->Master_Addr,
        config->Enable_ForceSend,
        0xBF
    };

    digitalWrite(config->Signal0, LOW);
    delay(300);

    size_t count = 0;
    _wire->beginTransmission(_devAddr);
    for (; count < 11; count++)
        Wire.write(config_str[count]);
    _wire->endTransmission();

    digitalWrite(config->Signal0, HIGH);

    return count;
}

int LCT200::enableISR(uint8_t uart, uint8_t pin, void (*fun)()) {
    if (uart == 0x00) _config.Signal0 = pin;
    else if (uart == 0x01) _config.Signal1 = pin;
    else return (-1);
    attachInterrupt(pin, fun, FALLING);
    return true;
}

int LCT200::readConfig(uint8_t data[11], uint16_t timeout) {
    uint8_t count = 0;
    uint32_t t1 = millis();

    pinMode(_config.Signal0, OUTPUT);
    pinMode(_config.Signal1, OUTPUT);
    digitalWrite(_config.Signal0, HIGH);
    digitalWrite(_config.Signal1, HIGH);
    delay(100);
    digitalWrite(_config.Signal0, LOW);
    delay(300);

    _wire->beginTransmission(_devAddr);
    _wire->write(0x10);
    _wire->endTransmission();
    _wire->requestFrom((uint8_t)_devAddr, 11);
    for (; _wire->available() && (timeout == 0 || millis() - t1 < timeout); count++) {
        data[count] = _wire->read();
    }
    // check for timeout
    if (timeout > 0 && millis() - t1 >= timeout && count < 11) count = -1; // timeout

    digitalWrite(_config.Signal0, HIGH);

    pinMode(_config.Signal0, INPUT_PULLUP);
    pinMode(_config.Signal1, INPUT_PULLUP);

    return count;
}
