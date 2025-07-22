//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "IostreamConnection.h"

#include <iostream>

int IostreamConnection::tryReadOne()
{
  char result;
  std::cin.get(result);
  if(std::cin)
  {
    return static_cast<int>(result);
  }
  else
  {
    return -1;
  }
}

char IostreamConnection::readOne()
{
  char result;
  std::cin.get(result);
  if(std::cin)
  {
    return result;
  }
  else
  {
    return 0;
  }
}

bytes IostreamConnection::read(int size)
{
  bytes r = bytes();

  while(r.size() < size)
  {
    char b = readOne();
    r.push_back(b);
  }

  return r;
}

void IostreamConnection::write(bytes bs)
{
  for (char b : bs)
  {
    std::cout.put(b);
  }
}
