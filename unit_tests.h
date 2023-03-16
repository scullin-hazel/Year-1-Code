 /*
 *  unit_tests.h
 *  Hazel Scullin
 *  October 1, 2022
 * 
 *  CS 15 Project 1: A Metro Simulator
 *
 *  testing file for functions included in the Passenger.cpp file 
 *
 */

#include "Passenger.h"
#include "PassengerQueue.h"
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace std;

void test_Passenger_print() {
    Passenger p(1, 2, 3);
    std::ostringstream ss;

    p.print(ss);

    assert(ss.str() == "[1, 2->3]");
}

void test_enqueue() {
    Passenger p1(1, 2, 3);
    Passenger p2(2, 3, 4);
    Passenger p3(3, 4, 5);
    Passenger p4(4, 5, 6);

    PassengerQueue test_queue;

    test_queue.enqueue(p1);
    test_queue.enqueue(p2);
    test_queue.enqueue(p3);
    test_queue.enqueue(p4);

    std::ostringstream ss;

    test_queue.print(ss);
}

// void test_front() {
//     Passenger p1(1, 2, 3);
//     Passenger p2(2, 3, 4);
//     Passenger p3(3, 4, 5);
//     Passenger p4(4, 5, 6);

//     PassengerQueue test_queue;

//     test_queue.enqueue(p1);
//     test_queue.enqueue(p2);
//     test_queue.enqueue(p3);
//     test_queue.enqueue(p4);

//     std::ostringstream ss;

//     Passenger frontp = test_queue.front();
//     assert(frontp.print() == "[1, 2->3]");
// }
