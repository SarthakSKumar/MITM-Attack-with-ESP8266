# MITM Attack Demonstration with ESP8266

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![ESP8266](https://img.shields.io/badge/ESP8266-NodeMCU-blue.svg)](https://www.espressif.com/en/products/socs/esp8266)
[![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-blue.svg)](https://www.arduino.cc/)

This repository demonstrates a Man-in-the-Middle (MITM) attack using ESP8266 modules. The project involves capturing data, and showing ways to mitigate such attacks.

## Overview

In this project, we demonstrate an MITM attack by intercepting data from another ESP8266 client device. The client device sends sensor data to a Python server, and the rogue access point attempts to capture this data.

## Hardware Requirements

- 2 x ESP8266 modules (NodeMCU or similar)
- DHT11 Temperature and Humidity Sensor
- MQ6 Gas Sensor
- Jumper wires
- Breadboard
- USB cables for programming and power

## Software Requirements

- Arduino IDE with ESP8266 board support
- Python 3.x
- Wireshark (for packet analysis)

## Clone the Repository

```bash
git clone [https://github.com/yourusername/mitm-attack-demo.git](https://github.com/SarthakSKumar/MITM-Attack-with-ESP8266)
cd MITM-Attack-with-ESP8266
