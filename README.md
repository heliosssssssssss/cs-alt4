# **Computer Science 2025 - ALT4 Embedded Systems Project**
[![Arduino](https://img.shields.io/badge/Made%20with-Arduino-blue?logo=arduino)](https://www.arduino.cc/)
[![C++](https://img.shields.io/badge/Language-C++-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Embedded Systems](https://img.shields.io/badge/Field-Embedded%20Systems-orange)](#)

## Measure medical data using MAX30102 and an Audrino Uno Rev3

This is my final project for the ALT4 (Embedded Systems) as a fifth year, it demostrates the usage of embedded systems and working with microcontrollers to achieve real time results.

 Using this project, you are able to display realtime data (heartbeat, oxygen saturation, and temperature) on a physical screen allowing the end user to see. 

 
## Frequently Asked Questions

#### Does this work with all MAX3010x's (MAX30102, MAX30105)?
No, this only works with the Gravity MAX30102 sensor,  you may need to use SparkFun or another module if you are working with a different MAX30102 

#### How is the medical data received?
All medical data (is obviously subject to bias) and shouldn't be treated as proper medical data because I have not bothered to work with RAW IR data and let the DFRobot_BloodOxygen_S libary do all the heavy maths.

#### Can I use/fork this project? 
Of course. I would've made this repository private if I didn't want anyone using it. You can use it and fork it as much as you want even send pull requests to code fixes because my C++ skills aren't the best (compared to python & typescript)

## Debug Mode

Debug mode allows you to scan for all I2C connections and get there addresses. I only added this because it would be hard to determine if a issue was code-based or because of my breadboard wires.

```bash
  #define addr_scan_debug true (will scan addresses)
  #define addr_scan_debug false (will not scan addresses)
```


