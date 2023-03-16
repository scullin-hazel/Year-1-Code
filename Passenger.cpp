/*
 * Passenger.cpp
 * Hazel Scullin
 * October 1, 2022
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * The purpose of this program is to create an instance of a 
 * Passenger struct. Right now the existing function is to 
 * print information about the passenger struct, the passenger's id, 
 * their station of origin and their destination station. 
 * 
 */ 

#include <iostream>
#include <string>
#include "Passenger.h"

using namespace std;

/*
 * name:      print
 * purpose:   to print passenger information to the output 
 * arguments: output stream
 * returns:   none, this is a void function
 * effects:   none other than printing to the output 
 */
void Passenger::print(std::ostream &output) {
        output << "[" << std::to_string(id) << ", " << std::to_string(from) 
               << "->" << std::to_string(to) << "]";
}
 