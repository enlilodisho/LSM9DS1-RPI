/*
 * GPIOBase
 * Copyright (c) 2020  Enlil Odisho
 * ------------------------------------------------
 * Abstract class for GPIO Control.
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
#include <string>

class GPIOBase {
    public:
        /**
         * Initializes GPIO pin.
         */
        virtual void init(std::string pin) {}

        /**
         * De-initializes GPIO pin.
         */
        virtual void deinit(std::string pin) {}

        /**
         * Enum for gpio pin modes.
         */
        enum PinMode {
            INPUT,
            OUTPUT
        };

        /**
         * Set the gpio pin as either INPUT or OUTPUT.
         */
        virtual void setPinMode(std::string pin, PinMode pinMode) = 0;

        /**
         * Gets and returns the current gpio pin mode.
         */
        virtual PinMode getPinMode(std::string pin) = 0;

        /**
         * Enum for gpio pin states.
         */
        enum PinState {
            HIGH,
            LOW
        };

        /**
         * Set gpio pin state as either HIGH or LOW.
         */
        virtual void setPinState(std::string pin, PinState pinState) = 0;

        /**
         * Gets and returns the gpio pin state.
         */
        virtual PinState getPinState(std::string pin) = 0;
};
