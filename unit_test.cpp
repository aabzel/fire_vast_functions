 
#include "stdafx.h"

#include "unit_test.h"
#include "fire_vast_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#include <fstream>   
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>

#include <iterator>


int test_extract_file_name(void) {
	string outStr="";
	outStr = extract_file_name(".\\fw\\Common\\criticalSection.h");
	if (outStr!= "criticalSection.h") {
		return 1;
	}
	return 0;
}

 

int test_preproc_cleaner(void){
	string outStr;
    outStr = remove_preproc ("");
	return 1;
}


int test_string_to_int (void) {
	int outVal=0;
	int ret;
	ret = string_to_int ("1234", &outVal);
	if(ret){
		return 1;
	}
	if(outVal!=1234){
		return 2;
	}
	return 0;
}


int test_func_name_extractor(void){
	int ret = 0;
	string funcName;
	ret = func_name_extractor ("int func_name (int a, int b)", &funcName);
	
	if(funcName!="func_name"){
		return UT_FUNC_NAME_SEPARATOR_ERROR;
	}
	ret = func_name_extractor ("int func_name1  (int a )", &funcName);
	
	if(funcName!="func_name1"){
		return UT_FUNC_NAME_SEPARATOR_ERROR;
	}
	
	return UT_FINE;
}

int run_unit_tests (void) {
	int ret=0;
	ret = test_func_name_extractor();
	if(ret){
		return ret;
	}

	ret = test_extract_file_name();
	if (ret) {
		return ret;
	}

	ret = test_string_to_int ();
	if (ret) {
		return ret;
	}
    return 0;
}