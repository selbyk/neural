#include <vector>
#include <fstream>
#include <iostream>
#include <ctype.h>
#include "fann.h"
#include "fann_cpp.h"

using namespace std;

void error(const char* p, const char* p2 = ""){
    cerr << p << ' ' << p2 << endl;
    exit(1);
}

/**
    Generates letter frequencies from a file to add to the training data
*/
void generate_frequencies(const char *filename, float *frequencies){
    ifstream infile(filename);
    if(!infile) error("Cannot open input file", filename);
    vector<unsigned int> letter_count(26, 0);
    unsigned int num_characters = 0;
    char c;
    while(infile.get(c)){
        c = tolower(c);
        if(c >= 'a' && c <= 'z'){
            letter_count[c - 'a']++;
            num_characters++;
        }
    }
    if(!infile.eof()) error("Something strange happened");
    for(unsigned int i = 0; i != 26; i++) frequencies[i] = letter_count[i]/(double)num_characters;
}

/**
    Generates letter frequencies from a file to add to the training data
*/
/*int main(int argc, char* argv[]){
    if(argc != 2) error("Remember to specify an input file");

    float frequencies[26];
    generate_frequencies(argv[1], frequencies);
    for(unsigned int i = 0; i != 26; i++) cout << frequencies[i] << ' ';

    cout << endl;
    return 0;
}*/

/**
    Tests a file and tells where it's english, french, or polish
*/
int main(int argc, char* argv[]){

    string ann_file = argv[1];
    string test_file = argv[2];

    float frequencies[26];
    generate_frequencies(test_file.c_str(), frequencies);
    for(unsigned int i = 0; i != 26; i++) cout << frequencies[i] << ' ';

    FANN::neural_net ann;
    ann.create_from_file(ann_file);

    float *output = ann.run(frequencies);

    cout << "English: " << output[0] << endl
        << "French: " << output[1] << endl
        << "Polish: " << output[2] << endl;
    return 0;
}

/**
    Creates the neural network and trains it on the data file
*/
/*int main(int argc, char* argv[]){
    string ann_file = argv[1];
    string training_file = argv[2];

    FANN::neural_net ann;
    ann.create_from_file(ann_file);

    ann.train_on_file(training_file, 2000, 10, 0.0001);
    ann.save(ann_file);
    ann.destroy();
    return 0;
}*/
