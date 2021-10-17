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
// 可以视为：
// 1. 入参
// 2. 返回值类型
// 3. 局部变量类型
int main(){
        int a, b;
        a = 1; b = 2;
        std::cout << "a = " << a << "b = " << b << std::endl;
        swap(a, b);
        std::cout << "Atfer swap()" << std::endl;
        std::cout << "a = " << a << "b = " << b << std::endl;

	return 0;
}

// 模板函数是函数模板的一个实例
// 只在类型完全匹配的才使用此类情况


// 重载规则顺序
// 1. 完全匹配的函数
// 2. 单独匹配的函数模板匹配
// 3. 然后进行函数重载

// 函数模板的初始化
// 1.      由编译器对传入的参数类型进行推定
// 2.      也可以显示地指定，如果参数没有出现在函数签名中。
// template < class T >
// void foo( void ) {}
// foo<int> (); // type T is int

// 类模板
template<class T>
class Vector
{
private:
        private m_size;
        private m_elements;
public:
        Vector(int);
        ~Vector();
        Vector& operator=(const Vector&);
        T& operator[] (int);
};
template<class T>
Vector<T>::Vector(int size): m_size(size)
{
}
template<class T>
Vector<T>::~Vector()
{
}

template<class T>
T& Vector<T>::operator[] (int idx)
{
        if (idx < m_size and idx >=0){
                return m_elements[idx];
        }
}
/* 每个成员函数前面都有 template <class T> 这一部分，
用以表明这是一个 类模板 vector<T> 的成员函数，且定义T为类型参数（代表未知类型）。*/
// usage
Vector<int> vec_int(100);
Vector<complex> vec_com(200);