/*
 * DatumStack.cpp
 * Hazel Scullin
 * October 18, 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * This is the implementation for the DatumStack class. It incudes all 
 * the functions in the vector library that would allow a vector to 
 * act like a stack. There are capacity and element access functions 
 * like size, isEmpty, and top that return information about the 
 * vector and the Datum elements in the vector. There are also 
 * modifying functions like clear, pop, and push that edit the contents 
 * of the vector. Some functions print error messages.
 * 
 */

#include "Datum.h"
#include "DatumStack.h"
#include <vector> 
#include <stdexcept>

using namespace std;

/*
 * name:      DatumStack
 * purpose:   default constructor
 * arguments: none
 * returns:   none
 * effects:   updates the member variables for the new DatumStack class
 */
DatumStack::DatumStack() {}; 

/*
 * name:      DatumStack
 * purpose:   constructor takes an array of Datum and an integer specifying 
 *            the size of the array as parameters and creates a stack
 * arguments: array of Datum and an integer representing the array's size 
 * returns:   none
 * effects:   
 */
DatumStack::DatumStack(Datum data[], int size) {
    for (int i = 0; i < size; i++) {
        push(data[i]);
    }
}

/*
 * name:      isEmpty
 * purpose:   returns true if this instance of the DatumStack class is 
 *            empty and false otherwise.
 * arguments: none
 * returns:   true or false depending on if the spack is epmpty or not 
 * effects:   none
 */
bool DatumStack::isEmpty() {
    return stack.empty();
} 

/*
 * name:      clear
 * purpose:   It makes the current stack into an empty stack
 * arguments: none
 * returns:   none
 * effects:   clears the memory associated with the stack so it is empty
 */
void DatumStack::clear() {
    return stack.clear();
}

/*
 * name:      size
 * purpose:   returns the number of Datum elements on the stack
 * arguments: none
 * returns:   the size of the stack as an integer
 * effects:   none
 */
int DatumStack::size() {
    return stack.size();
}

/*
 * name:      top
 * purpose:   returns the top Datum element on the stack. 
 *            does not remove the top element
 * arguments: none
 * returns:   top datum element
 * effects:   none
 */
Datum DatumStack::top(){
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }
    return stack.back();
} 

/*
 * name:      pop
 * purpose:   removes top element from the stack
 * arguments: none
 * returns:   none
 * effects:   removes top element from the stack
 */
void DatumStack::pop() {
    if (isEmpty()) {
        throw runtime_error("empty_stack");
    }
    return stack.pop_back();
} 

/*
 * name:      push
 * purpose:   takes a Datum element and puts it on the top of the stack.
 * arguments: the Datum to add to the stack
 * returns:   none
 * effects:   adds a Datum element to the stack 
 */
void DatumStack::push(Datum to_add) {
    return stack.push_back(to_add);
}