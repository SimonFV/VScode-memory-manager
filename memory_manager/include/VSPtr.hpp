#ifndef M_MANAGER_H
#define M_MANAGER_H 0
#include <iostream>

template <class T>

class VSPtr{
private:
    T* ptr;
public:
    // for use of explicit keyword  
    explicit VSPtr(T *p = NULL){
        ptr = p;
    }
    // Destructor 
    ~VSPtr(){
        delete(ptr);
    }
    // Overloading dereferencing operator 
    T& operator *(){
        return *ptr;
    }
    T* operator ->(){
        return ptr;
    }
};

#endif