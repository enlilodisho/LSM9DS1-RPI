/*
 * RasPi_GPIO
 * Copyright (c) 2020  Enlil Odisho
 * ------------------------------------------------
 * GPIO Class for Raspberry Pi.
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
#include <fcntl.h> // used for open,close,etc.
#include "GPIOBase.hpp"

class RasPi_GPIO: public GPIOBase {
    public:
        /**
         * Exports gpio pin so that it can be used.
         */
        void init(std::string pin) {
            write("/sys/class/gpio/export", pin);
        }

        /**
         * Unexports gpio pin after done using.
         */
        void deinit(std::string pin) {
            write("/sys/class/gpio/unexport", pin);
        }

        /**
         * Sets the gpio pin mode.
         */
        void setPinMode(std::string pin, PinMode pinMode) {
            std::string dir = "in";
            if (pinMode == PinMode.OUTPUT) {
                dir = "out";
            }

            write("/sys/class/gpio/gpio"+pin+"/direction", dir);
        }

        /**
         * Gets and returns the gpio pin mode.
         */
        PinMode getPinMode(std::string pin) {
            std::string dir = read("/sys/class/gpio/gpio"+pin+"/direction", 3);
            if (dir == "out") {
                return PinMode.OUTPUT;
            }
            return PinMode.INPUT;
        }

        /**
         * Sets the gpio pin state.
         */
        void setPinState(std::string pin, PinState pinState) {
            std::string val = "0";
            if (pinState == PinState.HIGH) {
                val = "1";
            }

            write("/sys/class/gpio/gpio"+pin+"/value", val);
        }

        /**
         * Gets and returns the gpio pin state.
         */
        PinState getPinState(std::string pin) {
            std::string state = read("/sys/class/gpio/gpio"+pin+"/value", 1);
            if (state == "1") {
                return PinState.HIGH;
            }
            return PinState.LOW;
        }

    private:
        /**
         * Opens file at path, then writes to it.
         */
        void write(std::string path, std::string val) {
            // Open file.
            int fd = open(path, O_WRONLY);
            if (fd == -1) {
                throw "Unable to open " + path;
            }

            if (write(fd, val.c_str(), val.length()) != val.length) {
                close(fd); // Close file.
                throw "Error writing '" + val + "' to " path;
            }

            // Close the file descriptor.
            close(fd);
        }

        /**
         * Reads from file 'n' chars.
         */
        std::string read(std::string path, int numChars) {
            // Open file.
            int fd = open(path, O_RDONLY);
            if (fd == -1) {
                throw "Unable to open " + path;
            }
            
            char val[numChars+1];
            int readAmt = read(fd, &val, numChars);
            if (readAmt == -1) {
                close(fd); // Close file.
                throw "Error reading from " + path;
            }
            // Add null-terminated char.
            val[readAmt] = '\0';

            return std::string(val);
        }
};
