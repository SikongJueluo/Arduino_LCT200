# LCT200 Library for Arduino

[English](./README.MD) [中文](./README_zh.MD)

---

## Contents

- [LCT200 Library for Arduino](#lct200-library-for-arduino)
  - [Contents](#contents)
  - [Introduction](#introduction)
    - [Key Features](#key-features)
  - [Installation](#installation)
    - [Installation via Arduino IDE](#installation-via-arduino-ide)
    - [Manual Installation](#manual-installation)
  - [Completed Features and Future Plans](#completed-features-and-future-plans)
    - [LCT200 Related Content](#lct200-related-content)
    - [Wifi Related Content](#wifi-related-content)
  - [Related Links](#related-links)
  - [Open Source License](#open-source-license)

## Introduction

This repository is an open-source library developed based on the OurEDA ESPWifi Shield, which can be used independently with LCT200 through I2C communication, or combined with Wifi Shield for a better experience, such as easier Wifi, TCP/UDP, MQTT, etc.

LCT200 is a communication chip that can expand 2 independent serial ports through the I2C interface. It also supports reading and writing data of the I2C interface through 2 serial ports.

### Key Features

- Expand 2 independent serial ports functionality through reading and writing via the I2C interface
- Read and write data of the I2C port connecting chips through 2 serial ports
- Cache serial port received data internally, awaiting I2C interface read
- Configurable I2C communication address for LCT200
- Multiple LCT200s can be used in one system, configured with different I2C addresses
- Can put the forwarding chip into low-power mode

## Installation

### Installation via Arduino IDE

Search for LCT200 Arduino and install it.

### Manual Installation

Download the code from this repository and place it in the project directory or Arduino library folder.

The library folder is usually located in the following directories:

Windows: C:\Users\\[User]\Document\Arduino15\libraries

Linux: \home\\[User]\Arduino\libraries

## Completed Features and Future Plans

### LCT200 Related Content

- [X] LCT200 query mode
- [X] LCT200 basic input and output
- [ ] LCT200 interactive mode
- [ ] More convenient interaction for LCT200 (interrupt-related content)

### Wifi Related Content

- [X] Basic Wifi content
- [ ] TCP/UDP
- [ ] MQTT
- [ ] Advanced Wifi settings

## Related Links

[LCT200](http://lcxet.com/product/lct/lct200.html)

[OurEDA Wifi Shield](http://)

## Open Source License

[GPLv3](./LICENSE) © SikongJueluo
