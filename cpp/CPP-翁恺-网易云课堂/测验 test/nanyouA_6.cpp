#include<iostream>
using namespace std;

class Complex
{
	double real, image;
public:
	Complex():real(0), image(0){}
	Complex(double r,double i):real(r), image(i){}
	Complex operator++(int);
	friend ostream& operator<<(ostream &, Complex &);
	friend istream& operator>>(istream &, Complex &);
};

Complex Complex::operator++(int)
{
	//return 自增前的对象（对象的拷贝）
	//自增作用在了自身上面
	Complex tmp(*this);

	real++; image++;
	return tmp;
};

ostream& operator<<(ostream &o, Complex& c)
{	
	o<<c.real<<"+"<<c.image<<"i"<<endl;
	return o;

};
istream& operator>>(istream& i, Complex& c)
{
	i>>c.real>>c.image;
	return i;
}

int main(void)
{
	Complex b, c(3.2, 7.8);
	cin >> b;
	cout<<b<<c;
	b = c++;
	cout<<b<<c;

	return 0;
};
