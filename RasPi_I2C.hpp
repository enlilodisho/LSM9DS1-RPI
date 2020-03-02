/*
 * RasPi_I2C
 * Copyright (c) 2020  Enlil Odisho
 * ------------------------------------------------
 * I2C Class for Raspberry Pi.
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
#include <linux/i2c-dev.h>
#include <sys/ioctl.h> // for open

class RasPi_I2C: public I2CBase {
    public:
        /**
         * Opens the I2C device file.
         */
        void init(BYTE dev_add) {
            // Open the I2C bus.
            dev_fd = open("/dev/i2c-1", O_RDWR);
            if (dev_fd == -1) {
                throw "Invalid file.";
            }

            // Set up I2C device.
            if (ioctl(dev_fd, I2C_SLAVE, dev_add) == -1) {
                throw "Invalid I2C device.";
            }

            // Save I2C device address.
            this->dev_add = dev_add;
        }

        /**
         * Closes the I2C device file.
         */
        void deinit() {
            fsync(dev_fd);
            if (close(dev_fd) == -1) {
                throw "Can't close file.";
            }
        }

        /**
         * Reads and returns a BYTE from a register on the I2C device.
         */
        BYTE readByte(BYTE reg_add) {
            return i2c_smbus_read_byte_data(dev_fd, reg_add);
        }

        /**
         * Reads and returns 'n' BYTEs starting from a register on the I2C
         * device.
         */
        BYTE[] readBytes(BYTE reg_add, int numBytes) {
            BYTE vals[numBytes];
            actNumBytes = i2c_smbus_read_i2d_block_data(dev_fd, reg_add,
                    numBytes, &vals);
            if (actNumBytes < numBytes) {
                // Read fewer bytes than requested, trim vals array.
                BYTE valsTrimmed[actNumBytes];
                for (int i = 0; i < actNumBytes; i++) {
                    valsTrimmed[i] = vals[i];
                }
                return valsTrimmed;
            }
            return vals;
        }

        /**
         * Writes a BYTE to a register on the I2C device.
         */
        void writeByte(BYTE reg_add, BYTE reg_val) {
            i2c_smbus_write_byte_data(dev_fd, reg_add, reg_val);
        }

    private:
        /**
         * File descriptor for I2C device.
         */
        int dev_fd = -1;
        
        /**
         * I2C Device Address.
         */
        BYTE dev_add;
};
