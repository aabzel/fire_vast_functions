#include "utils_cpp.h"

#include <iostream>
#include <sstream>
#include <fstream>

string load_file_to_string (string inputFileName) {
    ifstream cFileIn (inputFileName);
    string strCfileContent = "";
    if (cFileIn.is_open ()) {
        // cout << "file is open" << endl;
    } else {
        cout << "\nCan not open file " << inputFileName << endl;
        return "";
    }

    cFileIn.seekg (0, ios::end);
    strCfileContent.reserve (cFileIn.tellg ());
    cFileIn.seekg (0, ios::beg);

    strCfileContent.assign (istreambuf_iterator<char> (cFileIn), istreambuf_iterator<char> ());
    cFileIn.close ();

    return strCfileContent;
}

void print_map (map<int, int> histogram) {

    map<int, int>::iterator itr;
    for (itr = histogram.begin (); itr != histogram.end (); ++itr) {
        cout << ' ' << itr->first << ' ' << itr->second << '\n';
    }
}

void print_vector (vector<vector<int>> &intervals) {
    cout << endl;
    for (int i = 0; i < intervals.size (); i++) {
        cout << "[";
        for (int j = 0; j < intervals[i].size (); j++) {
            cout << intervals[i].at (j) << ' ';
        }
        cout << "]";
    }
    cout << endl;
    cout << endl;
}

void print_vector_strs (vector<string> words) {
    cout << __FUNCTION__ << endl;
    cout << endl;
    for (int i = 0; i < words.size (); i++) {
        cout << "[";
        cout << words[i] << ' ';
        cout << "]" << endl;
    }
    cout << endl;
}

int string_to_int (string text, int *outVal) {
    int number = 0;
    istringstream iss (text);
    iss >> number;
    if (!iss.good ()) {
        *outVal = number;
        return 0;
    }
    return 1;
}


bool findAndReplaceAll (string &data, string toSearch, string replaceStr) {
    // Get the first occurrence
    bool res = false;
    size_t pos = data.find (toSearch);
    // Repeat till end is reached
    while (pos != std::string::npos) {
        // Replace this occurrence of Sub String
        data.replace (pos, toSearch.size (), replaceStr);
        // Get the next occurrence from the current position
        pos = data.find (toSearch, pos + toSearch.size ());
        res = true;
    }
    return res;
}
