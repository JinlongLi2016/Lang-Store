
#include <iostream>

using namespace std;

// matrix支持任意类型的matrix
// 获取(i, j) 元素值
// 修改(i, j) 元素值

// +
// -

// attributes:
//  _rownb, _colnb
//  _

template <typename elemType>
class Matrix2D
{
public:
    Matrix2D(int rownb, int colnb) : _rownb(rownb), _colnb(colnb)
    {
        _array = new elemType[rownb * colnb]; // 分配了这么多空间,但是并未初始化
        for(int idx = 0; idx < rownb * colnb; i++)
            _array[idx] = elemType();
    }

    Matrix2D(elemType *array, int rownb, int colnb) : _rownb(rownb), _colnb(colnb)
    {
        _array = array;
    }

    ~Matrix2D()
    {
        delete [] _array;
    }

    // `copy` constructor & `copy assignment` operator
    Matrix2D(const Matrix2D& rhs);
    Matrix2D& operator=(const Matrix2D& rhs);



    // elemType operator()(int row, int col)
    // {
    //     // if(row < 0 or row >= _rownb or col < 0 or col >= _colnb)
    //     return *(_array + row * _colnb + col);
    // }

    elemType &operator()(int row, int col) const
    {
        // if(row < 0 or row >= _rownb or col < 0 or col >= _colnb)
        return _array[row * _colnb + col];
    }

    Matrix2D<elemType> operator+(const Matrix2D<elemType>&rhs);
    void operator+=(const Matrix2D<elemType> &rhs);
    ostream& print(ostream&) const;

    elemType *get_array()
    {
        return _array;
    }

    int size()
    {
        return _rownb * _colnb;
    }
    int row()
    {
        return _rownb;
    }

    int col()
    {
        return _colnb;
    }
    void print()
    {
        for (int i = 0; i < this->size(); i++)
            cout << " " << i;
    }

private:
    int _rownb, _colnb;
    // int _size; // 不安全， _size初始化在constructor中，不是所有对象初始化都会走指定的constructor
    elemType *_array;
};

// copy constructor
template<typename elemType>
Matrix2D<elemType>::Matrix2D(const Matrix2D& rhs){
    _rownb = rhs._rownb; _colnb = rhs._colnb;
    int size = _rownb * _colnb;
    _array = new elemType[size];
    for(int idx=0; idx < size; idx++)
        _array[idx] = rhs._array[idx];
}

//copy assignment 拷贝赋值运算(=)
template<typename elemType>
Matrix2D<elemType>& Matrix2D<elemType>::operator=(const Matrix2D<elemType>&rhs){
    if( this != &rhs){
        _rownb = rhs._rownb;
        _colnb = rhs._colnb;
        int size = _rownb * _colnb;
        delete[] _array;
        _array = new elemType[size];
        for (int idx = 0; idx < size; idx++)
            _array[idx] = rhs._array[idx];
    }
    return *this;
}

// +
template <typename elemType>
// Matrix2D<elemType> Matrix2D<elemType>::operator+(const Matrix2D<elemType> &rhs)
// {
//     Matrix2D<elemType> result(*this);
//     for(int r = 0; r < this->col(); r++){
//         for(int c = 0; c < this->col(); c++){
//             result(r, c) += rhs(r, c);
//         }
//     }
// }
Matrix2D<elemType> Matrix2D<elemType>::operator+(const Matrix2D<elemType> &rhs)
{
    Matrix2D<elemType> result(*this);
    result += rhs;
    return result;
}
// +=
template <typename elemType>
void Matrix2D<elemType>::operator+=(const Matrix2D<elemType>& rhs){
    for(int idx = 0; idx < this->size(); idx++)
        (*(_array + idx)) += (*(rhs._array + idx));
}

// print
template<typename elemType>
ostream& Matrix2D<elemType>::print(ostream& os) const{
    int col = this->cols();
    int size = this->size();

    for(int idx=0; idx<size; idx++){
        if(idx % col == 0) os << endl;
        os << (*( _array + ix )) << ' ';
    }
    os << endl;
    return os;
}

int main(void)
{
    Matrix2D<int> m(3, 2);

    m(0, 1) = 200;
    cout << m(0, 1) << endl;

    Matrix2D<int> m2(3, 2);

    Matrix2D<int> m3 = m + m2;
    m3.print();

    return 0;
}