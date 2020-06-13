#include <iostream>
#include <VSPtr.hpp>

using namespace std;

void scope(){
    VSPtr<bool> ptr2 = VSPtr<bool>::New();
    ptr2 = true;
    VSPtr<char> ptr3 = VSPtr<char>::New();
    ptr3 = '3';

    if(&ptr2){
        cout << *ptr3 << endl;
    }
}

int main(int arg, char* args[]){
    g_collector_run();
    
    VSPtr<int> ptr3 = VSPtr<int>::New();
    VSPtr<int> ptr4 = VSPtr<int>::New();
    VSPtr<int> ptr5 = VSPtr<int>::New();
    
    scope();

    ptr4 = ptr5;
    ptr3 = ptr5;

    ptr5 = 5;

    cout << *ptr3 << endl;

    g_collector_close();
    return 0;
}