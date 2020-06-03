#ifndef PTR_LIST_H
#define PTR_LIST_H

#include <VSPtr.hpp>

template <class T>
class ptr_list{
private:
    VSPtr<T> *first;
public:
    ptr_list(){
        first = NULL;
    }
    ~ptr_list(){}
    
    void add_ptr(VSPtr<T> *new_ptr){
        VSPtr<T> *temp = this->first;
        if(first == NULL){
            temp = new_ptr;
        }
        else{
            while(true){
                if(temp->next == NULL){
                    temp->next = new_ptr;
                    break;
                }
                temp = temp->next;
            }
        }
    }

    VSPtr<T> *get_ptr(int looking){
        VSPtr<T> *temp = this->first;
        while(temp != NULL){
            if(temp->ID == looking){
                break;
            }
            temp = temp->next;
        }
        return temp;
    }
};

#endif