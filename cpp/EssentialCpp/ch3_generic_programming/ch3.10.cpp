#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(){
    string word;
    vector< string > text;

    while( cin >> word ) // ctrl+z at new line represents terminal
        text.push_back(word);
    
    sort(text.begin(), text.end());

    for ( int ix = 0; ix < text.size(); ++ix)
        cout << text[ ix ] << ' ';
    
    return 0;
}