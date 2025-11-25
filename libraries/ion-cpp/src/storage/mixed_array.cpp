//
// Created by Dr. Brandon Wiley on 3/9/25.
//

#include <tuple>
#include <utility>
#include <vector>
#include <variant>
#include <optional>

#include "storage.h"
#include "word.h"
#include "ion_float.h"
#include "word_array.h"
#include "float_array.h"
#include "mixed_array.h"

#include "../types.h"
#include "../squeeze.h"

#include <Connection.h>
#include <logger.h>

// MixedArray
// Storage::from_bytes decodes a byte array into a MixedArray object
maybe<Storage> MixedArray::from_bytes(const bytes& data, const int o)
{
  return {Storage(o, StorageType::WORD, 0)};
}

// Encodes a MixedArray into a byte array
// Format: {((size x) squeeze) join x} (i each {x to_bytes} over join)
maybe<bytes> MixedArray::to_bytes(const Storage& storage) {
  if (std::holds_alternative<mixed>(storage.i)) {
    const mixed ii = std::get<mixed>(storage.i);

    auto r = bytes();

    const int size = static_cast<int>(ii.size());
    bytes sizeBytes = squeeze_int(size);

    r.insert(r.begin(), sizeBytes.begin(), sizeBytes.end());

    for (const Storage& y : ii) {
      bytes valueBytes = NOUN_TO_BYTES(y);
      r.insert(r.end(), valueBytes.begin(), valueBytes.end());
    }

    return {r};
  }
  else
  {
    return std::nullopt;
  }
}

maybe<Storage> MixedArray::from_conn(Connection& conn, const int objectType, Logger* logger)
{
  varint varsize = expand_conn(conn); // NOLINT
  if (std::holds_alternative<int>(varsize))
  {
    const int size = std::get<int>(varsize);

    auto i = mixed();

    for(int y = 0; y < size; y++)
    {
      if(maybe<Storage> maybeStorage = NOUN_FROM_CONN(conn, logger))
      {
        i.push_back(*maybeStorage);
      }
      else
      {
        return std::nullopt;
      }
    }

    return MixedArray::make(i, objectType);
  }

  else
  {
    // Varint sizes not yet fully implemented
    return std::nullopt;
  }
}

void MixedArray::to_conn(Connection& conn, const Storage& i)
{
  if (std::holds_alternative<mixed>(i.i))
  {
    const mixed ms = std::get<mixed>(i.i);

    // Always include type in to_conn implementation
    std::vector<char> typeBytes = { static_cast<char>(i.t), static_cast<char>(i.o) };
    conn.write(typeBytes);

    const int length = static_cast<int>(ms.size());
    const bytes lengthBytes = squeeze_int(static_cast<int>(length));

    conn.write(lengthBytes);

    for (const Storage& y : ms)
    {
      NOUN_TO_CONN(conn, y);
    }
  }
}

Storage MixedArray::make(mixed x, int o)
{
  return {o, StorageType::MIXED_ARRAY, x};
}

bytes MixedArray::default_noun_to_bytes(const Storage& x)
{
  bytes typeBytes = { static_cast<char>(x.t), static_cast<char>(x.o) };

  bytes valueBytes = bytes();
  switch(x.t)
  {
    case StorageType::WORD:
      return Word::to_bytes(x);

    case StorageType::FLOAT:
      if(maybe<bytes> maybeValueBytes = Float::to_bytes(x))
      {
        return *maybeValueBytes;
      }
      else
      {
        return {};
      }

    case StorageType::WORD_ARRAY:
      return WordArray::to_bytes(x);

    case StorageType::FLOAT_ARRAY:
      if(maybe<bytes> maybeValueBytes = FloatArray::to_bytes(x))
      {
        return *maybeValueBytes;
      }
      else
      {
        return {};
      }

    case StorageType::MIXED_ARRAY:
      if(maybe<bytes> maybeValueBytes = MixedArray::to_bytes(x))
      {
        return *maybeValueBytes;
        break;
      }
      else
      {
        return {};
      }

    default:
      return {};
  }
}

maybe<Storage> MixedArray::default_noun_from_conn(Connection& conn, Logger* logger)
{
  const int storageType = static_cast<unsigned char>(conn.readOne());
  const int objectType = static_cast<unsigned char>(conn.readOne());

  switch(storageType)
  {
    case StorageType::WORD:
      return maybe<Storage>(Word::from_conn(conn, objectType, logger));

    case StorageType::FLOAT:
      return maybe<Storage>(Float::from_conn(conn, objectType));

    case StorageType::WORD_ARRAY:
      return maybe<Storage>(WordArray::from_conn(conn, objectType));

    case StorageType::FLOAT_ARRAY:
      return maybe<Storage>(FloatArray::from_conn(conn, objectType));

    case StorageType::MIXED_ARRAY:
      return maybe<Storage>(MixedArray::from_conn(conn, objectType, logger));

    default:
      return std::nullopt;
  }
}

void MixedArray::default_noun_to_conn(Connection& conn, const Storage& x)
{
  switch(x.t)
  {
    case StorageType::WORD:
      Word::to_conn(conn, x);
      return;

    case StorageType::FLOAT:
      Float::to_conn(conn, x);
      return;

    case StorageType::WORD_ARRAY:
      WordArray::to_conn(conn, x);
      return;

    case StorageType::FLOAT_ARRAY:
      FloatArray::to_conn(conn, x);
      return;

    case StorageType::MIXED_ARRAY:
      MixedArray::to_conn(conn, x);
      return;

    default:
      return;
  }
}