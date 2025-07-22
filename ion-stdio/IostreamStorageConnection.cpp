//
// Created by Dr. Brandon Wiley on 3/17/25.
//

#include "IostreamStorageConnection.h"

#include "IostreamConnection.h"

#include "types.h"

#include "storage/storage.h"
#include "storage/mixed_array.h"

IostreamStorageConnection IostreamStorageConnection::make()
{
  return IostreamStorageConnection(IostreamConnection());
}

maybe<Storage> IostreamStorageConnection::read_storage()
{
  return NOUN_FROM_CONN(reliable);
}

void IostreamStorageConnection::write_storage(Storage x)
{
  NOUN_TO_CONN(reliable, x);
}
