/** const
 * 常变量
 * 常变量指针、常指针
 * 参数：常参、常引用、常变量指针；常返回值
 * 类：常成员函数、常数据成员、常对象
 **/
#include<iostream>
using namespace std;

int main(void){
	const int * cip;
	int i = 10;
	cip = &i; // safe non-const to const
	cout << *cip <<endl;
	// *cip = 54; // error, modify const int pointer

	const int ci = 10;
	int &refi = ci;
}