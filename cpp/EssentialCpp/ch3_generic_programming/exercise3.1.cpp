#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <iterator>
#include <algorithm>

#include <map>

using namespace std;

int main(){
    ifstream inf("sampletext.txt");

    istream_iterator< string > is_iter(inf);

    istream_iterator< string > eof;

    map<string,int> word_count;

    vector< string > text;

    copy(is_iter, eof, back_inserter(text));
                     
    // vector< string > excluded_words =vector< string > {"a", "an"};
    // g++ *.c++ -std=c++11


    vector< string > excluded_words{"a", "an"};

    excluded_words.push_back("a");
    excluded_words.emplace_back("an");
    excluded_words.emplace_back("or");
    excluded_words.emplace_back("the");
    excluded_words.emplace_back("and");
    excluded_words.emplace_back("but");
    
    vector< string >::iterator it = text.begin();
    while( it != text.end() ){
        cout << *it << ' ' << endl;

        if( std::find(excluded_words.begin(), excluded_words.end(), *it) != excluded_words.end()){
            word_count[*it] += 1;
        }
        ++it;
    }

    map<string,int>::iterator dit = word_count.begin();
    for(; dit != word_count.end(); dit++)
        cout << "key: " << dit->first  << " " 
        << "value: " << dit->second << endl;
    return 0;
}