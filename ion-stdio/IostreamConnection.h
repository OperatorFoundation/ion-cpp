//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#ifndef IOSTREAMCONNECTION_H
#define IOSTREAMCONNECTION_H

#include <types.h>
#include <Connection.h>

class IostreamConnection : public Connection
{
  public:
    IostreamConnection() = default;

    [[nodiscard]] int tryReadOne();
    [[nodiscard]] char readOne();
    [[nodiscard]] std::vector<char> read(int size);
    void write(std::vector<char> bs);
};

#endif //IOSTREAMCONNECTION_H
