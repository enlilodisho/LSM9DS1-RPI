/*
 * LSM9DS1
 * Copyright (c) 2020  Enlil Odisho
 * ------------------------------------------------
 * Class for LSM9DS1 sensor.
 * 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
#include "LSM9DS1.hpp"
#include "LSM9DS1_Registers.h"
#include <iostream> // logging

/**
 * Constructor.
 */
LSM9DS1::LSM9DS1() {
    // TODO change the device address by changing pin to high
    ag_add = LSM9DS1_AG_ADDRESS_1;
    i2c_ag.init(ag_add);
    std::cout << "Initialized LSM9DS1.\n";
}

/**
 * Destructor.
 */
LSM9DS1::~LSM9DS1() {
    i2c_ag.deinit();
    std::cout << "Deinitialized LSM9DS1.\n";
}

/**
 * Set the ODR for Acc and Gyro.
 */
void LSM9DS1::set_ag_odr(AG_ODR odr) {
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG6_XL);
    BYTE new_regv = (cur_regv & ~(AG_ODR::AG_ODR_MASK)) | odr;
    i2c_ag.writeByte(CTRL_REG6_XL, new_regv);
}
