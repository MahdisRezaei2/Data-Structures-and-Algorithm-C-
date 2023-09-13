#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cctype>

#include <iostream>
template <typename T>

class stack{
    public:
        stack(){
            top = nullptr;
        }
        void push(T x){
            top = new node{x, top};            
        }
        T peek(){
            if(isEmpty()){
                std::cout << "Stack Is Empty" << std::endl;
                exit(1);
            }
            return top->data;
        }
        T pop(){
            T ret = peek();
            node* to_del = top;
            top = top->next;
            delete to_del;
            return ret;

        }
        bool isEmpty(){
            return top == nullptr;
        }
        int size(){
        return top.size();
    }

    
       
        //memory management
    private:
        struct node{    
            T data;
            node* next;
        };
        node* top;
         //std::vector<double> top;
};

#endif