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
    AG_ODR_0    = 0,      // Sensor off
    AG_ODR_14_9 = 0x20,   // 14.9 Hz
    AG_ODR_59_5 = 0x40,   // 59.5 Hz
    AG_ODR_119  = 0x60,   // 119 Hz
    AG_ODR_238  = 0x80,   // 238 Hz
    AG_ODR_476  = 0xA0,   // 476 Hz
    AG_ODR_952  = 0xC0    // 952 Hz
};

/**
 * Mag ODR Setting.
 */
enum M_ODR {
    M_ODR_MASK  = 0x1C,
    M_ODR_0_625 = 0,      // 0.625 Hz
    M_ODR_1_25  = 0x04,   // 1.25 Hz
    M_ODR_2_5   = 0x08,   // 2.5 Hz
    M_ODR_5     = 0x0C,   // 5 Hz
    M_ODR_10    = 0x10,   // 10 Hz
    M_ODR_20    = 0x14,   // 20 Hz
    M_ODR_40    = 0x18,   // 40 Hz
    M_ODR_80    = 0x1C    // 80 Hz
};

/**
 * Acc Scale Setting.
 */
enum A_SCALE {
    A_SCALE_MASK = 0x18,
    A_SCALE_2    = 0,     // +/- 2G
    A_SCALE_4    = 0x10,  // +/- 4G
    A_SCALE_8    = 0x18,  // +/- 8G
    A_SCALE_16   = 0x08   // +/- 16G
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

/**
 * Mag Scale Setting.
 */
enum M_SCALE {
    M_SCALE_MASK = 0x60,
    M_SCALE_4   = 0,      // +/- 4 gauss
    M_SCALE_8   = 0x20,   // +/- 8 gauss
    M_SCALE_12  = 0x40,   // +/- 12 gauss
    M_SCALE_16  = 0x60    // +/- 16 gauss
};

/**
 * Mag Mode Setting.
 */
enum M_MODE {
    M_MODE_MASK         = 0x03,
    M_MODE_CONTINUOUS   = 0,
    M_MODE_SINGLE       = 0x01,
    M_MODE_POWERDOWN    = 0x03
};

/**
 * Mag Temperature compensation.
 */
enum M_TEMP_COMPENSATE {
    M_TEMP_COMPENSATE_MASK = 0x80
};

/**
 * Mag Operative mode.
 */
enum M_XY_PERFORMANCE {
    M_XY_PERFORMANCE_MASK       = 0x60,
    M_XY_PERFORMANCE_LOWPOWER   = 0,
    M_XY_PERFORMANCE_MEDIUM     = 0x20,
    M_XY_PERFORMANCE_HIGH       = 0x40,
    M_XY_PERFORMANCE_ULTRA      = 0x60
};
enum M_Z_PERFORMANCE {
    M_Z_PERFORMANCE_MASK        = 0x0C,
    M_Z_PERFORMANCE_LOWPOWER    = 0,
    M_Z_PERFORMANCE_MEDIUM      = 0x04,
    M_Z_PERFORMANCE_HIGH        = 0x08,
    M_Z_PERFORMANCE_ULTRA       = 0x0C
};

/**
 * Status register masks.
 */
enum AG_STATUS {
    AG_STATUS_TEMP_AVAIL = 0x04,
    AG_STATUS_GYRO_AVAIL = 0x02,
    AG_STATUS_ACC_AVAIL  = 0x01
};

/**
 * FIFO settings. (in FIFO_CTRL)
 */
enum FIFO_MODE {
    FIFO_MODE_MASK                    = 0xE0,
    FIFO_MODE_BYPASS                  = 0,
    FIFO_MODE_ON                      = 0x20,
    FIFO_MODE_ON_CONTINUOUS           = 0xC0,
    FIFO_MODE_ON_CONTINUOUS_TO_FIFO   = 0x60,
    FIFO_MODE_ON_BYPASS_TO_CONTINUOUS = 0x80
};
enum FIFO_THRESHOLD {
    FIFO_THRESHOLD_MASK     = 0x1F
};

/**
 * FIFO status register.
 */
enum FIFO_STATUS {
    FIFO_THRESHOLD_STATUS_MASK  = 0x80,
    FIFO_OVERRUN_STATUS_MASK    = 0x40,
    FIFO_NUM_UNREAD_MASK        = 0x3F
};

/**
 * Set INT1 Pin.
 */
enum INT1_MODE {
    INT1_OFF                = 0,
    INT1_GYRO               = 0x80,
    INT1_ACC                = 0x40,
    INT1_FSS5               = 0x20,
    INT1_OVERRUN            = 0x10,
    INT1_FIFO_THRESHOLD     = 0x08,
    INT1_BOOT_STATUS        = 0x04,
    INT1_GYRO_DATA_READY    = 0x02,
    INT1_ACC_DATA_READY     = 0x01
};

/**
 * Set INT2 Pin.
 */
enum INT2_MODE {
    INT2_OFF               = 0,
    INT2_ACTIVITY          = 0x80,
    INT2_FSS5              = 0x20,
    INT2_OVERRUN           = 0x10,
    INT2_FIFO_THRESHOLD    = 0x08,
    INT2_TEMP_DATA_READY   = 0x04,
    INT2_GYRO_DATA_READY   = 0x02,
    INT2_ACC_DATA_READY    = 0x01
};

/**
 * CTRL_REG9 Settings.
 */
enum CTRL9_SETTINGS {
    CTRL9_SLEEP_GYRO    = 0x40,
    CTRL9_FIFO_TEMP_EN  = 0x10,
    CTRL9_DRDY_EN       = 0x08,
    CTRL9_I2C_DISABLE   = 0x04,
    CTRL9_FIFO_EN       = 0x02,
    CTRL9_STOP_ON_FTH   = 0x01
};

#endif /* LSM9DS1_SETTINGS_H */
