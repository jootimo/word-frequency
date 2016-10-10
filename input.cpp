#include <iostream>
#include <string>

#include "input.h"

using namespace std;

Input::Input(const char* filename, const int requested_words)
{
    //open file for read only
    file.open(filename, ios::in);
    if(!file.is_open()) {
        cerr << "Unable to open file" << endl;
    }
    cout << "Opened file " << filename 
         << ", reading " << requested_words << " words" << endl;

    string word, result;
    int word_count = 0;
    //Operator >> breaks on empty character ' '
    while(file >> word && word_count < requested_words) {   
        word_count++;
        words += word += ' ';
    }
}

string Input::get_words()
{
    return words;
}

void Input::kill()
{
    file.close();
}