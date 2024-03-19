# LCT200 Library for Arduino

[English](./README.MD)  [中文](./README_zh.MD)

---

## 目录

- [介绍](#介绍)
- [安装](#安装)
- [已完成功能和未来计划](#已完成的功能及未来计划)
- [相关连接](#相关链接)
- [开源协议](#开源协议)

## 介绍

本仓库是基于 OurEDA ESPWifi Shield 开发的开源库，可以单独使用与 LCT200 通过I2C交流，也可以结合 Wifi Shield 一并使用，以便获得更好的体验，例如：更方便的Wifi、TCP/UDP、MQTT等等。

LCT200 是一款可以通过 I2C 接口通讯，拓展 2 路独立串口的通讯芯片。它同时也支持通过2路串口读写 I2C 接口的数据。

### 主要功能

- 通过对 I2C 接口读写实现拓展 2 路独立串口功能
- 通过读写 2 路串口实现读写 I2C 端口连接芯片的数据
- 将串口接收到的数据缓存到芯片内部，等待 I2C 接口读取
- 可以配置 LCT200 的 I2C 通讯地址
- 可以在一个系统中使用多个 LCT200，配置为不同 I2C 地址即可
- 可以使转发芯片进入低功耗模式

## 安装

### 通过 Arduino IDE 安装

搜索 LCT200 Arduino 查找并安装。

### 手动安装

下载本仓库代码，并将其放于工程目录下或者放于Arduino的库文件夹下。

库文件夹通常位于以下目录：

Windows：C:\Users\\[User]\Document\Arduino15\libraries

Linux: \home\\[User]\Arduino\libraries

## 已完成的功能及未来计划

### LCT200 相关内容

- [X] LCT200 查询模式
- [X] LCT200 基本输入输出
- [ ] LCT200 交互模式
- [ ] LCT200 更方便的交互(中断相关内容)

### Wifi 相关内容

- [X] Wifi 基本内容
- [ ] TCP/UDP
- [ ] MQTT
- [ ] Wifi 高级设置

## 相关链接

[LCT200](http://lcxet.com/product/lct/lct200.html)

[OurEDA Wifi Shield](http://)

## 开源协议

[GPLv3](./LICENSE) © SikongJueluo
