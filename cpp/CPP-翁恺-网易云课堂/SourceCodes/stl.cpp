#include <iostream>
// map/vector/list pair class
#include <vector>
#include <list>
#include <map>
#include <string>
using namespace std;

/* 基本数据结构如何实现以下几个目的
1. 实例化
2. 添加元素
3. 删除
4. 访问 & 遍历
*/
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

	map<string, int> m =  { {"CPU", 10}, {"GPU", 15}, {"RAM", 20}, };
	cout << m["CPU"] <<endl;
	m["GPU"] = 100;
	cout << m["GPU"] <<endl;

}

