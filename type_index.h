#ifndef TYPE_INDEX_H_
#define TYPE_INDEX_H_

#include <string>

enum TypeIndex {
  TIUNKNOWN,
  TIVOID,
  TICHAR,
  TII32,
  TII64,
  TIU32,
  TIU64,
  TISTRING, 
  TIPVOID,
  TIPCHAR,
  TIPI32,
  TIPI64,
  TIPU32,
  TIPU64,
};

template <typename T>
TypeIndex type_index() {
  return TIUNKNOWN;
}

template <>
TypeIndex type_index<void> {
  return TIVOID;
}

template <>
TypeIndex type_index<char> {
  return TICHAR;
}

template <>
TypeIndex type_index<int32_t> {
  return TII32;
}

template <>
TypeIndex type_index<uint32_t> {
  return TIU32;
}

template <>
TypeIndex type_index<int64_t> {
  return TII64;
}

template <>
TypeIndex type_index<uint64_t> {
  return TIU64;
}

template <>
TypeIndex type_index<std::string> {
  return TISTRING;
}

template <>
TypeIndex type_index<void*> {
  return TIPVOID;
}

template <>
TypeIndex type_index<char*> {
  return TIPCHAR;
}

template <>
TypeIndex type_index<int32_t*> {
  return TIPI32;
}

template <>
TypeIndex type_index<uint32_t*> {
  return TIPU32;
}

template <>
TypeIndex type_index<int64_t*> {
  return TIPI64;
}

template <>
TypeIndex type_index<uint64_t*> {
  return TIPU64;
}

#endif
