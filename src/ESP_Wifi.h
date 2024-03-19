#ifndef __ESP_WIFI_H__
#define __ESP_WIFI_H__

#include "LCT200.h"
#include "Arduino.h"
#include "IPAddress.h"

#define BUF_LENGTH 128
#define AT_OK "OK"
#define AT_ERROR "ERROR"
#define AT_WIFI_CONN_OK "WIFI CONNECTED"

#define AT_FIRM "GMR" 
#define AT_WIFI_MODE "CWMODE"
#define AT_WIFI_CONN "CWJAP"
#define AT_WIFI_SAP "CWSAP"

#define AT_IP_CONN "CIPSTART"
#define AT_IP_SEND "CIPSEND"


typedef enum esp_wifi_mode {
    WIFI_STA = 1,
    WIFI_AP,
    WIFI_BOTH
};


class ESP_Wifi {
protected:
    LCT200Serial * _serial;

private:
    char _ackBuf[BUF_LENGTH] = {0};
    int sendCommand(const char * command, const char * param = NULL, bool isQuey = false);
    int readAck(const char * ack, uint16_t timeout = 1000);
    int readAck(const char * ack, const char * error, uint16_t timeout = 1000);
    char * searchBuf(const char * str);
    void clearBuf();

public:
    bool begin(LCT200Serial &serial, uint16_t baud = 115200);

    bool setMode(esp_wifi_mode mode);
    bool connectAP(const char * ssid, const char * pwd);
    bool createAP(const char * ssid, const char * pwd, uint8_t chl, uint8_t ecn);
    bool udpConnect(const char * ip, uint16_t remote_port, uint16_t local_port = 0);
    int udpSend(const char * data, size_t data_size);

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
