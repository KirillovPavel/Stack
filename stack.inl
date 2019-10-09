#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

template<typename stack_t>
Stack<stack_t>::Stack():
    cannary1(0xBADBABA7),
    size(0),
    capacity(10),
    hash(0),
    data(new stack_t[10]),
    cannary2(0xFADEEF99)
{}
template<typename stack_t>
void Stack<stack_t>::set_hash(){
    hash = find_hash();
}
template<typename stack_t>
int Stack<stack_t>::find_hash() const{
    int hash_buf = 0;
    for(int i = 0; i < size; i++){
        hash_buf += (data[i] & i) * i;
    }
    return hash_buf;
}
template<typename stack_t>
void Stack<stack_t>::resize_up(){
    error(__LINE__);
    capacity *= 2;
    stack_t* buf = new stack_t[capacity]{};
    for(int i = 0; i < size; i++)
        buf[i] = data[i];
    delete[] data;
    data = buf;
    error(__LINE__);
}
template<typename stack_t>
void Stack<stack_t>::resize_down(){
    error(__LINE__);
    capacity -= capacity / 4;
    stack_t* buf = new stack_t[capacity]{};
    for(int i = 0; i < size; i++)
        buf[i] = data[i];
    delete[] data;
    data = buf;
    error(__LINE__);
}
template<typename stack_t>
void Stack<stack_t>::push_back(stack_t elem){
    error(__LINE__);
    if(size == capacity)
        resize_up();
    data[size] = elem;
    size++;
    set_hash();
    error(__LINE__);
}
template<typename stack_t>
void Stack<stack_t>::pop(){
    error(__LINE__);
    if(size > 0){
        if(2 * size <= capacity)
            resize_down();
        size--;
    } else {
        cout << "Stack: No elements, chek your code(line "  << __LINE__
             << ')' << endl;
    }
    set_hash();
    error(__LINE__);
}
template<typename stack_t>
stack_t* Stack<stack_t>::top(){
    error(__LINE__);
    if(size > 0){
        error(__LINE__);
        return data + size - 1;
    } else {
        cout << "No elements in stack(line " << __LINE__ << ')' << endl;
        error(__LINE__);
        return nullptr;
    }
}
template<typename stack_t>
void Stack<stack_t>::print() const{
    error(__LINE__);
    for(int i = 0; i < size; i++)
        cout << data[i] << endl;
    error(__LINE__);
}
template<typename stack_t>
char Stack<stack_t>::error(int line) const{
    char err = 0;
    if(size < 0){
        err = 1;
        cout << "Size is negative: " << line << endl;
    }
    if(size > capacity){
        cout << "Size > Capacity: " << line << endl;
        err = 2;
    }
    if(data == nullptr){
        cout << "Stack lost its data: " << line << endl;
        err = 3;
    }
    if(cannary1 != 0xBADBABA7){
        cout << "Attack from the left side: " << line << endl;
        err = 4;
    }
    if(cannary2 != 0xFADEEF99){
        cout << "Attack from the right side: " << line << endl;
        err = 5;
    }
    if(hash != find_hash()){
        cout << "Somebody genious break into your data(but not enough genious really): "
             << line
             << endl;
        err = 6;
    }
    if(err != 0){
        dump();
        cout << "Error: problems with stack - see Info_file"
             << endl;
        //abort();
        this->~Stack();
    }
    return err;
}
template<typename stack_t>
void Stack<stack_t>::dump() const{
    ofstream Info_file("Info_file", ios::out);
    if(!Info_file.is_open()){
        cout << "Can't open file for dump" << endl;
    }
    Info_file << "Stack: [" << this << ']' << endl;
    Info_file << "  Cannary1: " << hex << cannary1 << dec << endl;
    Info_file << "  Size: " << size << endl;
    Info_file << "  Capacity: " << capacity << endl;
    Info_file << "  Cannary2: " << hex << cannary2 << dec << endl;
    Info_file << "  Hash: " << hash << " - " << find_hash() << endl;
    Info_file << "  Data: [" << data << ']' << endl;
    if(data == nullptr){
        Info_file << "      no data" << endl;
    } else {
        if(size <= 0){
            for(int i = size; i < 0; i++){
                Info_file << "      Stack[" << i << "] = " << *(data + i) << endl;
            }
            Info_file << "      Stack[0] = " << *data << "  (*)" << endl;
            Info_file << "      Stack[1] = " << *(data + 1) << "  (*)" << endl;
        } else {
            for(int i = 0; i < size; i++){
                Info_file << "      Stack[" << i << "] = " << *(data + i) << endl;
            }
            Info_file << "      Stack[" << size << "] = " << *(data + size) << "  (*)" << endl;
            Info_file << "      Stack[" << size + 1 << "] = " << *(data + size + 1) << "  (*)" << endl;
        }
    }
    Info_file.close();
}
template<typename stack_t>
Stack<stack_t>::~Stack(){
    delete[] data;
}
