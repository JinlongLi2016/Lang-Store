#include "Stack.h"

int main(void)
{
    Stack st;
    for(int i = 10; i < 20; i++)
        st.push(i);
    
    elemType pout;
    if(st.pop(pout))
        std::cout << pout << std::endl;
    std::cout << "hello";   
};