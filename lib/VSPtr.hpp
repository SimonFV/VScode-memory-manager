#ifndef M_MANAGER_H
#define M_MANAGER_H

#include <iostream>
#include <stdexcept>
#include <g_collector.hpp>
#include <control.hpp>

using namespace std;

//dynamic inheritance to facilitate the use of regular VSPointers.
class VSPtrI{
public:
    virtual ~VSPtrI(){}
    virtual int getID(){}
    virtual string getInfo(){}
};

static unordered_map<int, VSPtrI> ptr_map;

template <typename T>
class VSPtr: public VSPtrI{
private:
    T* ptr;
    int ID;
    string info[] = {"int", "0x0002", "2"};

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
        VSPtr<T> temp = VSPtr(new T);
        temp.ID = g_collector::getInstance()->generate_id();
        //start
        cout << "given id: " << temp.ID << endl;
        ptr_map[temp.ID] = temp;
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

    //Get information
    string getInfo(){

        return info;
    }
    int getID(){
        return this->ID;
    }
};

#endif