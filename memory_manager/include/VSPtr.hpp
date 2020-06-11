#ifndef M_MANAGER_H
#define M_MANAGER_H

#include <iostream>
#include <stdexcept>
#include <control.hpp>
#include <g_collector.hpp>
#include <counter.hpp>

using namespace std;

template <typename T>
class VSPtr{
private:
    T* ptr;
    counter* count;
    int ID;
    string info;

public:
    // Constructor
    VSPtr(T *p = NULL){
        ptr = p;
        count = new counter();
        count->plus(1);
    }
    
    // Copy constructor
    VSPtr(const VSPtr<T>& vsptr){
        ptr = vsptr.ptr; 
        count = vsptr.count; 
        count->plus(1); 
    }

    // Destructor 
    ~VSPtr(){
        count->plus(-1);
    }

    //Creates new pointer
    static VSPtr<T> New(){
        VSPtr<T> temp = VSPtr(new T);
        temp.ID = g_collector::getInstance()->generate_id();
        BucketT<T>* b = new BucketT<T>(temp.count, temp.ptr);
        g_collector::getInstance()->add_ptr(temp.ID, b);
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
        count = b.count;
        count->plus(1);
    }

    void operator =(T const &b){
        *ptr = b;
    }
};

#endif