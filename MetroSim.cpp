/*
 * MetroSim.cpp
 * Hazel Scullin
 * October 10, 2022
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * The purpose of this program: MetroSim.cpp is for creating 
 * an instance of the MetroSim class and then manipulating it 
 * through the comand source (either a file or the command line). 
 * The class has a basic constructor, a number of functions for 
 * initializing the arrays and variables, and a command loop 
 * that calls the functions for editing the train and station 
 * array. 
 * 
 */ 
#include <iostream>
#include <fstream>
#include "MetroSim.h"
#include "Passenger.h"
#include "PassengerQueue.h"

/*
 * name:      metrosim constructor
 * purpose:   constuct the metroSim
 * arguments: none
 * returns:   none 
 * effects:   updates conductor and p_cout to zero
 */
MetroSim::MetroSim() {
    conductor = 0; // tracks the location of the train
    p_count = 1;  // for assigning the unique passenger ID's to passengers

}

/*
 * name:      run 
 * purpose:   run functions as the command loop for the metroSim 
 * arguments: file that stores station names, the output file, and the command 
 *            source (either another file or cin)
 * returns:   none 
 * effects:   initializes arrays, prints to cout, takes in commands, 
 *            ends simulation
 */
void MetroSim::run(ifstream &stations, ofstream &out_file, 
                    istream &command_source) {
    build_arrays(stations);
    char command;
    while (not command_source.eof()) {
        print();
        cout << "Command? ";
        command_source >> command;
    
        if (command == 'm') {
            command_source >> command;
            if (command == 'm') {
                board_train();
                conductor = (conductor + 1) % station_array.size();
                exit_train(out_file);
            }
            else if (command == 'f'){
                cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
                return;
            }
        }
        else if (command == 'p') {
            add_newPassenger(command_source);
        }
    }
    cout << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

/*
 * name:      add_newPassenger
 * purpose:   adds a passenger at its station of origin in the station array
 * arguments: the command source (either a file or cin)
 * returns:   none 
 * effects:   adds a passenger at the end of a queue 
 */
void MetroSim::add_newPassenger(istream &command_source) {
    // creates a new passenger and sets the id 
    int command;
    Passenger newP; 
    newP.id = p_count;
    p_count += 1;

    // reads in info about the passenger from command source
    command_source >> command;
    newP.from = command;

    command_source >> command;
    newP.to = command;

    // adds passenger to the passenger queue in the station
    station_array.at(newP.from).queue.enqueue(newP);
}

/*
 * name:      build_arrays
 * purpose:   constructs the station and train arrays with the names of the    
 *            stations given in the file 
 * arguments: file of station names
 * returns:   none 
 * effects:   fills train and station arrays
 */
void MetroSim::build_arrays(ifstream &stations) {
    Waitlist newWaitlist;
    string temp_station;

    while (getline(stations, temp_station)) {
        newWaitlist.station_name = temp_station;
        // sets the train and station arrays to have the names of all 
        // the stations
        train_array.push_back(newWaitlist);
        station_array.push_back(newWaitlist);
    }
}

/*
 * name:      print
 * purpose:   to print hte information in the correct format to cout about the  
 *            simulation. Where the train is and where the passengers are
 * arguments: none
 * returns:   none 
 * effects:   prints to cout
 */
void MetroSim::print() {
    int count = 0;
    // this part prints the passengers in the train array at the top
    cout << "Passengers on the train: {";
    for (std::vector<Waitlist>::iterator it = train_array.begin(); it != 
    train_array.end(); ++it) {
        it->queue.print(cout);
    }
    cout << "}" << endl;
    // prints everythign in the station array as well as where the train is
    for (std::vector<Waitlist>::iterator it = station_array.begin(); 
         it != station_array.end(); ++it) {
        if (count == conductor) {
            cout << "TRAIN: ";
        }
        else {
            cout << "       ";
        }
        cout << "[" << count << "] " << station_array.at(count).station_name 
             << " {";  
        it->queue.print(cout);
        cout << "}" << endl;

        count += 1;
    }    
}

/*
 * name:      board_train
 * purpose:   adds passengers from the station_array to the train_array in the 
 *            correct position 
 * arguments: none
 * returns:   none 
 * effects:   adds passengers from the station_array to the train_array
 */
void MetroSim::board_train() {
    while (station_array.at(conductor).queue.size() != 0) {
        // sets a temporary variable equal to the value we are moving
        Passenger transfer_p = station_array.at(conductor).queue.front();
        station_array.at(conductor).queue.dequeue();

        // addds passenger to train array
        train_array.at(transfer_p.to).queue.enqueue(transfer_p);
    }
}

/*
 * name:      exit_train
 * purpose:   removed passengers form the train_array and prints them to the 
 *            provided output file. 
 * arguments: none
 * returns:   none 
 * effects:   removes passenger and prints to output file 
 */
void MetroSim::exit_train(ofstream &out_file) {
    while (train_array.at(conductor).queue.size() != 0) {
        // sets a temporary variable equal to the value we are moving
        Passenger remove_p = train_array.at(conductor).queue.front();
        train_array.at(conductor).queue.dequeue();

        // prints to out file 
        out_file << "Passenger " << remove_p.id << " left train at station " << 
        train_array.at(conductor).station_name << endl;
    }
}
