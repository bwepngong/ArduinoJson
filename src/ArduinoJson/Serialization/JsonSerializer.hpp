// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License

#pragma once

#include "IndentedPrint.hpp"
#include "JsonWriter.hpp"
#include "Prettyfier.hpp"
#include "StaticStringBuilder.hpp"

#if ARDUINOJSON_ENABLE_STD_STREAM
#include "StreamPrintAdapter.hpp"
#endif

namespace ArduinoJson {

class JsonArray;
class JsonObject;
class JsonVariant;

namespace Internals {

class JsonArraySubscript;
template <typename TKey>
class JsonObjectSubscript;

template <typename Writer>
class JsonSerializer {
 public:
  static void serialize(const JsonArray &, Writer &);
  static void serialize(const JsonArraySubscript &, Writer &);
  static void serialize(const JsonObject &, Writer &);
  template <typename TKey>
  static void serialize(const JsonObjectSubscript<TKey> &, Writer &);
  static void serialize(const JsonVariant &, Writer &);
};
}  // namespace Internals

template <typename TSource, typename TDestination>
typename Internals::EnableIf<!Internals::StringTraits<TDestination>::has_append,
                             size_t>::type
serializeJson(const TSource &source, TDestination &destination) {
  Internals::JsonWriter<TDestination> writer(destination);
  Internals::JsonSerializer<Internals::JsonWriter<TDestination> >::serialize(
      source, writer);
  return writer.bytesWritten();
}

#if ARDUINOJSON_ENABLE_STD_STREAM
template <typename TSource>
std::ostream &serializeJson(const TSource &source, std::ostream &os) {
  Internals::StreamPrintAdapter adapter(os);
  serializeJson(source, adapter);
  return os;
}
#endif

template <typename TSource>
size_t serializeJson(const TSource &source, char *buffer, size_t bufferSize) {
  Internals::StaticStringBuilder sb(buffer, bufferSize);
  return serializeJson(source, sb);
}

template <typename TSource, size_t N>
size_t serializeJson(const TSource &source, char (&buffer)[N]) {
  return serializeJson(source, buffer, N);
}

template <typename TSource, typename TDestination>
typename Internals::EnableIf<Internals::StringTraits<TDestination>::has_append,
                             size_t>::type
serializeJson(const TSource &source, TDestination &str) {
  Internals::DynamicStringBuilder<TDestination> sb(str);
  return serializeJson(source, sb);
}

template <typename TSource, typename TDestination>
size_t serializeJsonPretty(const TSource &source,
                           Internals::IndentedPrint<TDestination> &print) {
  Internals::Prettyfier<TDestination> p(print);
  return serializeJson(source, p);
}

template <typename TSource>
size_t serializeJsonPretty(const TSource &source, char *buffer,
                           size_t bufferSize) {
  Internals::StaticStringBuilder sb(buffer, bufferSize);
  return serializeJsonPretty(source, sb);
}

template <typename TSource, size_t N>
size_t serializeJsonPretty(const TSource &source, char (&buffer)[N]) {
  return serializeJsonPretty(source, buffer, N);
}

template <typename TSource, typename TDestination>
typename Internals::EnableIf<!Internals::StringTraits<TDestination>::has_append,
                             size_t>::type
serializeJsonPretty(const TSource &source, TDestination &print) {
  Internals::IndentedPrint<TDestination> indentedPrint(print);
  return serializeJsonPretty(source, indentedPrint);
}

template <typename TSource, typename TDestination>
typename Internals::EnableIf<Internals::StringTraits<TDestination>::has_append,
                             size_t>::type
serializeJsonPretty(const TSource &source, TDestination &str) {
  Internals::DynamicStringBuilder<TDestination> sb(str);
  return serializeJsonPretty(source, sb);
}
}  // namespace ArduinoJson
