#include "counter.h"
#include "frequency.h"
#include <iostream>

using namespace std;

Counter::Counter(Input &input, const int start, const int end)
{
    this->start = start;
    this->end = end;
    this->text = input.get_words();
}

void Counter::count(const int id)
{
    cout << "Started counter " << id << ", counting characters "
         << start << "-" << end << endl;

    char c;
    string word;
    for(int i = start; i < end; i++) {
        c = tolower(text.at(i));
        if(isalpha(c)) {
            word += c;
        } else if(word.length() != 0){
            freq.add(word);
            word = "";
        } else {    
            word = "";
        }
    }   
    cout << "Finished counter " << id  << endl;  
}

Frequency Counter::get_frequency()
{   
    if(freq.get_freq_map().size() == 0) {
        cerr << "Frequency is empty or not yet counted!" << endl;
        exit(-1);
    }
    return freq;
}