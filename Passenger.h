/*
 * Passenger.h
 * Hazel Scullin
 * October 1, 2022
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * Interface for the Passenger class. As of right now this interface defines
 * the Passenger struct and its member variables, the passenger id, the 
 * origin station, and the destination station as well as a constructor and 
 * an initial print function. 
 * 
 */


#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        // TODO: implement the print function in Passenger.cpp
        void print(std::ostream &output);

};

#endif
