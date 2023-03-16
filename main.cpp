/*
 * main.cpp
 * Hazel Scullin
 * October 10, 2022
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * The purpose of this program: main.cpp is a driver function that takes input 
 * files from the command line. The program will check if the files can be 
 * opened and then creates a metro simulation and calls it using those files.
 * 
 */ 

#include <iostream>
#include <fstream>
#include <string>
#include "MetroSim.h"

using namespace std;

template<typename streamtype>
void open_or_die(streamtype &stream, string file_name);

int main(int argc, char *argv[])
{
    // declaring file streams if we use them
    ifstream instream;
    ofstream outstream;
    MetroSim MERTO;
    // Enforce correct usage: must have exactly 3 or 4 command line args.
    if (not ((argc == 3) or (argc == 4))) {
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]" 
             << endl;
        exit(1);
    } else {
        open_or_die(instream,  argv[1]);
        open_or_die(outstream,  argv[2]);
        if (argc == 3) {
            MERTO.run(instream, outstream, cin);
        } else {
            // argc == 4
            ifstream commands;
            open_or_die(commands,  argv[3]);
            MERTO.run(instream, outstream, commands);
            commands.close();
        }
        instream.close();
        outstream.close();
    }
    return 0;
}

/*
 * name:      open_or_die
 * purpose:   tries to open a given file
 * arguments: an ifstream or ofstream and the file to be opened
 * returns:   none if file opens, and exits with a print statement 
 *            if opening fails. 
 * effects:   updates numChars to zero and front to nullptr
 */
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not stream.is_open()) {
        cerr << "Error: could not open file " + file_name << endl;
		exit(1);
	}
}