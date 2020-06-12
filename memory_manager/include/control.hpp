#ifndef CONTROL_H
#define CONTROL_H

#include <VSPtr.hpp>
#include <counter.hpp>
#include <unordered_map>
#include <data_type.hpp>
#include <sstream>
#include <string>

using namespace std;

//Functions utilized by the VS code extension
extern "C"{
    void make_json();
}

//Bucket class that stores the pointers information
class Bucket{
public:
    virtual ~Bucket(){}
    virtual counter* getCount(){}
    virtual string getType(){}
    virtual string getDir(){}
};

template <typename T>
class BucketT: public Bucket{
private:
    counter* count;
    T* ptr;
    string type;
public:
    BucketT(counter* c, T* p){
        this->count = c;
        this->ptr = p;
    }
    ~BucketT(){
        delete(count);
        delete(ptr);
    }
    T* getPtr(){return ptr;}
    counter* getCount(){return count;}
    string getType(){return type_name<decltype(ptr)>();}
    string getDir(){
        const void * address = static_cast<const void*>(ptr);
        stringstream ss;
        ss << address;
        string name = ss.str();
        return name;
    }
};

#endif
