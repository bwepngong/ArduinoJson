// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "../Configuration.hpp"
#include "JsonSerializer.hpp"

namespace ArduinoJson {
namespace Internals {

// Implements all the overloads of printTo() and prettyPrintTo()
// Caution: this class use a template parameter to avoid virtual methods.
// This is a bit curious but allows to reduce the size of JsonVariant, JsonArray
// and JsonObject.
template <typename T>
class JsonPrintable {
 public:
  const T &downcast() const {
    return *static_cast<const T *>(this);
  }
};
}  // namespace Internals
}  // namespace ArduinoJson
