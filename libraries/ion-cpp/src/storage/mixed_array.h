//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef MIXED_ARRAY_H
#define MIXED_ARRAY_H

#include <vector>

#include "storage.h"

#include <Connection.h>

#ifndef NOUN_TO_BYTES
#define NOUN_TO_BYTES(i) MixedArray::default_noun_to_bytes(i)
#endif

#ifndef NOUN_FROM_CONN
#define NOUN_FROM_CONN(conn) MixedArray::default_noun_from_conn(conn)
#endif

#ifndef NOUN_TO_CONN
#define NOUN_TO_CONN(conn, i) MixedArray::default_noun_to_conn(conn, i)
#endif

class MixedArray
{
public:
  static maybe<Storage> from_bytes(const bytes& data, int o);
  static maybe<bytes> to_bytes(const Storage& storage);

  static maybe<Storage> from_conn(Connection& conn, int objectType);
  static void to_conn(Connection& conn, const Storage& i);

  static Storage make(mixed x = {}, int o = NounType::LIST);

  static bytes default_noun_to_bytes(const Storage& i);
  static maybe<Storage> default_noun_from_conn(Connection& conn);
  static void default_noun_to_conn(Connection& conn, const Storage& i);
};

#endif //MIXED_ARRAY_H
