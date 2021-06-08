#include<iostream>
using namespace std;

class Employee{
private:
	int x;
	
public:
	Employee( const std::string& name,
			const std::string& ssn );

protected:
	std::string m_name;
	std::string m_ssn;

};


Employee::Employee(const std::string& name, 
		const std::string& ssn)
{
	m_name = name;
	m_ssn = ssn;
}


int main()
{
	int x = 1;
	int i;
	for(i=0; i<10; i++)
	{
		cout << x<< endl;
	
	}
	Employee e("jack", "231");
	return 0;
}

