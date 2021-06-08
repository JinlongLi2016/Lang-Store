#include <iostream>

//函数模板
template < class T >
void swap(T& x, T& y){
	T temp = x;
	x = y;
	y = temp;
}

// class T, parameterized type name 参数化的类型名
// inside swap, using T as if it's a type name
//
int main(){
        std::cout << "hello jack"<< std::endl;
	return 0;
}

