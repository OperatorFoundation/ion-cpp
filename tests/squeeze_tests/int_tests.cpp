//
// Created by Dr. Brandon Wiley on 7/3/25.
//

#include <catch2/catch_all.hpp>

#include "squeeze.h"
#include "storage/word.h"
#include "Pipe.h"

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

TEST_CASE("squeeze bigint", "[conn]")
{
  constexpr int input = 1;
  Pipe pipe;
  Connection& a = pipe.getEndA();
  Connection& b = pipe.getEndB();

  Storage word = Word::make(input, 0);
  Word::to_conn(a, word);
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