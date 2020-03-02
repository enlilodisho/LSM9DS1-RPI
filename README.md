# LSM9DS1 Library [WIP]

Library for the LSM9DS1 IMU.

--------------------------------------------------

### Introduction

This is a C++ library for the ST Microelectronics LSM9DS1 inertial module. This module has 9DOF (3D accelerometer, 3D gyroscope, and 3d magnetometer) and supports both I2C and SPI for communication.

This library is planned to eventually support all features of the LSM9DS1, including both I2C and SPI. It was designed to be used on a Raspberry Pi, but should work on any other device which supports I2C or SPI by creating a new class that implements I2C/SPIBase.hpp and GPIOBase.hpp.


### Development Progress

At the moment, this library is not yet functional to be used in your project. As I implement features, I will update the list of available features below.

I will first begin by implementing I2C. SPI support will come later.

##### Basic Capabilities
* [ ] I2C Support
* [ ] SPI Support
* [ ] Read accelerometer data
* [ ] Read gyroscope data
* [ ] Read magnetometer data


### License
This code is licensed under the **MIT License**.

Basically, you may use this code however you want, but it comes with no warranty nor liability.

See LICENSE.md for full license.
