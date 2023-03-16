 /*
 * PassengerQueue.cpp
 * Hazel Scullin
 * October 1, 2022
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * The purpose of this program is to create an instance of a 
 * PassengerQueue Class. Right now the existing functions are to 
 * print information about the passenger struct, the passenger's id, 
 * their station of origin and their destination station. In addition
 * there are finstions to return the element at the front, to add a 
 * passenger at the end, to remove a passenger at the front, and to 
 * return the size. 
 * 
 */ 

#include <stdexcept>
#include <iostream>
#include <list>
#include "Passenger.h"
#include "PassengerQueue.h"

using namespace std;

/*
 * name:      front
 * purpose:   Returns, but does not remove, the element at the 
 *            front of the queue
 * arguments: none
 * returns:   the element at the front of the passenger queue
 * effects:   none
 */
Passenger PassengerQueue::front() {
    return passenger_list.front();
}
 
/*
 * name:      dequeue
 * purpose:   Removes the element at the front of the queue
 * arguments: none
 * returns:   none
 * effects:   Removes the element at the front of the queue
 */
void PassengerQueue::dequeue() {
    return passenger_list.pop_front();
}

/*
 * name:      enqueue
 * purpose:   Inserts a new passenger at the end of the queue
 * arguments: the passenger to be added
 * returns:   none
 * effects:   Inserts a new passenger at the end of the queue
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    return passenger_list.push_back(passenger);
} 

/*
 * name:      size
 * purpose:   Returns the number of elements in the queue
 * arguments: none
 * returns:   the number of elements in the queue
 * effects:   none
 */
int PassengerQueue::size() {
    return passenger_list.size();
}

/*
 * name:      print
 * purpose:   Prints each Passenger in the PassengerQueue
 * arguments: the output stream to be printed to
 * returns:   none
 * effects:   Prints each Passenger to the output stream
 */
void PassengerQueue::print(ostream &output) {
    for (list<Passenger>::iterator i = passenger_list.begin(); i != 
    passenger_list.end(); i++) {
        i->print(output);
    }
}
