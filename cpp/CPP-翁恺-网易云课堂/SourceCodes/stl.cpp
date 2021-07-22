#include <iostream>
// map/vector/list pair class
#include <vector>
#include <list>
#include <string>
using namespace std;

int main(){
	std::vector<int> x;
	for(int a=0; a<100; a++)
		x.push_back(a);
	std::vector<int>::iterator p;
	for(p=x.begin();
			p<x.end(); p++)
		cout<<*p <<" ";

	list<string> s;
	s.push_back("Hello");
	s.push_back("World");

	s.push_front("pushed front ");

	cout << endl;
	list<string>::iterator p_list;
	for(p_list=s.begin();
			p_list!=s.end(); p_list++)
		cout<<*p_list<<" ";
	cout<<endl;
}