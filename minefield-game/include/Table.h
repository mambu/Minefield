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
 * File:   Table.h
 * Author: Marco Ambu
 *
 * Created on August 9, 2010, 11:54 AM
 */

#ifndef _TABLE_H
#define	_TABLE_H

#include <vector>
#include <stdexcept>

class Table
{
public:
  Table(std::size_t width, std::size_t height)
          : width_(width), height_(height)
  {
      for (std::size_t x = 0; x < width_; ++x)
      {
        table_.push_back(std::vector<int>(height, 0));
      }
  }

  std::size_t getWidth() const { return width_; }
  std::size_t getHeight() const { return height_; }

  int operator()(std::size_t x, std::size_t y) const {
    if (x >= width_ || y >= height_)
      throw std::range_error("Index out of bounds");
    return table_[x][y]; }
  int& operator()(std::size_t x, std::size_t y) {
    if (x >= width_ || y >= height_)
      throw std::range_error("Index out of bounds");
    return table_[x][y];
  }

private:
  std::size_t width_, height_;

  std::vector<std::vector<int> > table_;
};

#endif	/* _TABLE_H */

