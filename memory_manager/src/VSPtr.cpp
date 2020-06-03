#include <VSPtr.hpp>
#include <g_collector.hpp>

int id_num = 0;

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

}

void g_collector::add_ptr(void *new_ptr){

}