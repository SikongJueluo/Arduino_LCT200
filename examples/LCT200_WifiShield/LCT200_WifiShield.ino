#include <Wire.h>

#include "LCT200.h"

#define DATA_LENGTH 32

bool signal0_status = false;  // 用于判断串口0数据接收完毕，信号刚刚拉低
bool signal1_status = false;  // 用于判断串口1数据接收完毕，信号刚刚拉低
uint8_t data_buf[DATA_LENGTH] = {0};

LCT200 lct;

void setup() {
    Serial.begin(115200);
    Serial.println("Begin to initialize...");
    lct.begin(Wire);

    Serial.println(lct.readConfig(data_buf));
    Serial.printf("REG:");
    for (int i = 0; i < 11; i++) {
        Serial.printf(" %02x ", data_buf[i]);
    }
    Serial.println();
    digitalWrite(5, HIGH);
    data_clean(data_buf, DATA_LENGTH);

    Serial.println("finished...");
}

void loop() {
    uint16_t serial_cnt = 0;
    if (digitalRead(5) == LOW) {
        if (signal0_status == 0) {
            signal0_status = true;

            serial_cnt = lct.Serial0.readBytes(16, data_buf);
            if (serial_cnt == -1) {
                Serial.println("Can't get the LCT200 Serial 0 Data");
            } else {
                Serial.printf("Count_Num:%d\n", serial_cnt);
                Serial.printf("Serial0:%s", data_buf);
                data_clean(data_buf, DATA_LENGTH);
                lct.Serial0.print("Get your message\n");
            }
        }
    } else {
        signal0_status = 0;
    }

    if (digitalRead(4) == LOW) {
        if (signal1_status == 0) {
            signal1_status = true;

            // if(lct.Serial1.available()) {
            //     for (int i = 0; lct.Serial1.available() && i < 16; i++)
            //         data_buf[i] = lct.Serial1.read();
            // }
            serial_cnt = lct.Serial1.readBytes(16, data_buf);
            if (serial_cnt == -1) {
                Serial.println("Can't get the LCT200 Serial 1 Data");
            } else {
                Serial.printf("Count_Num:%d\n", serial_cnt);
                Serial.printf("Serial1:%s", data_buf);
                data_clean(data_buf, DATA_LENGTH);
                lct.Serial1.print("Get your message\n");
            }
        }
    } else {
        signal1_status = 0;
    }
}

void data_clean(uint8_t *data, uint8_t length) {
    for (int i = 0; i < length; i++) {
        data[i] = 0x00;
    }
}