#include "frequency.h"
#include <vector>
#include <algorithm>


#include <iostream>

using namespace std;

void Frequency::add(const string key, const int value)
{
    freq_map[key] += value;
}

void Frequency::add(Frequency *sub_freq)
{
    map<string, int> to_add = sub_freq->get_freq_map();
    string key;
    int value; 
    for(iter = to_add.begin(); iter != to_add.end(); ++iter) {
        key = iter->first;
        value = iter->second; 
        add(key, value);
    }
}

std::map<std::string, int> Frequency::get_freq_map()
{
    return freq_map;
}

string Frequency::get_string(const bool get_all)
{   
    const int WORDS_TO_SHOW = 20;

    //Map cannot be sorted on values instead of keys so a vector representation is needed
    vector<pair<string, int>> freq_vec(freq_map.begin(), freq_map.end());
    
    //sort vector according to values
    bool compare(const pair<string, int> &a, const pair<string, int> &b);
    sort(freq_vec.begin(), freq_vec.end(), compare);
    
    string freq_string, key, value;
    int words = WORDS_TO_SHOW;
    if(get_all) words = static_cast<int>(freq_vec.size()); // size() returns unsigned int
   
    freq_string = "\nMost frequent words:\n";  
    for(int i = 0; i < words; i++) {
        key = freq_vec[i].first;
        value = to_string(freq_vec[i].second);
        freq_string.append(key + " - " + value + "\n");
    }
    return freq_string;
}

//Comparator for sorting frequency vector on values instead of keys
bool compare(const pair<string, int> &a, const pair<string, int> &b)
{
    return a.second > b.second;
}
