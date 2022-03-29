#include "Stack.h"

Stack::Stack(int capacity){
    if(capacity)
        _stack.reserve(capacity);
}

Stack::~Stack(){}

bool Stack::full() { return _stack.size() == _stack.max_size(); }
bool Stack::empty() { return _stack.size() == 0; }

bool Stack::pop(elemType& elem){
    if(empty()){return false;}
    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::push(elemType elem){
    if(full()){return false;}
    _stack.push_back(elem);
    return true;
}

bool Stack::peek(elemType& elem){
    if(empty()){return false;}
    elem = _stack.back();
    return true;
}
