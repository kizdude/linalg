/* test_util.h - tiny dependency-free test harness.
 *
 * Usage:
 *   TEST_BEGIN();
 *   CHECK(cond, "message");
 *   CHECK_NEAR(a, b, tol, "message");
 *   return TEST_END();          // nonzero exit code if any check failed
 */
#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>
#include <math.h>

static int g_failures = 0;
static int g_checks = 0;

#define TEST_BEGIN() do { g_failures = 0; g_checks = 0; } while (0)

#define CHECK(cond, msg) do {                                        \
    ++g_checks;                                                      \
    if (!(cond)) {                                                   \
        ++g_failures;                                                \
        fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, msg);\
    }                                                                \
} while (0)

#define CHECK_NEAR(a, b, tol, msg) do {                              \
    ++g_checks;                                                      \
    double _da = (double)(a), _db = (double)(b);                     \
    if (fabs(_da - _db) > (tol)) {                                   \
        ++g_failures;                                                \
        fprintf(stderr, "FAIL %s:%d: %s (%.10g vs %.10g)\n",         \
                __FILE__, __LINE__, msg, _da, _db);                  \
    }                                                                \
} while (0)

static int test_end(const char *name) {
    if (g_failures == 0)
        printf("PASS %s (%d checks)\n", name, g_checks);
    else
        printf("FAILED %s (%d/%d checks failed)\n", name, g_failures, g_checks);
    return g_failures == 0 ? 0 : 1;
}

#define TEST_END() test_end(__FILE__)

#endif /* TEST_UTIL_H */
