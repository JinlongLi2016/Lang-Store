#include <iostream>
#include <fstream>

#include <iterator>
#include <vector>

using namespace std;

int main(void){

    int anumber;
    vector<int> numbers {1, 2, 3, 4}, odd_ns, even_ns;

    ofstream of_event_stream("event.txt");
    ofstream of_odd_stream("odd.txt");

    ostream_iterator<int> even_iter(of_event_stream, "\n");
    ostream_iterator<int> odd_iter(of_odd_stream, " ");

    // while(cin >> anumber){
    //     if(anumber == 0){
    //         break;
    //     }
    //     numbers.push_back(anumber);
    // }
    for(auto n: numbers){
        cout << n << " ";
    }
    cout << "\n";
    for(auto number: numbers){
        if(anumber % 2 < 0.5){
            even_ns.push_back(number);
        }else{
            odd_ns.push_back(number);
        }
    }
    cout << "odd_ns.size() =  " << odd_ns.size() << " even_ns.size() = " << even_ns.size() << "\n";
    for(auto n: odd_ns){
        cout << n << " ";
    }
    cout << "end";
    copy(odd_ns.begin(), odd_ns.end(), odd_iter);
    copy(even_ns.begin(), even_ns.end(), even_iter);

    return 0;
}