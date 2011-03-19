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

#include "Minefield.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

//------------------------------------
Minefield::Minefield(std::size_t width, std::size_t height, std::size_t bombs)
  : bombs_(bombs), mineTable_(width, height), openTable_(width, height)
{
  if (width == 0 || height == 0)
    throw std::invalid_argument("Field dimensions cannot be 0");
  init();
}

//------------------------------------
void Minefield::init()
{
  std::size_t width = mineTable_.getWidth();
  std::size_t height = mineTable_.getHeight();
  if (bombs_ < 1 || bombs_ > width * height - 1)
    throw std::invalid_argument("Wrong number of bombs");

  for (std::size_t i = 0; i < bombs_; )              //mette le bombe nella matrice
  {
    std::size_t px = std::size_t(rand() % width);
    std::size_t py = std::size_t(float(height)*rand()/(RAND_MAX+1.0));
//    std::cout <<"Bomb #" << i <<":  "<< px << ", " << py << std::endl;
    if (mineTable_(px, py) != -1)
    {
      mineTable_(px, py) = -1;
      ++i;
    }
  }
  // Insert numbers
  for (std::size_t x = 0; x < width; ++x)
    for (std::size_t y = 0; y < height; ++y)
    {
      unsigned int counter = 0;
      if (mineTable_(x, y) != -1)
      {
        if (x != 0 && y != 0 && mineTable_(x-1, y-1) == -1) ++counter; //in alto a sinistra
        if (x != 0 && mineTable_(x-1, y) == -1) ++counter;   // a sinistra
        if (x != 0 && y != height-1 && mineTable_(x-1, y+1) == -1) ++counter; // in basso a sinistra
        if (y != height-1 && mineTable_(x, y+1) == -1) ++counter;   // in basso
        if (x != width-1 && y != height-1 && mineTable_(x+1, y+1) == -1) ++counter; //in basso a destra
        if (x != width-1 && mineTable_(x+1, y) == -1) ++counter;   // a destra
        if (x != width-1 && y != 0 && mineTable_(x+1, y-1) == -1) ++counter; // in alto a destra
        if (y != 0 && mineTable_(x, y-1) == -1) ++counter;   // in alto
        mineTable_(x, y) = counter;
      }
    }
}
//------------------------------------
void Minefield::open(std::size_t x, std::size_t y)
{
  if (openTable_(x, y) == 1 || mineTable_(x, y) == -1)
    return;

  openTable_(x, y) = 1;

  if (mineTable_(x, y) != 0)
    return;

  std::size_t width = mineTable_.getWidth();
  std::size_t height = mineTable_.getHeight();

  if (x != 0 && y != 0 && mineTable_(x-1, y-1) != -1)
      open(x-1, y-1);        //in alto a sinistra
  if (x != 0 && mineTable_(x-1, y) != -1)
      open(x-1, y);          //a sinistra
  if (x != 0 && y != height-1 && mineTable_(x-1, y+1) != -1)
    open(x-1, y+1);     //in basso a sinistra
  if (y != height-1 && mineTable_(x, y+1) != -1)
    open(x, y+1);                 //in basso
  if (x != width-1 && y != height-1 && mineTable_(x+1, y+1) != -1)
    open(x+1, y+1);  //in basso a destra
  if (x != width-1 && mineTable_(x+1, y) != -1)
    open(x+1, y);                 //a destra
  if (x != width-1 && y != 0 && mineTable_(x+1, y-1) != -1)
    open(x+1, y-1);     //in alto a destra
  if (y != 0 && mineTable_(x, y-1) != -1)
    open(x, y-1);                    // in alto
}
//------------------------------------
bool Minefield::isComplete() const
{
  std::size_t width = mineTable_.getWidth();
  std::size_t height = mineTable_.getHeight();
  std::size_t counter = 0;
  for (std::size_t x = 0; x < width; ++x)
    for (std::size_t y = 0; y < height; ++y)
    {
      if (openTable_(x, y) == 1)
        ++counter;
    }
  return counter + bombs_ == width * height;
}
//------------------------------------
std::size_t Minefield::getWidth() const
{
  return mineTable_.getWidth();
}
std::size_t Minefield::getHeight() const
{
  return mineTable_.getHeight();
}
//------------------------------------
bool Minefield::isVisible(std::size_t x, std::size_t y) const
{
  return openTable_(x, y) == 1;
}
//------------------------------------
int Minefield::getValue(std::size_t x, std::size_t y) const
{
  return mineTable_(x, y);
}
//------------------------------------
bool Minefield::test(std::size_t x, std::size_t y)
{
  if (mineTable_(x, y) == -1)
    return true; // bomb found
  open(x, y);
  return false;  // bomb not found
}
//------------------------------------
