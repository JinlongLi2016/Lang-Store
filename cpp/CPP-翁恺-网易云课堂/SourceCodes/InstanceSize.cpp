#include<iostream>
using namespace std;
class Time{
public:
	int hour, minute, second;
	void set(){
		cin>>hour>>minute>>second;}

};

int main(void)
{
	cout<<sizeof(Time)<<endl;
	Time t;
	cout<<sizeof(t)<<endl;
}
