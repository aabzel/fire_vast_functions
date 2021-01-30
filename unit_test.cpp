#include "unit_test.h"

//#include "stdafx.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <iterator>

#include "fire_vast_functions.h"
#include "uTests.h"
#include "utils_cpp.h"

int test_extract_file_name (void) {
    cout << endl << __FUNCTION__ << "()" << endl;
    string outStr = "";
    outStr = extract_file_name (".\\fw\\Common\\criticalSection.h");
    if (outStr != "criticalSection.h") {
        return 1;
    }
    return 0;
}

int test_preproc_cleaner (void) {
    cout << endl << __FUNCTION__ << "()" << endl;
    string outStr;
    outStr = remove_preproc ("");
    return 1;
}

int test_string_to_int (void) {
    cout << endl << __FUNCTION__ << "()" << endl;
    int outVal = 0;
    int ret;
    EXPECT_NULL (string_to_int ("1234", &outVal));

    if (outVal != 1234) {
        return 2;
    }
    return 0;
}

int test_func_name_extractor (void) {
    cout << endl << __FUNCTION__ << "()" << endl;
    string funcName;
    EXPECT_NULL (func_name_extractor ("int func_name (int a, int b)", &funcName));

    if (funcName != "func_name") {
        return UT_FUNC_NAME_SEPARATOR_ERROR;
    }
    EXPECT_NULL (func_name_extractor ("int func_name1  (int a )", &funcName));

    if (funcName != "func_name1") {
        return UT_FUNC_NAME_SEPARATOR_ERROR;
    }

    return UT_FINE;
}

bool test_determine_headername (void) {
    cout << endl << __FUNCTION__ << "()" << endl;
    string header_name = "";
    header_name = determine_headername ("amount_of_uio_states.c");
    EXPECT_EQ_STR_CPP ("amount_of_uio_states.h", header_name);

    header_name = determine_headername ("some_code.cpp");
    EXPECT_EQ_STR_CPP ("some_code.h", header_name);

    header_name = determine_headername ("some_code.i");
    EXPECT_EQ_STR_CPP ("some_code.i", header_name);
    return true;
}

int run_unit_tests (void) {
    cout << endl << __FUNCTION__ << "()" << endl;
    EXPECT_NULL (test_func_name_extractor ());
    EXPECT_NULL (test_extract_file_name ());
    EXPECT_NULL (test_string_to_int ());
    EXPECT_TRUE (test_determine_headername ());
    return 0;
}
