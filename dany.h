#ifndef DANY_H_
#define DANY_H_

#include <utility>

#include "type_index.h"

class dany {
 public:
  dany() : content(0) {}

  template <typename ValueType>
  dany(const ValueType &value) : content(new holder<ValueType>(value)) {}

  dany(const dany &other)
      : content(other.content ? other.content->clone() : 0) {}

  dany(dany &&other) : content(other.content) { other.content = 0; }

  template <typename ValueType>
  dany(ValueType &&value)
      : content(new holder<ValueType>(static_cast<ValueType &&>(value))) {}

  ~dany() { delete content; }

  dany &swap(dany &rhs) {
    std::swap(content, rhs.content);
    return *this;
  }

  template <typename ValueType>
  dany &operator=(const ValueType &rhs) {
    dany(rhs).swap(*this);
    return *this;
  }

  dany &operator=(dany rhs) {
    dany(rhs).swap(*this);
    return *this;
  }

  dany &operator=(const dany &rhs) {
    dany(rhs).swap(*this);
    return *this;
  }

  dany &operator=(dany &&rhs) {
    rhs.swap(*this);
    any().swap(rhs);
    return *this;
  }

  template <class ValueType>
  dany &operator=(ValueType &&rhs) {
    dany(static_cast<ValueType &&>(rhs)).swap(*this);
    return *this;
  }

  bool empty() const { return !content; }

  void clear() { any().swap(*this); }

  TypeIndex type() { return content ? content->type() : type_index<void>(); }

  class placeholder {
   public:
    virtual ~placeholder() {}

    virtual TypeIndex type() = 0;

    virtual placeholder *clone() = 0;
  };

  template <typename ValueType>
  class holder : public placeholder {
   public:
    holder(const ValueType &value) : held(value) {}

    holder(ValueType &&value) : held(static_cast<ValueType &&>(value)) {}

    virtual TypeIndex type() { return type_index<ValueType>(); }

    virtual placeholder *clone() { return new holder(held); }

    ValueType held;

   private:
    holder &operator=(const holder &);
  };

  placeholder *content;
};

inline void swap(dany &lhs, dany &rhs) { lhs.swap(rhs); }

template <typename ValueType>
ValueType *dany_cast(dany &operand) {
  return operand.type() == type_index<ValueType>()
             ? &(static_cast<dany::holder<ValueType> *>(operand.content)->held)
             : 0;
}

template <typename ValueType>
inline const ValueType *dany_cast(const dany *operand) {
  return any_cast<ValueType>(const_cast<dany *>(operand));
}

#endif
