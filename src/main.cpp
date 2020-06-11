#include <iostream>
#include <VSPtr.hpp>

using namespace std;


void scope(){
    VSPtr<int> ptr = VSPtr<int>::New();
    VSPtr<char> ptr2 = VSPtr<char>::New();
}

int main(int arg, char* args[]){
    
    scope();
    VSPtr<int> ptr3 = VSPtr<int>::New();
    VSPtr<int> ptr4 = ptr3;

    g_collector::getInstance()->run_inspection();

    return 0;
}