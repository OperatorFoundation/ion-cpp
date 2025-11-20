//
// Created by Dr. Brandon Wiley on 7/3/25.
//
#include <catch2/catch_all.hpp>
#include "squeeze.h"
#include "storage/word.h"
#include "Pipe.h"
#include <iostream>

TEST_CASE("squeeze int 0", "[int]")
{
  constexpr int input = 0;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int 1", "[int]")
{
  constexpr int input = 1;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int -1", "[int]")
{
  constexpr int input = -1;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int 256", "[int]")
{
  constexpr int input = 256;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int -256", "[int]")
{
  constexpr int input = -256;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

// NEW TESTS FOR SIGNED/UNSIGNED BUGS

TEST_CASE("squeeze int with bit 7 set in first byte", "[int]")
{
  constexpr int input = 128; // 0x80 - bit 7 set
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int with bit 7 set in first byte negative", "[int]")
{
  constexpr int input = -128; // -0x80
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int max positive 2-byte value", "[int]")
{
  constexpr int input = 32767; // 0x7FFF - max positive 2-byte signed
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int just over 2-byte signed", "[int]")
{
  constexpr int input = 32768; // 0x8000 - bit 15 set
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int with bit 31 set - near max positive", "[int]")
{
  constexpr int input = 1014850000; // Your problematic value
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int with bit 31 set - second value", "[int]")
{
  constexpr int input = 1014860000; // Your other problematic value
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int max int32", "[int]")
{
  constexpr int input = 2147483647; // 0x7FFFFFFF - max positive int32
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int min int32", "[int]")
{
  constexpr int input = -2147483648; // 0x80000000 - min negative int32
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);

  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }

  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int negative with high bit set in representation", "[int]")
{
  constexpr int input = -1014850000;
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze int all bytes have bit 7 set", "[int]")
{
  constexpr int input = -16843009; // 0xFEFEFEFF - lots of high bits
  bytes data = squeeze_int(input);
  std::tuple<varint, bytes> result = expand_int(data);
  varint value = std::get<0>(result);
  bytes rest = std::get<1>(result);
  REQUIRE(std::holds_alternative<int>(value));
  if(std::holds_alternative<int>(value))
  {
    int output = std::get<int>(value);
    REQUIRE(input == output);
  }
  REQUIRE(rest.empty());
}

TEST_CASE("squeeze bigint", "[conn]")
{
  constexpr int input = 1;
  Pipe pipe;
  Connection& a = pipe.getEndA();
  Connection& b = pipe.getEndB();

  Storage word = Word::make(input, 0);
  std::cout << "Word created with type: " << word.t << ", obj: " << word.o << std::endl;

  Word::to_conn(a, word);
  std::cout << "Word written to connection" << std::endl;

  int storageType = b.readOne();
  int objectType = b.readOne();

  REQUIRE(storageType == StorageType::WORD);
  REQUIRE(objectType == 0);

  maybe<Storage> maybeResult = Word::from_conn(b, 0);
  std::cout << "Read from connection, has value: " << (maybeResult != std::nullopt) << std::endl;

  REQUIRE(maybeResult != std::nullopt);

  Storage result = *maybeResult;
  std::cout << "Result type: " << result.t << ", obj: " << result.o << std::endl;
  std::cout << "Result holds int: " << std::holds_alternative<int>(result.i) << std::endl;

  if(std::holds_alternative<ints>(result.i)) {
    std::cout << "Result holds ints (bigint) instead!" << std::endl;
    ints vals = std::get<ints>(result.i);
    std::cout << "ints size: " << vals.size() << std::endl;
    for(size_t i = 0; i < vals.size(); i++) {
      std::cout << "  ints[" << i << "] = " << vals[i] << std::endl;
    }
  }

  REQUIRE(std::holds_alternative<int>(result.i));

  if(std::holds_alternative<int>(result.i))
  {
    int output = std::get<int>(result.i);
    std::cout << "Output value: " << output << std::endl;
    REQUIRE(input == output);
  }
}

TEST_CASE("squeeze bigint with large value", "[conn]")
{
  constexpr int input = 1014860000;
  Pipe pipe;
  Connection& a = pipe.getEndA();
  Connection& b = pipe.getEndB();
  Storage word = Word::make(input, 0);
  Word::to_conn(a, word);

  int storageType = b.readOne();
  int objectType = b.readOne();

  REQUIRE(storageType == StorageType::WORD);
  REQUIRE(objectType == 0);

  maybe<Storage> maybeResult = Word::from_conn(b, 0);
  REQUIRE(maybeResult != std::nullopt);
  Storage result = *maybeResult;
  REQUIRE(std::holds_alternative<int>(result.i));
  if(std::holds_alternative<int>(result.i))
  {
    int output = std::get<int>(result.i);
    REQUIRE(input == output);
  }
}

TEST_CASE("squeeze roundtrip through connection", "[conn]")
{
  Pipe pipe;
  Connection& a = pipe.getEndA();
  Connection& b = pipe.getEndB();

  // Test several problematic values
  std::vector<int> testValues = {
    0, 1, -1,
    128, -128,
    32767, 32768, -32768,
    1014850000, 1014860000,
    2147483647, -2147483648
  };

  for(int input : testValues)
  {
    Storage word = Word::make(input, 0);
    Word::to_conn(a, word);

    int storageType = b.readOne();
    int objectType = b.readOne();

    REQUIRE(storageType == StorageType::WORD);
    REQUIRE(objectType == 0);

    maybe<Storage> maybeResult = Word::from_conn(b, 0);
    REQUIRE(maybeResult != std::nullopt);
    Storage result = *maybeResult;
    REQUIRE(std::holds_alternative<int>(result.i));
    if(std::holds_alternative<int>(result.i))
    {
      int output = std::get<int>(result.i);
      REQUIRE(input == output);
    }
  }
}