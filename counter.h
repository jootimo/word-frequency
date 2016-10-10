/*requests a string of at most W word from Input and counts the
frequency of words.*/
#include "input.h"
#include "frequency.h"
#include <string>

#ifndef COUNTER_H
#define COUNTER_H

class Counter {
private:
    //the text to count words from
    std::string text;

    //Frequency object to save data to
    Frequency freq;
    int start, end;
public:
    Counter(Input &input, int start, int end);
    void count(int id);
    Frequency get_frequency();
};

#endif
