#include "Stack.hpp"

int main(){
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(232);

    st.pop();

    std::cout << st.peek() << std::endl;

    st.push(234);
    
    st.print();
}