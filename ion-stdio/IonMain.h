#ifndef MAIN_H
#define MAIN_H

#include "IostreamStorageConnection.h"

class IonMain
{
  public:
    IonMain();

    void loop();

  private:
    IostreamStorageConnection conn;
};

#endif //MAIN_H
