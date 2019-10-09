#include "stack.h"

int main()
{
    Stack<int> stack;
    for(int i = 0; i < 56; i += 2)
        stack.push_back(i + 3);
    for(int i = 0; i < 78; i += 2)
        stack.pop();
    //cout << *stack.top() << endl;
    return 0;
}
