#ifndef LSM9DS1_HPP
#define LSM9DS1_HPP

#include "RasPi_I2C.hpp"
#include "LSM9DS1_Settings.h"
#include "Config.h"

/**
 * I2C device addresses.
 */
#define LSM9DS1_AG_ADDRESS_1    0x6B
#define LSM9DS1_AG_ADDRESS_2    0x6A
#define LSM9DS1_M_ADDRESS_1     0x1E
#define LSM9DS1_M_ADDRESS_2     0x1C

class LSM9DS1 {
    public:
        LSM9DS1();  // constructor
        ~LSM9DS1(); // destructor

        void set_ag_odr(AG_ODR odr);
        void set_g_scale(G_SCALE scale);
    private:
        int ag_add, m_add;  // I2C address of acc/gyro and magnetometer.
        RasPi_I2C i2c_ag;
};

#endif /* LSM9DS1_HPP */
