 
#include "stdafx.h"
#include "unit_test.h"
#include "preprocSettings.h"
#include "fire_vast_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sstream>
#include <string>
#include <fstream>  
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <regex>
#include <iterator>


vector<functionNode_t>  FuncNodeList;
 
bool operator < (const functionNode_t& node1, const functionNode_t& node2)
{
	return node2.amountOfLine < node1.amountOfLine;
}


string extract_file_name (string inputFileNameH) {
	int len = inputFileNameH.length();
	string outStr = "";
#if DEBUG_EXTRACT_FILE_NAME
	cout << "inputFileNameH: " << inputFileNameH << endl;
#endif
	char backSlash = '\\';
	for (int i = (len - 1); 0 <= i; i--) {
		if (backSlash != inputFileNameH[i] )
		{
			outStr = inputFileNameH[i] + outStr;
		} else {

			break;
		}
	}

	return outStr;
}

string remove_preproc ( string codeSnippetOut) {
	//return codeSnippetOut;
	string result;
	string strT = codeSnippetOut;
	string inputFileNameCLackComments = codeSnippetOut;
	regex  pattern("(#([^\r\n]*))");
	smatch matches;
    while(regex_search(strT, matches, pattern)) {
		    if(matches.size()) {
				findAndReplaceAll(inputFileNameCLackComments, matches.str(0), "");
		    }
			strT = matches.suffix().str();
	}
    return inputFileNameCLackComments;
}


int func_name_extractor (string inStr, string* outStr)
{//inStr = "((pf) ? (sfree((pf)->saddr), sfree((pf)->daddr), \	     sfree((pf)->sserv), sfree((pf)->dserv)) : (void)0 ), sfree(pf) )"
	if (inStr.find("?") != string::npos) {
		*outStr="";
	    return 1;
	}    
	int sizeOfinStr = 0;
	int writeFlag = 0;
	int nameWasFlag = 0;
	string temStr="";
	sizeOfinStr = inStr.length();
	for(int i=(sizeOfinStr-1); 0<i; i--){
		if(writeFlag){
			if(inStr[i]!=' '){
				temStr=inStr[i]+temStr;
				nameWasFlag=1;
			}else{
				if(nameWasFlag){
					writeFlag=0;
				}
			}
		}
		if('('==inStr[i]){
			writeFlag=1;
		}
	}
	if(!nameWasFlag){
		return 1;
	}
#if DEPLOY_UT_DEBUG
	cout <<"\n" << inStr;
	cout <<"\n" << temStr;
#endif

	*outStr=temStr;
	return 0;
}

void print_list_of_functions_proto (void) {
	cout << "\n\nresult of search: " << FuncNodeList.size() << " functions: \n" << endl;
	for (int i = 0; i < FuncNodeList.size(); i++) {
		cout << FuncNodeList[i].funcName <<": " <<FuncNodeList[i].amountOfLine << endl;
	}
}

void verify_functions_length (string file, int funcSizeLim) {
	int amountOfViolations = 0;
	int spotViolation = 0;
	std::sort(FuncNodeList.begin(), FuncNodeList.end()); 

	for (int i = 0; i < FuncNodeList.size(); i++) {
		if( funcSizeLim< FuncNodeList[i].amountOfLine){
			spotViolation=1;
		}
	}
	if(spotViolation){
		cout << file<<  ": ";
	}
	for (int i = 0; i < FuncNodeList.size(); i++) {
		if( funcSizeLim< FuncNodeList[i].amountOfLine){
			amountOfViolations++;
			spotViolation = 1;
			cout <<"\n    "<< FuncNodeList[i].funcName <<": \t" <<FuncNodeList[i].amountOfLine << " lines";
            cout <<" exceeds "<<funcSizeLim <<" lines. Split it!" ;
		}
	}
	if(amountOfViolations){
        cout << "\n    Amount of functions with length violation: " << amountOfViolations<< "/"<<FuncNodeList.size()<< endl;
	} else {
#if DEBUG_FINE_RESULT
		cout << "All " << FuncNodeList.size() << " functions have fine length!" << endl;
#endif
	}

}


string  clean_fun_proto_right (string codeSnippetIn)
{
	int len=codeSnippetIn.length();
	if(len<7){
		return "";
	}
#if DEBUG_CLEAN_FUN_PROTO_RIGHT
	cout << "\n clean_fun_proto_right " << "\n";
	cout << "\n codeSnippetIn {" << codeSnippetIn << "}\n";
#endif
	string codeSnippetOut;
	codeSnippetOut = codeSnippetIn;
	char LastChar;
	while (1) {
		LastChar = codeSnippetOut.back();
		if (')' != LastChar) {
			codeSnippetOut.pop_back();
		}
		else {
			break;
		}
	}
#if DEBUG_CLEAN_FUN_PROTO_RIGHT
	cout << "\n codeSnippetOut {" << codeSnippetOut << "}\n";
#endif
	return codeSnippetOut;
}


