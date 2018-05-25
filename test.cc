#include <stdio.h>

#include <string>

#include "dany.h"
#include "type_index.h"

#define CHECK_TRUE(x, msg)                      \
  do {                                          \
    if (!(x)) {                                 \
      printf("Error[%d]: %s\n", __LINE__, msg); \
    }                                           \
  } while (0)

#define CHECK_FALSE(x, msg)                     \
  do {                                          \
    if ((x)) {                                  \
      printf("Error[%d]: %s\n", __LINE__, msg); \
    }                                           \
  } while (0)

#define CHECK_EQUAL(x, y, msg)                  \
  do {                                          \
    if ((x) != (y)) {                           \
      printf("Error[%d]: %s\n", __LINE__, msg); \
    }                                           \
  } while (0)

#define CHECK_UNEQUAL(x, y, msg)                \
  do {                                          \
    if ((x) == (y)) {                           \
      printf("Error[%d]: %s\n", __LINE__, msg); \
    }                                           \
  } while (0)

void test_default_ctor() {
  dany value;
  CHECK_TRUE(value.empty(), "empty");
}

void test_converting_ctor() {
  std::string text = "test message";
  dany value = text;

  CHECK_FALSE(value.empty(), "empty");
  CHECK_EQUAL(value.type(), TISTRING);
  CHECK_EQUAL(*any_cast<std::string>(value), text,
              "comparing cast copy against original text");
  CHECK_UNEQUAL(any_cast<std::string>(value), &text,
                "comparing address in copy against original text");
}

int main() {
  test_default_ctor();
  test_converting_ctor();

  return 0;
}
