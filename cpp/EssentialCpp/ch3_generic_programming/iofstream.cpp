#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(){
    ifstream in_file("input.txt");
    ofstream out_file("output.txt");

    if ( ! in_file || ! out_file){
        cerr << "!!Unable to ";
        return -1;
    }

    istream_iterator< string > is(in_file);
    istream_iterator< string > eof;

    vector< string > text;
    copy(is, eof, back_inserter( text ));

    sort(text.begin(), text.end());

    vector<string>::iterator it = text.begin();
    while( it != text.end() ){
        cout << *it << " " ;
        ++it;
    }

    ostream_iterator< string > os(out_file, " ");

    copy(text.begin(), text.end(), os);

    return 0;
}