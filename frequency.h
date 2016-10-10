/*Used to store frequency of words. Each thread will create its own
instance of this class. After the threads complete, the results are merged into
a single Frequency instance.*/

#include <map>
#include <string>

#ifndef FREQUENCY_H
#define FREQUENCY_H

class Frequency {
private:
    /*
     * std::map automatically allocates memory when needed,
     * so even though the size of the map is not known in advance, and can be huge,
     * it can still be created from the stack. 
     */
    std::map<std::string, int> freq_map;
    std::map<std::string, int>::iterator iter;    
public:

    //Add a single word to map. Value can be given as an optional parameter
    void add(std::string key, int value = 1);

    //Function for merging frequencies
    void add(Frequency *sub_freq);

    std::map<std::string, int> get_freq_map();

    //String representation of the map
    std::string get_string(bool get_all);
};

#endif
