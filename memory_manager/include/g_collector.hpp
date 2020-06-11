#ifndef G_COLLECT
#define G_COLLECT
#include <VSPtr.hpp>

//Garbage Collector class
class g_collector{
private:
    static g_collector *gc_instance;
    g_collector(){}
    ~g_collector(){}

public:
    static g_collector *getInstance();
    g_collector(g_collector &other) = delete;
    void operator=(const g_collector &) = delete;

public:
    int generate_id();
    void run_inspection();
    void add_ptr(int id, Bucket* b);

};

g_collector *g_collector::gc_instance = nullptr;

#endif