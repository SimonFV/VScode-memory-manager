
#include <VSPtr.hpp>
#include <control.hpp>

using namespace std;

static unordered_map<int, Bucket*> ptr_map;
static int id_num = 0;

g_collector *g_collector::getInstance(){
    if(gc_instance == nullptr){
        gc_instance = new g_collector();
    }
    return gc_instance;
}

int g_collector::generate_id(){
    id_num++;
    return id_num;
}

void g_collector::run_inspection(){
    for (pair<int, Bucket*> element : ptr_map){
        cout<<"(id "<< element.first << ") has: "<< element.second->getCount()->get() <<endl;
	    if(element.second->getCount()->get() == 0){
            cout<< "deleting (id " << element.first <<")"<< endl;
            delete element.second;
        }
    }
}

void g_collector::add_ptr(int id, Bucket* b){
    ptr_map[id] = b;
}

void g_collector::generate_data(){
    cout<< "generating json file"<<endl;
}