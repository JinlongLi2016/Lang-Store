#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <vector>

using namespace std;
typedef int elemType;

class Stack{
    public:
        Stack(int capacity = 0);
        ~Stack();

        bool empty();
        bool full();
        
        bool push(elemType elem);
        bool pop(elemType& elem);
        bool peek(elemType& elem);

    private:
        std::vector<elemType> _stack;
};

#endif