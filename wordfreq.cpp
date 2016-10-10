#include "input.h"
#include "counter.h"
#include "frequency.h"
#include <limits>
#include <string.h>
#include <iostream>

using namespace std;

//Data needed by threads to construct counters.
struct thread_data {
    Counter *counter;
    int thread_id;
};

int main(int argc, const char *argv[])
{
    if(argc < 2 || argc > 5) {
        cerr << "Wrong number of arguments,\n"
             << "USAGE: <filename> <no. of words (optional)> <no. of threads (optional)> \n"
             << "Use handle -a if you want to list all words in the file" << endl;
        return 1;
    }

    const char *filename = argv[1];
    int words;
    int  thread_count;
    bool all_words = false;
    
    //default argumets
    if(argv[2] && atoi(argv[2])) words = atoi(argv[2]);
    else words = numeric_limits<int>::max();
    
    if(argv[3] && atoi(argv[3])) thread_count = atoi(argv[3]);
    else thread_count = 1; 
    

    //fix invalid arguments
    if(words < 0) words = -words;
    if(thread_count != 1 && thread_count != 2 && thread_count != 4) thread_count = 1;

    //initialize Input with file
    Input input(filename, words);

    //Frequency where sub-frequencies are merged
    Frequency main_freq;

    //initialize counters
    int input_length = input.get_words().length();
    //array of data to be passed in pthread_create
    struct thread_data td[thread_count];
    Counter *counters[thread_count];
    int start, end;
    for(int i = 0; i < thread_count; i++) {
       start = (i * input_length / thread_count);
       end = ((i + 1) * input_length / thread_count) - 1;
       counters[i] = new Counter(input, start, end);
       td[i].counter = counters[i];
       td[i].thread_id = i;
    }
    
    //start threads
    void *start_counter(void *thread_argument); //forward declaration
    pthread_t threads[thread_count];    
    int status;
    for(int i = 0; i < thread_count; i++) {
        status = pthread_create(&threads[i], NULL, start_counter, (void *)&td[i]);
        if(status != 0) {
            cerr << "Unable to create thread, " << status << endl;
            exit(-1);
        }
    }

    //wait for threads to finish
    for(int i = 0; i < thread_count; i++) {    
        pthread_join(threads[i], NULL);
    }

    //close the open file
    input.kill();

    //merge frequencies into one main frequency
    for(int i = 0; i < thread_count; i++) {
        Frequency sub_freq = counters[i]->get_frequency();
        main_freq.add(&sub_freq);
        delete(counters[i]);
        counters[i] = nullptr;
    }

    //print out the result
    if(strcmp(argv[1], "-a") == 0 || (argv[3] && strcmp(argv[3], "-a") == 0)
            || (argv[4] && strcmp(argv[4], "-a") == 0) ) {
        all_words = true;
    }
    cout << main_freq.get_string(all_words) << endl;

    return 0;
}

/*
 * Start a counter given in thread_args
 * Called from pthread_create
 */
void *start_counter(void *thread_args)
{
    struct thread_data *data;
    data = (struct thread_data *) thread_args;  
    //call Counter's count function
    data->counter->count(data->thread_id);
    
    return 0;
}
