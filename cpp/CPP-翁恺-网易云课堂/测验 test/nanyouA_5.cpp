#include<iostream>
using namespace std;

class Student
{
	char *name;//name
	int age; // age
	int grad;// credit
public:
	Student(char[] n, int a):age(a){
		
		age = a;
		name = new char(n);
	}
	~Student(){
		//release memory
		delete name;

	}
	void print();

};

void Student::print()
{
	cout<<"name:"<<name << ",age"<<age<<endl;
}
int main(void)
{
	Student s("Amos", 14);
	s.print();
	
	return 0;
}

