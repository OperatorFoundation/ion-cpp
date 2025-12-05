//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#ifndef MIXED_ARRAY_H
#define MIXED_ARRAY_H

#include <vector>

#include "storage.h"

#include <transmission-cpp.h>
#include <Connection.h>

#ifndef NOUN_TO_BYTES
#define NOUN_TO_BYTES(i) MixedArray::default_noun_to_bytes(i)
#endif

#ifndef NOUN_FROM_CONN
#define NOUN_FROM_CONN(conn, logger) MixedArray::default_noun_from_conn(conn, logger)
#endif

#ifndef NOUN_TO_CONN
#define NOUN_TO_CONN(conn, i, logger) MixedArray::default_noun_to_conn(conn, i, logger)
#endif

class MixedArray
{
public:
  static maybe<Storage> from_bytes(const bytes& data, int o);
  static maybe<bytes> to_bytes(const Storage& storage);

  static maybe<Storage> from_conn(Connection& conn, int objectType, Logger* logger);
  static void to_conn(Connection& conn, const Storage& i);

  static Storage make(mixed x = {}, int o = NounType::LIST);

  static bytes default_noun_to_bytes(const Storage& i);
  static maybe<Storage> default_noun_from_conn(Connection& conn, Logger* logger);
  static void default_noun_to_conn(Connection& conn, const Storage& i, Logger* logger);
};

#endif //MIXED_ARRAY_H
