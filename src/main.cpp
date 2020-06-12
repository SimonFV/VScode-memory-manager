#include <iostream>
#include <VSPtr.hpp>

using namespace std;

int main(int arg, char* args[]){
    g_collector_run();
    
    VSPtr<int> ptr3 = VSPtr<int>::New(); //id 1
    VSPtr<int> ptr5 = VSPtr<int>::New(); //id 2
    VSPtr<int> ptr4 = ptr3;
    VSPtr<bool> ptr2 = VSPtr<bool>::New(); //id 2
    ptr2 = false;

    ptr4 = ptr5;
    ptr3 = ptr5;
    ptr3 = 3;

    usleep(5000000);
    
    g_collector::getInstance()->generate_data();
    


    g_collector_close();
    return 0;
}