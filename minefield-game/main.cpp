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
#include <ctime>
#include <sstream>
#include <stdexcept>

std::string toString(int number)
{
  if (number == -1)
    return "*";
  std::ostringstream os;
  os << number;
  return os.str();
}

void showMinefield(const Minefield& minefield, bool filterView)
{
  std::size_t width = minefield.getWidth();
  std::size_t height = minefield.getHeight();

  for (std::size_t y = 0; y < height; ++y)
  {
    for (std::size_t x = 0; x < width; ++x)
    {
      int value = minefield.getValue(x, y);
      if (minefield.isVisible(x, y) || !filterView)
        std::cout << toString(value) + " ";
      else
        std::cout << "_ ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main()
{
  std::srand((unsigned int)time(0));
  std::cout << "*** Mine field ***" << std::endl;
  std::cout << "Enter the size (width x height): " << std::endl;
  std::size_t width = 0, height = 0;
  std::cin >> width >> height;
  std::cout << "Enter the number of bombs: " << std::endl;
  std::size_t bombs = 0;
  std::cin >> bombs;
  
  try {
    Minefield field(width, height, bombs);
    std::size_t x = 0, y = 0;
    bool stop = false;
    while (!stop)
    {
      showMinefield(field, true);
      std::cin >> x >> y;
      if (field.test(x, y))
      {
        std::cout << "OPS... BOMB! :-(" << std::endl;
        break;
      }
      if (field.isComplete())
      {
        std::cout << "CONGRATULATIONS: GAME SUCCESFULLY COMPLETED!" << std::endl;
        break;
      }
    }
    showMinefield(field, false);
  }
  catch(std::exception& e)
  {
    std::cout << "Error : " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cout << "Unknown error." << std::endl;
  }

  return 0;
}
