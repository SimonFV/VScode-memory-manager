#ifndef CONTROL_H
#define CONTROL_H

#include <VSPtr.hpp>
#include <counter.hpp>
#include <unordered_map>
#include <data_type.hpp>
#include <sstream>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

extern "C"{
    /**
     * Function used by the VS code extension to generate a JSON file with the data.
     */
    void make_json();
}

static thread th; /* Thread for the garbage collector.*/
static bool key = false; /* Bool to stop the thread of the garbage collector.*/

/**
 * Loop of the thread for the garbage collector.
 * Keeps itself running on a while loop and calls the garbage collector every second.
 */
void gc_loop();

/**
 * Activates the thread of the garbage collector.
 */
void g_collector_run();

/**
 * Stops the thread of the garbage collector.
 */
void g_collector_close();

//functions to get the pointer from the hashmap
void find_ptr(int ID);
string get_ptr_int(int ID);
string get_ptr_float(int ID);
string get_ptr_double(int ID);
string get_ptr_bool(int ID);
string get_ptr_char(int ID);
string get_ptr_string(int ID);


/**
 * Bucket interface class that stores the pointers information.
 * It has some basic functions to work with the unknown type BucketTs.
 */
class Bucket{
public:
    virtual ~Bucket(){}

    /**
     * @returns the counter state of the pointer.
     */
    virtual counter* getCount(){}

    /**
     * @returns a string with the type of data of the stored pointer.
     */
    virtual string getType(){}

    /**
     * @returns a string with the address of the pointer.
     */
    virtual string getDir(){}
};

/**
 * Bucket class that stores the pointers information.
 */
template <typename T>
class BucketT: public Bucket{
private:
    counter* count;
    T* ptr;
    string type;
public:

    /**
     * @param c counter.
     * @param p pointer.
     */
    BucketT(counter* c, T* p){
        this->count = c;
        this->ptr = p;
    }

    /**
     * Destructor.
     * Also deletes the pointer and its counter.
     */
    ~BucketT(){
        delete(count);
        delete(ptr);
    }

    /**
     * @returns the actual pointer.
     */
    T* getPtr(){return ptr;}

    /**
     * @returns the counter state of the pointer.
     */
    counter* getCount(){return count;}

    /**
     * @returns a string with the type of data of the stored pointer.
     */
    string getType(){
        string temp = type_name<decltype(ptr)>();
        temp.pop_back();
        return temp;
    }

    /**
     * @returns a string with the address of the pointer.
     */
    string getDir(){
        const void * address = static_cast<const void*>(ptr);
        stringstream ss;
        ss << address;
        string name = ss.str();
        return name;
    }
};

#endif
