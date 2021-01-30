#pragma once

#include <map>
#include <vector>

using namespace std;

bool findAndReplaceAll (string &data, string toSearch, string replaceStr);
int string_to_int (string text, int *outVal);
void print_map (map<int, int> histogram);
void print_vector (vector<vector<int>> &intervals);
void print_vector_strs (vector<string> words);
string load_file_to_string (string inputFileName);
