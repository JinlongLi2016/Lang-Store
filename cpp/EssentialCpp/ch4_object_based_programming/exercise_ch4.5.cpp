#include <iostream>

using namespace std;


class Matrix{
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
    }

    private:
        float arr[16];
};