#ifndef M_MANAGER_H
#define M_MANAGER_H

#include <iostream>
#include <stdexcept>
#include <g_collector.hpp>

using namespace std;

template <class T>
class VSPtr{
private:
    T* ptr;
    int ID;
public:
    // Constructor
    VSPtr(T *p = NULL){
        ptr = p;
    }
    // Destructor 
    ~VSPtr(){
        delete(ptr);
    }

    
    //Creates new pointer
    static VSPtr<T> New(){
        VSPtr temp = VSPtr(new T);
        temp.ID = g_collector::getInstance()->generate_id();
        
        return temp;
    }

    // Overloaded operators
    T& operator *(){
        return *ptr;
    }

    T* operator ->(){
        return ptr;
    }

    T& operator &(){
        return *ptr;
    }

    void operator =(VSPtr const &b){
        ptr = b.ptr;
        ID = b.ID;
    }

    void operator =(T const &b){
        *ptr = b;
    }
    
};

#endif