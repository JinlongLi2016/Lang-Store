/** const
 * 常变量
 * 常变量指针、常指针
 * 参数：常参、常引用、常变量指针；常返回值
 * 类：常成员函数、常数据成员、常对象
 **/
#include<iostream>
using namespace std;

int main(void){
	const int ci = 10;

	//////常变量指针&常指针/////////////////
	const int * cip;//常变量指针
	int i = 10;
	cip = &i; // safe non-const to const
	cout << *cip <<endl;

	int * const q = 10; // 常指针
	*q = 11;
	// q++; Error
	// 两者的区别在于const离谁近
}

///////////常成员函数、常数据成员、常对象//////////////////

// 	常成员函数不能修改数据成员和调用非常成员函数
int Date::set_day(int d){
	day = d; // OK
}
int Date::get_day() const{
	day++;        //Error! 修改数据成员
	set_day(12);  //Error! 调用非常成员函数
	return day;
}

// [将const写在函数名括号后面，表明this是const？]
// 	在声明和定义处均需要在参数后跟上const关键字
// 	不修改数据的函数成员应该被声明为const
// 	常成员函数对常对象比较安全