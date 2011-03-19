/*
The MIT License

Copyright (c) 2010 Marco Ambu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

/*
 * File:   Minefield.h
 * Author: Marco Ambu
 *
 * Created on August 9, 2010, 11:05 AM
 */

#ifndef _MINEFIELD_H
#define _MINEFIELD_H

#include "Table.h"

class Minefield
{
public:
    Minefield(std::size_t width, std::size_t height, std::size_t bombs);

    bool test(std::size_t x, std::size_t y);
    bool isComplete() const;

    int getValue(std::size_t x, std::size_t y) const;
    bool isVisible(std::size_t x, std::size_t y) const;
    std::size_t getWidth() const;
    std::size_t getHeight() const;

private:
    void init();
    void open(std::size_t x, std::size_t y);

private:
    std::size_t bombs_;
    Table mineTable_;
    Table openTable_;
};

#endif
