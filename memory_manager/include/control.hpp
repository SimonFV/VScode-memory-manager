#ifndef CONTROL_H
#define CONTROL_H

#include <VSPtr.hpp>
#include <counter.hpp>
#include <unordered_map>

using namespace std;

//Functions utilized by the VS code extension
extern "C"{
    string getData();
    void start(){cout << "asdasdasd" << endl;}
}

//Bucket class that stores the pointers information
class Bucket{
public:
    virtual ~Bucket(){}
    virtual counter* getCount(){}
};

template <typename T>
class BucketT: public Bucket{
private:
    counter* count;
    T* ptr;
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
};

#endif
