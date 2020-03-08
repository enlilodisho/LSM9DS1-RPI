/*
 * LSM9DS1 Settings
 * Copyright (c) 2020  Enlil Odisho
 * ------------------------------------------------
 * Contains the customizable settings for the LSM9DS1 sensor.
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
#ifndef LSM9DS1_SETTINGS_H
#define LSM9DS1_SETTINGS_H

/**
 * Acc&Gyro ODR Setting.
 */
enum AG_ODR {
    AG_ODR_MASK = 0xE0,
    AG_ODR_14_9 = 0x20,   // 14.9 Hz
    AG_ODR_59_5 = 0x40,   // 59.5 Hz
    AG_ODR_119  = 0x60,   // 119 Hz
    AG_ODR_238  = 0x80,   // 238 Hz
    AG_ODR_476  = 0xA0,   // 476 Hz
    AG_ODR_952  = 0xC0    // 952 Hz
};

/**
 * Gyro Scale Setting.
 */
enum G_SCALE {
    G_SCALE_MASK = 0x18,
    G_SCALE_245  = 0,     // 245 dps
    G_SCALE_500  = 0x08,  // 500 dps
    G_SCALE_2000 = 0x18   // 2000 dps
};

#endif /* LSM9DS1_SETTINGS_H */
