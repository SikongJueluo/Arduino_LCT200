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

#include "ESP_Wifi.h" 



bool ESP_Wifi::begin(LCT200Serial &serial, uint32_t baud) {
    _serial = &serial;

    _serial->print("AT\r\n");
    // Serial.print("ATOK");
    if (readAck(AT_OK) == (-1)){
        // Serial.print(_ackBuf);
        return false;
    }

    return true;
}

int ESP_Wifi::sendCommand(const char * command, const char * param, bool isQuey) {
    char buf[BUF_LENGTH] = {0};
    if (isQuey) {
        sprintf(buf, "AT+%s?\r\n", command);
    }
    else {
        if (param == NULL) {
            sprintf(buf, "AT+%s\r\n", command);
        } else {
            sprintf(buf, "AT+%s=%s\r\n", command, param);
        }
    }

    if (_serial->print(buf)) return 0;
    return (-1);
}

int ESP_Wifi::readAck(const char * ack, uint16_t timeout) {
    uint64_t time = millis();
    uint8_t count = 0;

    clearBuf();

    while (millis() - time < timeout)
    {
        if (_serial->available()) {
            _ackBuf[count++] = _serial->read();

            if (searchBuf(ack)) return count;
        }
    }

    return (-1);
}

int ESP_Wifi::readAck(const char * ack, const char * error, uint16_t timeout) {
    uint32_t time = millis();
    uint8_t count = 0;

    clearBuf();

    while (millis() - time < timeout)
    {
        if (_serial->available()) {
            _ackBuf[count++] = _serial->read();

            if (searchBuf(ack)) return count;
            if (searchBuf(error)) return (-1);
        }
    }

    return (-1);
}

char * ESP_Wifi::searchBuf(const char * str) {
    return strstr(_ackBuf, str);
}

void ESP_Wifi::clearBuf() {
    memset(_ackBuf, '\0', BUF_LENGTH);
}






bool ESP_Wifi::setMode(esp_wifi_mode mode) {
    char mode_str[2] = {mode + '0', 0};
    sendCommand(AT_WIFI_MODE, mode_str);
	return (readAck(AT_OK)> 0 ? true : false );
}

bool ESP_Wifi::connectAP(const char * ssid, const char * pwd) {
    char param[BUF_LENGTH] = {0};
    sprintf(param, "\"%s\",\"%s\"", ssid, pwd);
    sendCommand(AT_WIFI_CONN, param);
	return (readAck(AT_WIFI_CONN_OK, 10000)> 0 ? true : false );
}
bool ESP_Wifi::createAP(const char * ssid, const char * pwd, uint8_t chl, uint8_t ecn) {
    char param[BUF_LENGTH] = {0};
    sprintf(param, "\"%s\",\"%s\",%d,%d", ssid, pwd, chl, ecn);
    sendCommand(AT_WIFI_SAP, param);
	return (readAck(AT_OK, AT_ERROR, 10000)> 0 ? true : false );

}

bool ESP_Wifi::udpConnect(const char * ip, uint16_t remote_port, uint16_t local_port) {
    char param[BUF_LENGTH] = {0};
    if (local_port)
        sprintf(param, "\"UDP\",\"%s\",%d,%d,0", ip, remote_port, local_port);
    else
        sprintf(param, "\"UDP\",\"%s\",%d", ip, remote_port);
    sendCommand(AT_IP_CONN, param);
	return (readAck(AT_OK)> 0 ? true : false );
}

int ESP_Wifi::udpSend(const char * data, size_t data_size) {
    char param[8] = {0};
    int ack;

    sprintf(param, "%d", data_size);
    sendCommand(AT_IP_SEND, param);

    delay(20);
    _serial->print(data);
	return (readAck(AT_OK, 5000)> 0 ? true : false );


    // ack = readAck(AT_OK, AT_ERROR);
    // if (ack > 0) {
    //     _serial->print(data);

    //     ack = readAck(AT_OK, AT_ERROR);
    //     if (ack > 0) return data_size;
    // }
    // return ack;
}




size_t ESP_Wifi::write(char ch) {
    return _serial->write(ch);
}
size_t ESP_Wifi::print(uint8_t num) {
    return _serial->print(num);
}
size_t ESP_Wifi::print(const char * string) {
    return _serial->print(string);
}
size_t ESP_Wifi::print(const String & s) {
    return _serial->print(s);
}
size_t ESP_Wifi::print(const Printable & x) {
    return _serial->print(x);
}
int ESP_Wifi::available() {
    return _serial->available();
}
int ESP_Wifi::readBytes(uint8_t length, uint8_t *data, uint16_t timeout) {
    return _serial->readBytes(length, data, timeout);
}
int ESP_Wifi::read() {
    return _serial->read();
}


