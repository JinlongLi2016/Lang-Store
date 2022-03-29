
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

template<typename elemType>
class Matrix2D{
    public:
        Matrix2D(int rownb, int colnb): _rownb(rownb), _colnb(colnb){
            _array = new elemType[rownb * colnb]; // 分配了这么多空间,但是并未初始化
        }

        Matrix2D(elemType* array, int rownb, int colnb) : _rownb(rownb), _colnb(colnb)
        {
            _array = array;
        }

        ~Matrix2D()
        {
            delete[] _array;
        }

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

        Matrix2D operator+(Matrix2D<elemType> &rhs)
        {
            // @TODO check 2 2dmatrices shape the same

            elemType result[rhs.size()];
            for (int i=0; i < rhs.size(); i++)
            {
                result[i] = this->_array[i] + *(rhs.get_array() + i);
            }
            return Matrix2D(result, this->_rownb, this->_colnb);
        }

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
        void print(){
            for(int i = 0; i < this->size(); i++)
                cout << " " << i ;
        }
        private:
            int _rownb, _colnb;
            // int _size; // 不安全， _size初始化在constructor中，不是所有对象初始化都会走指定的constructor
            elemType *_array;
        };



int main(void){
    Matrix2D<int> m(3, 2);

    m(0, 1) = 200;
    cout << m(0, 1) << endl;

    Matrix2D<int> m2(3, 2);
    
    Matrix2D<int> m3 = m + m2;
    m3.print();

    return 0;
}