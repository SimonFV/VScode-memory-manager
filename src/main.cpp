#include <iostream>
#include <VSPtr.hpp>

using namespace std;

//test
int main(int arg, char* args[]){
    VSPtr<int> ptr(new int()); 
    *ptr = 20;
    cout << *ptr << endl; 
    return 0;
}