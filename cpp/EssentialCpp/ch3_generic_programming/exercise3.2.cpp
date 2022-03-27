#include <string>
#include <iostream>
#include <fstream>

#include <algorithm>
#include <iterator>
using namespace std;

bool shorter(string a, string b){
    return a.length() < b.length();
}

int main(void){
    ifstream inf("sampletext.txt");
    istream_iterator<string> is_iter(inf);

    istream_iterator<string> eof;

    vector<string> string_vector;

    while(is_iter != eof){
        string_vector.emplace_back(*is_iter);
        ++is_iter;
    }

    sort(string_vector.begin(), 
        string_vector.end(),
        *shorter); // pass function ptr

    vector<string>::iterator iter = string_vector.begin();

    while(iter != string_vector.end()){
        cout << *iter << "\n";
        iter++;
    }
    return 0;
}