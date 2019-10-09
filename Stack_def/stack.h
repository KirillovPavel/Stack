#ifndef STACK_H
#define STACK_H

template<typename stack_t>
class Stack{
protected:
    long long int cannary1;
    int size;
    int capacity;
    int hash;
    stack_t* data;
    long long int cannary2;

    void set_hash();
    int find_hash() const;
    void resize_up();
    void resize_down();
public:
    Stack();

    void push_back(stack_t elem);
    void pop();
    stack_t* top();
    void print() const;
    char error(int line = -1) const;
    void dump() const;
    ~Stack();
};

#include "stack.lnl"
#endif // STACK_H
