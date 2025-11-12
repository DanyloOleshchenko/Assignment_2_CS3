#ifndef TEST_COMMON_H
#define TEST_COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSERT_TRUE(expr) do {         if (!(expr)) {             fprintf(stderr, "[FAIL] %s:%d: ASSERT_TRUE(%s)\n", __FILE__, __LINE__, #expr);             exit(1);         } else {             /* printf("[ OK ] %s\n", #expr); */         }     } while (0)

#define ASSERT_EQ_INT(expected, actual) do {         long long _e = (long long)(expected);         long long _a = (long long)(actual);         if (_e != _a) {             fprintf(stderr, "[FAIL] %s:%d: expected %lld, got %lld\n", __FILE__, __LINE__, _e, _a);             exit(1);         }     } while (0)

#endif /* TEST_COMMON_H */
