#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <iterator>

#include <map>

using namespace std;

int main(){
    ifstream inf("sampletext.txt");

    istream_iterator< string > is_iter(inf);

    istream_iterator< string > eof;

    map<string,int> word_count;

    vector< string > text;

    copy(is_iter, eof, back_inserter(text));

    vector< string >::iterator it = text.begin();
    while( it != text.end() ){
        cout << *it << ' ' << endl;
        word_count[*it] += 1;
        ++it;
    }

    map<string,int>::iterator dit = word_count.begin();
    for(; dit != word_count.end(); dit++)
        cout << "key: " << dit->first  << " " 
        << "value: " << dit->second << endl;
    return 0;
}