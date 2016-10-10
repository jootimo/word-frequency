/*Input: Keeps the text file open, and on a request scans and most W word
 *from the file into a string and returns the string. A single instance of this
 *class will be used by multiple counters.
 */
#include <fstream>

#ifndef INPUT_H
#define INPUT_H

class Input {
private:
    std::ifstream file;
    std::string words;
public:
    Input(const char* filename, const int requested_words);
    std::string get_words();
    //close the input file
    void kill();
};

#endif
