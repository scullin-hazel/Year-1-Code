/*
 * PassengerQueue.h
 * Hazel Scullin
 * October 1, 2022
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * This is the interface for the PassengerQueue Class. 
 * Right now the existing functions are to print information 
 * about the passenger struct, the passenger's id, their station 
 * of origin and their destination station. In addition there 
 * are finstions to return the element at the front, to add a 
 * passenger at the end, to remove a passenger at the front, 
 * and to return the size. 
 * 
 */ 

#ifndef PASSENGERQUEUE_H
#define PASSENGERQUEUE_H

#include <stdexcept>
#include <iostream>
#include <list>
#include "Passenger.h"

using namespace std;

class PassengerQueue {
    public:

    Passenger front();
    // Returns, but does not remove, the element at the front of the queue
    void dequeue();
    // Removes the element at the front of the queue
    void enqueue(const Passenger &passenger); 
    // Inserts a new passenger at the end of the queue
    int size();
    // Returns the number of elements in the queue
    void print(ostream &output);
    // Prints each Passenger in the PassengerQueue to the given output
    // stream from front to back, with no spaces in between and no trailing
    // newline.

    private:

    list<Passenger> passenger_list;
    // an std::list made of passengers named passenger_list

};

#endif