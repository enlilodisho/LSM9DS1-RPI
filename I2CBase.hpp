/*
 * I2CBase
 * Copyright (c) 2020  Enlil Odisho
 * ------------------------------------------------
 * Abstract class for I2C communication.
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
#ifndef I2C_BASE_HPP
#define I2C_BASE_HPP

/**
 * Use the term 'BYTE' to refer to type 'unsigned char'.
 */
typedef unsigned char BYTE;

class I2CBase {
    public:
        /**
         * Initialize I2C.
         */
        virtual void init(BYTE dev_add) {}

        /**
         * De-initialize I2C.
         */
        virtual void deinit() {}

        /**
         * Reads and returns byte stored in register at a particular address.
         */
        virtual BYTE readByte(BYTE reg_add) = 0;

        /**
         * Reads and returns multiple bytes stored in consecutive registers,
         * starting from a particular address.
         */
        virtual BYTE* readBytes(BYTE reg_add, int num) = 0;

        /**
         * Writes to a register at a particular address.
         */
        virtual void writeByte(BYTE reg_add, BYTE reg_val) = 0;
};

#endif /* I2C_BASE_HPP */
