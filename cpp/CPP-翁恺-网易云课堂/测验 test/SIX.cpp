#include <iostream>
using namespace std;

class Point
{
	double x, y;
public:
	Point(double xi, double yi):x(xi), y(yi){ };
	virtual void show(){
		cout <<"("<< x<<"," << y<<")" << endl;
	};
};

class Circle: public Point
{
public:
	double r;
	Circle(double xi, double yi, double ri):Point(xi, yi), r(ri){};
	double area(){
		return 3.14 * r * r;
	};
	virtual void show() override{ //最好加上override，否则父类不是虚函数会报错？
		cout << "drived class called" <<endl;
		Point::show();
		cout<<"area:"<<area()<<endl;
	};

};

int main(void)
{
	Point p(10, 20), *pt;
	Circle c(3, 4, 15);
	pt = &p;
	pt->show();
	pt = &c;
	pt->show();
	//通过指针或引用调用的非 virtual的函数 则只会调用 指针类型定义之函数
	Circle *cpt = &c;
	cout<<"cpt->show():"<<endl;
	cpt->show();
	cout<<"c.show:"<<endl;
	c.show();
	return 0;
}
