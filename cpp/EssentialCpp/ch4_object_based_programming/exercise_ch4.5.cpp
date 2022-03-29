#include <iostream>

using namespace std;


class Matrix{
    public:
    Matrix()
    {
        for (int i = 0; i < 16; i++)
            arr[i] = i;
    }
    Matrix(float *array){
        for(int i = 0; i < 16; i++){
            arr[i] = *(array + i);
        }
    }

    Matrix operator+(const Matrix& rhs){
        float arr[16] = {0};
        for(int i = 0; i < 16; i++){
            arr[i] = (*this).arr[i] + rhs.arr[i];
        }
        return Matrix(arr);
    }

    Matrix operator*(const Matrix& rhs){
        float arr[16] = {0};
        for (int i = 0; i < 16; i++)
        {
            arr[i] = (*this).arr[i] * rhs.arr[i];
        }
        return Matrix(arr);
    }

    Matrix operator+=(const Matrix& rhs){
        // ?
        for (int i = 0; i < 16; i++)
        {
            (*this).arr[i] += rhs.arr[i];
        }
        return *this;
    }

    float& operator() (int row, int col){
        return arr[4 * row + col];
    }
    float operator()(int row, int col) const
    {
        return arr[4 * row + col];
    }

    void print(){
        for(int i = 0; i < 16; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    private:
        float arr[16];
};

int main(void){
    int array[16] = {0};
    Matrix m1;
    Matrix m2;
    m1.print();
    m1 += m2;
    m1.print();

    cout << "m2(2, 2): " << m2(2, 2) << endl;
}