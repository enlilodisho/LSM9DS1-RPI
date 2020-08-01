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
#ifndef RASPI_GPIO_HPP
#define RASPI_GPIO_HPP

#include <fcntl.h> // used for open,close,etc.
#include <unistd.h> // used for usleep
// for exceptions:
#include <stdexcept>
#include <string.h>
#include <errno.h>

#include "GPIOBase.hpp"

class RasPi_GPIO: public GPIOBase {
    public:
        /**
         * Exports gpio pin so that it can be used.
         */
        void init(std::string pin) {
            writeFile("/sys/class/gpio/export", pin);
            usleep(100000); // sleep for 100 miliseconds for export to complete
        }

        /**
         * Unexports gpio pin after done using.
         */
        void deinit(std::string pin) {
            writeFile("/sys/class/gpio/unexport", pin);
            usleep(100000); // sleep for 100 miliseconds for unexport to complete
        }

        /**
         * Sets the gpio pin mode.
         */
        void setPinMode(std::string pin, PinMode pinMode) {
            std::string dir = "in";
            if (pinMode == OUTPUT) {
                dir = "out";
            }

            writeFile("/sys/class/gpio/gpio"+pin+"/direction", dir);
        }

        /**
         * Gets and returns the gpio pin mode.
         */
        PinMode getPinMode(std::string pin) {
            std::string dir = readFile("/sys/class/gpio/gpio"+pin+"/direction", 3);
            if (dir == "out") {
                return OUTPUT;
            }
            return INPUT;
        }

        /**
         * Sets the gpio pin state.
         */
        void setPinState(std::string pin, PinState pinState) {
            std::string val = "0";
            if (pinState == HIGH) {
                val = "1";
            }

            writeFile("/sys/class/gpio/gpio"+pin+"/value", val);
        }

        /**
         * Gets and returns the gpio pin state.
         */
        PinState getPinState(std::string pin) {
            std::string state = readFile("/sys/class/gpio/gpio"+pin+"/value", 1);
            if (state == "1") {
                return HIGH;
            }
            return LOW;
        }

    private:
        /**
         * Opens file at path, then writes to it.
         */
        void writeFile(std::string path, std::string val) {
            // Open file.
            int fd = open(path.c_str(), O_WRONLY);
            if (fd == -1) {
                throw std::runtime_error(std::string("Unable to open "+path+". "
                                    + strerror(errno)));
            }

            if (write(fd, val.c_str(), val.length()) != val.length()) {
                close(fd); // Close file.
                throw std::runtime_error(std::string("Error writing '"+val
                                    +"' to "+path+". " + strerror(errno)));
            }

            // Close the file descriptor.
            close(fd);
        }

        /**
         * Reads from file 'n' chars.
         */
        std::string readFile(std::string path, int numChars) {
            // Open file.
            int fd = open(path.c_str(), O_RDONLY);
            if (fd == -1) {
                throw std::runtime_error(std::string("Unable to open "+path+". "
                                    + strerror(errno)));
            }
            
            char val[numChars+1];
            int readAmt = read(fd, &val, numChars);
            if (readAmt == -1) {
                close(fd); // Close file.
                throw std::runtime_error(std::string("Error reading from "+path+". "
                                    + stderror(errno)));
            }
            // Add null-terminated char.
            val[readAmt] = '\0';

            return std::string(val);
        }
};

#endif /* RASPI_GPIO_HPP */
