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
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG1_G);
    BYTE new_regv = (cur_regv & ~(AG_ODR::AG_ODR_MASK)) | odr;
    i2c_ag.writeByte(CTRL_REG1_G, new_regv);
}

/**
 * Set the scale for Acc.
 */
void LSM9DS1::set_a_scale(A_SCALE scale) {
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG6_XL);
    BYTE new_regv = (cur_regv & ~(A_SCALE::A_SCALE_MASK)) | scale;
    i2c_ag.writeByte(CTRL_REG6_XL, new_regv);
}

/**
 * Set the Scale for Gyro.
 */
void LSM9DS1::set_g_scale(G_SCALE scale) {
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG1_G);
    BYTE new_regv = (cur_regv & ~(G_SCALE::G_SCALE_MASK)) | scale;
    i2c_ag.writeByte(CTRL_REG1_G, new_regv);
}

/**
 * Set the int1 pin.
 */
void LSM9DS1::set_int1_pin(INT1_MODE int1Mode) {
    BYTE new_regv = 0;
    if (int1Mode != INT1_OFF) {
        new_regv |= int1Mode;
    }
    i2c_ag.writeByte(INT1_CTRL, new_regv);
}

/**
 * Set the int2 pin.
 */
void LSM9DS1::set_int2_pin(INT2_MODE int2Mode) {
    BYTE new_regv = 0;
    if (int2Mode != INT2_OFF) {
        new_regv |= int2Mode;
    }
    i2c_ag.writeByte(INT2_CTRL, new_regv);
}

/**
 * Turn data available bit on/off.
 */
void LSM9DS1::set_drdy_enable_bit(bool value) {
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG9);
    BYTE new_regv = cur_regv;
    if (value) {
        new_regv |= CTRL9_DRDY_EN;
    } else {
        new_regv &= ~CTRL9_DRDY_EN;
    }
    i2c_ag.writeByte(CTRL_REG9, new_regv);
}

/**
 * Get Data Available Bits.
 */
BYTE LSM9DS1::get_data_status_reg() {
    return i2c_ag.readByte(STATUS_REG_1);
}

/**
 * Turn FIFO feature on/off.
 */
void LSM9DS1::set_fifo_enable_bit(bool value) {
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG9);
    BYTE new_regv = cur_regv;
    if (value) {
        new_regv |= CTRL9_FIFO_EN;
    } else {
        new_regv &= ~CTRL9_FIFO_EN;
    }
    i2c_ag.writeByte(CTRL_REG9, new_regv);
}

/**
 * Enable/disable storing of temperature in FIFO.
 */
void LSM9DS1::set_fifo_temp_enable_bit(bool value) {
    BYTE cur_regv = i2c_ag.readByte(CTRL_REG9);
    BYTE new_regv = cur_regv;
    if (value) {
        new_regv |= CTRL9_FIFO_TEMP_EN;
    } else {
        new_regv &= ~CTRL9_FIFO_TEMP_EN;
    }
    i2c_ag.writeByte(CTRL_REG9, new_regv);
}

/**
 * Change FIFO mode.
 */
void LSM9DS1::set_fifo_mode(FIFO_MODE mode) {
    BYTE cur_regv = i2c_ag.readByte(FIFO_CTRL);
    BYTE new_regv = (cur_regv & ~(FIFO_MODE_MASK)) | mode;
    i2c_ag.writeByte(FIFO_CTRL, new_regv);
}

/**
 * Set the FIFO threshold level.
 */
void LSM9DS1::set_fifo_threshold(uint8_t threshold) {
    if (threshold < 0 || threshold > 31) {
        threshold = 0;
    }
    BYTE cur_regv = i2c_ag.readByte(FIFO_CTRL);
    BYTE new_regv = (cur_regv & ~(FIFO_THRESHOLD_MASK)) | (threshold & FIFO_THRESHOLD_MASK);
    i2c_ag.writeByte(FIFO_CTRL, new_regv);
}

BYTE LSM9DS1::get_fifo_status() {
    return i2c_ag.readByte(FIFO_SRC);
}

/**
 * Return whether FIFO filling is equal or higher than threshold level.
 */
bool LSM9DS1::is_fifo_threshold_reached(BYTE fifoStatus) {
    if (fifoStatus & FIFO_THRESHOLD_STATUS_MASK == FIFO_THRESHOLD_STATUS_MASK) {
        return true;
    }
    return false;
}

/**
 * Return whether FIFO overrun has occured.
 */
bool LSM9DS1::did_fifo_overrun(BYTE fifoStatus) {
    if (fifoStatus & FIFO_OVERRUN_STATUS_MASK == FIFO_OVERRUN_STATUS_MASK) {
        return true;
    }
    return false;
}

/**
 * Return the number of unread samples stored into FIFO.
 */
uint8_t LSM9DS1::get_num_fifo_unread(BYTE fifoStatus) {
    BYTE numUnread = fifoStatus & FIFO_NUM_UNREAD_MASK;
    return numUnread;
}

/**
 * Return whether temperature data is available.
 */
bool LSM9DS1::is_temp_available(BYTE status) {
    if (status & AG_STATUS_TEMP_AVAIL == AG_STATUS_TEMP_AVAIL) {
        return true;
    }
    return false;
}

/**
 * Return whether gyroscope data is available.
 */
bool LSM9DS1::is_gyro_available(BYTE status) {
    if (status & AG_STATUS_GYRO_AVAIL == AG_STATUS_GYRO_AVAIL) {
        return true;
    }
    return false;
}

/**
 * Return whether accelerometer data is available.
 */
bool LSM9DS1::is_acc_available(BYTE status) {
    if (status & AG_STATUS_ACC_AVAIL == AG_STATUS_ACC_AVAIL) {
        return true;
    }
    return false;
}

/**
 * Gets and returns the gyroscope data from the output registers.
 * Note: X = pitch, y = roll, Z = yaw (stated in datasheet)
 */
struct SensorData LSM9DS1::get_angular_rate() {
    struct SensorData gyro;
    BYTE* data = i2c_ag.readBytes(OUT_X_L_G, 6);
    gyro.x = (data[1] << 8) | data[0];
    gyro.y = (data[3] << 8) | data[2];
    gyro.z = (data[5] << 8) | data[4];
    delete data;
    return gyro;
}

/**
 * Gets and returns the linear acceleration from the output registers.
 */
struct SensorData LSM9DS1::get_linear_acc() {
    struct SensorData acc;
    BYTE* data = i2c_ag.readBytes(OUT_X_L_XL, 6);
    acc.x = (data[1] << 8) | data[0];
    acc.y = (data[3] << 8) | data[2];
    acc.z = (data[5] << 8) | data[4];
    delete data;
    return acc;
}

/**
 * Gets and returns the temperature from the output registers.
 */
int16_t LSM9DS1::get_temperature() {
    int16_t temp;
    BYTE* data = i2c_ag.readBytes(OUT_TEMP_L, 2);
    temp = (data[1] << 8) | data[0];
    delete data;
    return temp;
}
