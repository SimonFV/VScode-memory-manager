#include <iostream>
#include <VSPtr.hpp>

using namespace std;

int main(int arg, char* args[]){
    
    VSPtr<int> ptr3 = VSPtr<int>::New();
    VSPtr<int> ptr5 = VSPtr<int>::New();
    VSPtr<int> ptr4 = ptr3;

    ptr4 = ptr5;
    ptr3 = ptr5;

    g_collector::getInstance()->run_inspection();

    return 0;
}