string clean_fun_proto_left(string codeSnippetIn) {
	int len=codeSnippetIn.length();
	if(len<7){
		return "";
	}
#if DEBUG_CLEAN_FUN_PROTO_LEFT_IN
	cout << "\n clean_fun_proto_left " << "\n";
	cout << "\n codeSnippetIn [" << codeSnippetIn << "]\n";
#endif
	string codeSnippetOut;
	codeSnippetOut = codeSnippetIn;
	codeSnippetOut = remove_preproc(codeSnippetOut);
	char firstChar = '\0';
	while (1) {
		if (1 < codeSnippetOut.size()) {
			firstChar = codeSnippetOut[0];
			if (' ' == firstChar) {
				codeSnippetOut.erase(0, 1);
			}
			else if (0x0A == firstChar) {
				codeSnippetOut.erase(0, 1);
			}
			else if (0x0D == firstChar) {
				codeSnippetOut.erase(0, 1);
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	codeSnippetOut = remove_preproc(codeSnippetOut);
#if DEBUG_CLEAN_FUN_PROTO_LEFT_OUT
	cout << "\n codeSnippetOut [" << codeSnippetOut << "]\n";
#endif
	return codeSnippetOut;
}

int is_proto(string codeSnippetIn) {
	 
    if (codeSnippetIn.find("(") != string::npos) {
		if (codeSnippetIn.find(")") != string::npos) {
			return 0;
		}
		else {
			return 2;
		}
	} else {
		return 1;
	}
	return 5;
}

string separate_func_prototype(string codeSnippetIn)
{
#if DEBUG_SEP_FUN_PROTO_IN
	cout << "\n clean_fun_proto_left " << "\n";
	cout << "\n codeSnippetIn <" << codeSnippetIn << ">\n";
#endif
	string codeSnippetOut = "";
	int size = 0;
	size = codeSnippetIn.size();
	for (int i = size - 1; 0 < i; i--)
	{
		if (codeSnippetIn[i] == ';') {
			break;
		}
		if (codeSnippetIn[i] == '}') {
			break;
		}
		if (codeSnippetIn[i] == '/') {
			break;
		}
		if (codeSnippetIn[i] == '"') {
			break;
		}
		codeSnippetOut = codeSnippetIn[i] + codeSnippetOut;
	}
	if (is_proto (codeSnippetOut)) {
		return "";
	}
	codeSnippetOut = clean_fun_proto_left(codeSnippetOut);
	codeSnippetOut = clean_fun_proto_right(codeSnippetOut);
#if DEBUG_SEP_FUN_PROTO_IN
	cout << "\n codeSnippetOut <" << codeSnippetOut << ">\n";
#endif
	return codeSnippetOut;
}

void findAndReplaceAll(string & data, string toSearch, string replaceStr)
{
    // Get the first occurrence
    size_t pos = data.find(toSearch);
    // Repeat till end is reached
    while( pos != std::string::npos) {
	    // Replace this occurrence of Sub String
	    data.replace(pos, toSearch.size(), replaceStr);
	    // Get the next occurrence from the current position
	    pos =data.find(toSearch, pos + toSearch.size());
    }
}


string load_file_to_string (string inputFileName) {
    ifstream cFileIn(inputFileName);
	string strCfileContent = "";
	if (cFileIn.is_open()) {
		//cout << "file is open" << endl;
	} else {
		cout << "\nCan not open file " << inputFileName << endl;
		return "";
	}

	cFileIn.seekg(0, ios::end);
	strCfileContent.reserve(cFileIn.tellg());
	cFileIn.seekg(0, ios::beg);

	strCfileContent.assign( istreambuf_iterator<char>(cFileIn),
		                    istreambuf_iterator<char>());
	cFileIn.close();

	return strCfileContent;   
}


void parse_c_file (string inputFileNameC)
{
	string strCfileContent; 
	strCfileContent = load_file_to_string (inputFileNameC);
	if (0 == strCfileContent.length() ) {
		return;
	}

	int bracketCount = 0;
	int blockCounter = 0;
	FuncNodeList.clear();
	string codeSnippet = "";

	int amntOfCharsIfFile =0,amountOfLineInFile =0;
	int amountOfLineInFunc =0;
	for (int i = 0; i < strCfileContent.size(); i++) {
		amntOfCharsIfFile++;
		codeSnippet = codeSnippet + strCfileContent[i];
		if ('\n'==strCfileContent[i] ){
			amountOfLineInFile++;
			if(319==amountOfLineInFile){
				int catchVal=1;
			}
			amountOfLineInFunc++;
		}
		if (strCfileContent[i] == '{') {
			if(0==bracketCount){
				amountOfLineInFunc=0;
			}
			bracketCount++;
			if (1 == bracketCount) {
				blockCounter++;
#if DEBUG_FILE_PARSER
				cout << "\nFunction proto catch!" << endl;
#endif
				//cout << "\n<" << codeSnippet << ">";
				codeSnippet.pop_back();
				// IS FUCCTION?
				codeSnippet = separate_func_prototype(codeSnippet);
				if (3<codeSnippet.length()) {
					//cout << "\n{" << codeSnippet << "}";
				    functionNode_t nodeFun;
					nodeFun.amountOfLine = 999999;
					nodeFun.funcSignature=codeSnippet;
					int ret = func_name_extractor (nodeFun.funcSignature, &nodeFun.funcName);
					if (!ret) {
					    if( !is_proto(nodeFun.funcSignature)) {
                            FuncNodeList.push_back(nodeFun);
					    }
					}


#if DEBUG_FILE_PARSER
					cout <<"\nfuncrions: " << nodeFun.funcName << endl;
#endif
					codeSnippet.clear();
				}
			}
		}
		if (strCfileContent[i] == '}') {
			if (bracketCount == 0) {
#if DEBUG_ERRORS
				cout << "} balance error!" << endl;
				cout << "error char: " << amntOfCharsIfFile << endl;
				cout << "error line: " << amountOfLineInFile << endl;
#endif 
			} else if (0 < bracketCount) {
				bracketCount--;
				if (!bracketCount) {
#if DEBUG_SNIPPET
					cout <<codeSnippet<< endl;
#endif 
#if DEBUG_FILE_PARSER
					cout << "\n{} body end. "<< "Amount of line in func: " << amountOfLineInFunc << endl;
					cout << "blockCounter: " << blockCounter << endl;
					cout << "FuncNodeList.size(): " << FuncNodeList.size() << endl;
#endif
					if(0<FuncNodeList.size()){
						FuncNodeList[FuncNodeList.size()-1].amountOfLine=amountOfLineInFunc;
					}
				}
			}
		}
	}
#if DEBUG_FILE_PARSER
	cout << "amount of characters in file: " << amntOfCharsIfFile << endl;
	cout << "amount of line in file: " << amountOfLineInFile << endl;
#endif
}

int string_to_int (string inStr, int *outVal){
    int number =0;
    istringstream iss (inStr);
    iss >> number;
    if (!iss.good ()) {
		*outVal = number;
       return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {

	int ret= 0;
	ret = run_unit_tests();
	if(ret){
		cout << "\n Unit test error: [" << ret << "]\n";
#if DEBUG_WAIT_KEY
	    getchar();
#endif
		return 1;
	}
	string inputFileNameC;
	string strFuncSizeLim;
	if (argc < 3) {
		cout << "Usage: fire_vast_functions.exe file.c number" << endl;
		return 1;
	}
#if DEBUG_MAIN_ARGS
	cout << "argc: " << argc << endl;
	cout << "argv[0]: " << argv[0] << endl;
	cout << "argv[1]: " << argv[1] << endl;
	cout << "argv[2]: " << argv[2] << endl;
#endif
	inputFileNameC = argv[1];
	strFuncSizeLim = argv[2];

#if DEBUG_MAIN_ARGS
	cout << "input File Name C: " << inputFileNameC << endl;
	cout << "func size limit: " << strFuncSizeLim << endl;
#endif
	int funcSizeLim=0;
	ret = string_to_int (strFuncSizeLim, &funcSizeLim);
	if(ret){
		cout << "\n invalid 2nd argument. Must be a number. \n";
#if DEBUG_WAIT_KEY
	    getchar();
#endif
	}

	if(ret){
#if DEBUG_WAIT_KEY
	    getchar();
#endif
		return ret;
	}
	parse_c_file (inputFileNameC);

#if DEBUG_LIST_OF_ALL_FUNCTIONS
	print_list_of_functions_proto( );
#endif 
	verify_functions_length (inputFileNameC ,funcSizeLim);

#if DEBUG_WAIT_KEY
	getchar();
#endif

	return 0;
}

