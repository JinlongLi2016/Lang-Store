
// 接口应该被声明为虚的(virtual)，这样子类必须实现才能使用

#include <iostream> 
using namespace std;


// 纯虚函数 vs 虚函数
#define MAX_SIZE  100
class Stack{
    public:
        Stack(){};
        virtual bool pop(int&) = 0;  // 虚函数(virtual)需要有函数体；纯虚函数(=0)不需
        virtual bool push(int) = 0; // This is not okay

        virtual int size() = 0;

        bool empty()
        {
            return _size == 0;
        }
        virtual bool full() = 0;

        virtual int peek() = 0;

        virtual void print() = 0;

        virtual ~Stack() {}; // 如果类有虚方法，一般析构函数也需要是虚的
    
    protected:
        int _size = 0;
};

class LIFO_Stack: public Stack{
    public:
        LIFO_Stack(): Stack(){
            _stack = new int[MAX_SIZE];
            _size = 0;
        }

        ~LIFO_Stack(){
            delete[] _stack;
        }

        bool push(int elem){
            if(_size >= MAX_SIZE)
                return false;
            *(_stack + _size) = elem;
            _size ++;
            return true;
        }
        bool pop(int &elem){
            if(_size <= 0)
                return false;
            elem = *(_stack + _size - 1);
            _size --;
            return true;
        }

        void print(){
            std::cout  <<  "hell";
        };
        virtual int size(){
            return _size;
        };

        virtual bool full(){
            return _size == MAX_SIZE;
        };
        virtual int peek(){
            return *(_stack + _size);
        };

    private:
        int * _stack;     
};

class Peekback_Stack: public Stack{
    public:
        Peekback_Stack(): Stack(){
            _stack = new int[MAX_SIZE];
            _size = 0;
        }   
        ~Peekback_Stack(){
            delete [] _stack;
        }
        int size(){ return _size;};
        bool push(int elem){
            if(_size >= MAX_SIZE)   return false;
            *(_stack + _size) = elem;
            _size ++;
            return true;
        }
        bool pop(int &elem){
            if(_size <= 0) return false;
            elem = *(_stack + _size);
            _size --;
            return true;
        }
        void print(){
            std::cout << "PeekbackStack.print()"<< endl;
        }
        bool full(){ return _size >= MAX_SIZE;}
        int peek(){ return *(_stack + _size);}

        int operator[](int idx){
            if(idx < 0 or idx >= _size){
                cout << "error"<<endl;
                return 0;     
            }
            return *(_stack + idx);
        }

    private:
        int* _stack;
};

int main(void){
    LIFO_Stack lifostack;
    lifostack.push(10);    lifostack.push(10);    lifostack.push(10);
    lifostack.push(10);    lifostack.push(10);    lifostack.push(10);

    int pout;
    lifostack.pop(pout);
    cout << "pout: " << pout << endl;
    cout << "stack size: " << lifostack.size() << endl;

    cout << endl;
    cout << "Peekback_Stack: " << endl;
    Peekback_Stack pbstack;
    pbstack.push(10);    pbstack.push(10);    pbstack.push(10);
    pbstack.push(10);    pbstack.push(10);    pbstack.push(10);

    cout << "pbstack.size = " << pbstack.size() << endl;
    cout << "pbstack[2]: " <<  pbstack[2] << endl;
    return 0;
}

// 1. typedef int elemType;
//  
// 1. 