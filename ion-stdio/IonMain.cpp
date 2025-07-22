#include "IonMain.h"

#include <iostream>

IonMain::IonMain() : conn(IostreamStorageConnection::make()) {}

void IonMain::loop()
{
  std::optional<Storage> storage = conn.read_storage();

  if(storage)
  {
    conn.write_storage(*storage);
  }
}
