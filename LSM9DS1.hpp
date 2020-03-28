#ifndef LSM9DS1_HPP
#define LSM9DS1_HPP

#include <stdint.h>
#include "RasPi_I2C.hpp"
#include "LSM9DS1_Settings.h"
//#include "Config.h"

/**
 * I2C device addresses.
 */
#define LSM9DS1_AG_ADDRESS_1    0x6B
#define LSM9DS1_AG_ADDRESS_2    0x6A
#define LSM9DS1_M_ADDRESS_1     0x1E
#define LSM9DS1_M_ADDRESS_2     0x1C

struct SensorData {
    int16_t x;
    int16_t y;
    int16_t z;
};

class LSM9DS1 {
    public:
        LSM9DS1();  // constructor
        ~LSM9DS1(); // destructor

        void set_ag_odr(AG_ODR odr);
        void set_g_scale(G_SCALE scale);
        
        // ctrl_reg9
        void set_drdy_enable_bit(bool value); // turn feature on/off

        struct SensorData get_linear_acc();

        BYTE get_status_reg();
        bool is_temp_available(BYTE status);
        bool is_gyro_available(BYTE status);
        bool is_acc_available(BYTE status);
    private:
        int ag_add, m_add;  // I2C address of acc/gyro and magnetometer.
        RasPi_I2C i2c_ag;
};

#endif /* LSM9DS1_HPP */
