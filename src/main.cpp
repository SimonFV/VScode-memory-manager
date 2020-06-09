#include <iostream>
#include <VSPtr.hpp>

using namespace std;

int main(int arg, char* args[]){

    VSPtr<int> ptr = VSPtr<int>::New();
    VSPtr<char> ptr2 = VSPtr<char>::New();
    
    VSPtr<string> ptr3 = VSPtr<string>::New();
    VSPtr<char> ptr4 = VSPtr<char>::New();
    ptr4 = '4';
    ptr3 = "g";

    ptr2 = ptr4;
    cout << ptr_map.find(1)->first << endl;
    
    return 0;
}