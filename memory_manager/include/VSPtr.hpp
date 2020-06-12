#ifndef M_MANAGER_H
#define M_MANAGER_H

#include <iostream>
#include <stdexcept>
#include <control.hpp>
#include <g_collector.hpp>
#include <counter.hpp>

using namespace std;

/**
 * Type of shared pointer class.
 * The main class of the VSPtr library. Can store any kind of pointer and handle
 * the deletion automatically when the real pointer has no more VSPtrs pointing at it.
 */
template <typename T>
class VSPtr{
private:
    VSPtr<T>* old; /* VSPtr that stores the last pointer this one was pointing at.*/
    T* ptr; /* Actual pointer store in the VSPtr.*/
    counter* count; /* Counter of references for a pointer.*/
    int ID; /* int ID of the VSPtr.*/

public:
    /**
     * Constructor for the VSPtr class.
     * Initialize its counter and adds 1 to it.
     * 
     * @param p pointer with the specified type.
     */
    VSPtr(T *p = NULL){
        old = this;
        ptr = p;
        count = new counter();
        count->plus(1);
    }
    
    /**
     * Copy Constructor for the VSPtr class.
     * Special constructor for copies of VSPtr.
     * 
     * @param vsptr pointer with the specified type.
     */
    VSPtr(const VSPtr<T>& vsptr){
        old = this;
        ptr = vsptr.ptr; 
        count = vsptr.count; 
        count->plus(1); 
    }

    /**
     * Destructor for the VSPtr class.
     * Decreases the counter in 1.
     */
    ~VSPtr(){
        count->plus(-1);
    }

    /**
     * Method in charge of constructing the VSPtrs.
     * Assigns an ID to the pointer and creates a Bucket object for storing its information,
     * then links the ID and the Bucket in a HashMap.
     * The type of value that will be stored must be specified inside the brackets < >.
     * 
     * @return VSPtr created.
     */
    static VSPtr<T> New(){
        VSPtr<T> temp = VSPtr(new T);
        temp.ID = g_collector::getInstance()->generate_id();
        BucketT<T>* b = new BucketT<T>(temp.count, temp.ptr);
        g_collector::getInstance()->add_ptr(temp.ID, b);
        return temp;
    }

    /**
     * Overloaded * operator.
     * 
     * @return Value pointed by the actual pointer.
     */
    T& operator *(){
        return *ptr;
    }

    /**
     * Overloaded -> operator.
     * 
     * @return Actual pointer.
     */
    T* operator ->(){
        return ptr;
    }

    /**
     * Overloaded & operator.
     * 
     * @return Value pointed by the actual pointer.
     */
    T& operator &(){
        return *ptr;
    }

    /**
     * Overloaded = operator.
     * Decreases by 1 the counter of the VSPtr that it was pointing before.
     * @param b VSPtr of the same type.
     */
    void operator =(VSPtr const &b){
        old->count->plus(-1);
        old = this;
        ptr = b.ptr;
        ID = b.ID;
        count = b.count;
        count->plus(1);
    }

    /**
     * Overloaded = operator.
     * 
     * @param b Value to be stored.
     */
    void operator =(T const &b){
        *ptr = b;
    }
};

#endif