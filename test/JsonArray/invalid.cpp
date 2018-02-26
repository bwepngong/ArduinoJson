// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#include <ArduinoJson.h>
#include <catch.hpp>

using namespace Catch::Matchers;

TEST_CASE("JsonArray::invalid()") {
  SECTION("SubscriptFails") {
    REQUIRE_FALSE(JsonArray::invalid()[0].success());
  }

  SECTION("AddFails") {
    JsonArray& array = JsonArray::invalid();
    array.add(1);
    REQUIRE(0 == array.size());
  }

  SECTION("CreateNestedArrayFails") {
    REQUIRE_FALSE(JsonArray::invalid().createNestedArray().success());
  }

  SECTION("CreateNestedObjectFails") {
    REQUIRE_FALSE(JsonArray::invalid().createNestedObject().success());
  }

  SECTION("PrintToWritesBrackets") {
    char buffer[32];
    serializeJson(JsonArray::invalid(), buffer, sizeof(buffer));
    REQUIRE_THAT(buffer, Equals("[]"));
  }
}
