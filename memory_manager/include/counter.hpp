#ifndef COUNTER_H
#define COUNTER_H

class counter{
private: 
    int count;
public:
    //Constructor
    counter(){
        count = 0;
    }
    counter(const counter&) = delete; 
    counter& operator=(const counter&) = delete; 

    //Destructor
    ~counter(){}

    int get(){
        return count;
    }

    void plus(int i){
        count = count + i;
    }

};


#endif