#ifndef COUNTER_H
#define COUNTER_H

/**
 * Counter class for the VSPtrs.
 * Stores the number of VSPtrs that are pointing at one especific pointer.
 */
class counter{
private: 
    int count; 
public:
    /**
     * Constructor.
     */
    counter(){
        count = 0;
    }

    counter(const counter&) = delete; /* Constructor for avoiding copies.*/
    counter& operator=(const counter&) = delete; /* Method for avoiding copies.*/

    /**
     * Destructor.
     */
    ~counter(){}

    /**
     * Method that returns the counting value.
     * 
     * @return int counting state.
     */
    int get(){
        return count;
    }

    /**
     * Method that changes the value of the count.
     * 
     * @param i Adds this value to the count.
     */
    void plus(int i){
        count = count + i;
    }

};


#endif