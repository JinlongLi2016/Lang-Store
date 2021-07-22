/** 多态
 * 1) 向上造型 upcast
 * 2) 多态绑定
 * */
#include <iostream>
using namespace std;

class Point{
public:
	Point(double a, double b){
		x = a;
		y = b;
	}
	void print(){
		cout << "Point located at (" << x <<"," << y << ")" << endl;
	}
	virtual void print2(){
		cout << "Point located at (" << x <<"," << y << ")" << endl;
	}

	double x, y;
};

class Circle: public Point{
	double r;
public:
	Circle(double a, double b, double c): Point(a, b){
		r = c;
	}
	void print(){
		cout << "Circle located at ";
		Point::print();
	}
	virtual void print2(){
		cout << "Circle located at ";
		Point::print();
	}
};


int main(void){
	Point p(1, 20.3); // Point p = Point(1, 20.3);
	Circle c(1, 2, 3.5);
	Point* p_ptr = &c;

	// 1) 基类指针指向子类时，调用的是基类的函数，但是是子类的成员变量
	c.print();
	p_ptr->print();
	// 2) 当把基类、子类的print函数设为虚的时候，两者调用情况一致。（多态）
	c.print2();
	p_ptr->print2();
}

