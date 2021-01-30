// unit_test.h

#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <stdio.h>
#include <string.h>
#include <string>

enum errorCodes {
    UT_FINE = 0,
    UT_FUNC_NAME_SEPARATOR_ERROR = 1,

    UT_AMOUNT_OF_ERROR
};
int test_func_name_extractor (void);
int run_unit_tests (void);

#endif /* UNIT_TESTS_H */