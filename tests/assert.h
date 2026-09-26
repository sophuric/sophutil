#ifndef ASSERT_H
#define ASSERT_H
#include <inttypes.h>
#include <stdio.h>
#define ASSERT(type_actual, print_type_actual, actual, type_expected, print_type_expected, expected)                                                                          \
	{                                                                                                                                                                         \
		type_actual temp_actual = (actual);                                                                                                                                   \
		type_expected temp_expected = (expected);                                                                                                                             \
		if (temp_actual != temp_expected) {                                                                                                                                   \
			fprintf(stderr, "Assertion failed at %s line %u: Expected %" print_type_expected ". Actual %" print_type_actual, __FILE__, __LINE__, temp_expected, temp_actual); \
			goto fail;                                                                                                                                                        \
		}                                                                                                                                                                     \
	}

#define ASSERT_2(type, print_type, actual, expected) ASSERT(type, print_type, actual, type, print_type, expected)

#define ASSERT_I0(actual) ASSERT_2(int, "i", actual, 0)

#define ASSERT_P(actual, expected) ASSERT_2(void *, "p", actual, expected)

#define ASSERT_NOT_EQUAL(type_actual, print_type_actual, actual, type_expected_not, print_type_expected_not, expected_not)                                                                \
	{                                                                                                                                                                                     \
		type_actual temp_actual = (actual);                                                                                                                                               \
		type_expected_not temp_expected_not = (expected_not);                                                                                                                             \
		if (temp_actual == temp_expected_not) {                                                                                                                                           \
			fprintf(stderr, "Assertion failed at %s line %u: Expected not %" print_type_expected_not ". Actual %" print_type_actual, __FILE__, __LINE__, temp_expected_not, temp_actual); \
			goto fail;                                                                                                                                                                    \
		}                                                                                                                                                                                 \
	}

#define ASSERT_NOT_EQUAL_2(type, print_type, actual, expected_not) ASSERT_NOT_EQUAL(type, print_type, actual, type, print_type, expected_not)

#define ASSERT_NOT_EQUAL_P(actual, expected_not) ASSERT_NOT_EQUAL_2(void *, "p", actual, expected_not)

#endif //ASSERT_H
