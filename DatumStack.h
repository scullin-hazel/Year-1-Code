/*
 * DatumStack.h
 * Hazel Scullin
 * October 18, 2022 
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * This is the interface for the DatumStack class. It incudes all 
 * the functions in the vector library that would allow a vector to 
 * act like a stack. There are capacity and element access functions 
 * like size, isEmpty, and top that return information about the 
 * vector and the Datum elements in the vector. There are also 
 * modifying functions like clear, pop, and push that edit the contents 
 * of the vector. 
 */

#ifndef DATUMSTACK_H
#define DATUMSTACK_H

#include <string>
#include "Datum.h"
#include <vector>

using namespace std;

class DatumStack {  
public:
    DatumStack(); // default constructor
    DatumStack(Datum data[], int size);// constructor takes an 
    // array of Datum and an integer specifying the size of the 
    // array as parameters and creates a stack

    bool isEmpty(); // returns true if this instance of the 
    // DatumStack class is empty and false otherwise.
    void clear(); // It makes the current stack into an empty stack.
    int size(); // returns the number of Datum elements on the stack
    Datum top(); // returns the top Datum element on the stack. 
    // NOTE: It does not remove the top element

    void pop(); // removes top  element from the stack
    void push(Datum to_add); // takes a Datum element and puts 
    // it on the top of the stack.
private:
    std::vector<Datum> stack;

};

#endif