/*
 * RPNCalc.h
 * Hazel Scullin
 * October 18, 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * The purpose of this file is to simulate an RPN calculator by calling
 * an instance of a DatumStack. We then manipulate this instance of the 
 * DatumStack using basic mathmatical operations and comparisons. This 
 * particular file is the interface for the RPNCalc class. It begins our 
 * command loop and has functions that allow execution on files and strings 
 * in addition to the basic mathmatical operations and comparisons.
 * 
 */

#ifndef __RPNCALC_H
#define __RPNCALC_H

#include "Datum.h"
#include "DatumStack.h"

using namespace std;

class RPNCalc { 
public:
        RPNCalc(); // initializes the RPNCalc object
        void run(); // calls command loop

private:

        bool keep_looping; // bool to control for 'quit'

        // MOVE THESE TO PRIVATE ONCE THEY ARE TESTED 
        void command_loop(istream &command_source);
        // handles all the inputs and calling the according functions

        void add_num(Datum number); // pushes a Datum containing the 
        // number onto the stack
        void add_true(); // pushes a Datum with the boolean true on the stack
        void add_false(); // pushes a Datum with the boolean false on the stack
        void not_command(); // pushes a datum with the opposite boolean value 
        // ƒof the popped element to be pushed on the stack.
        void print(); // prints the value on the top of the stack to cout 
        void clear(); // clears the calculator, emptying the stack.
        void drop(); // removes top element from the stack
        void dup(); // duplicates the top element on the stack.
        void swap(); // swaps the top two elements on the stack.

        // the maths
        void add(); // add two integers
        void subtract(); // subtract two integers
        void multiply(); // multiply two integers
        void divide(); // divide two integers
        void mod(); // mod two integers

        // comparisons
        void less_than(); // check if x < y
        void less_than_or_equal(); // check if x <= y
        void greater_than(); // check if x > y
        void greater_than_or_equal(); // check if x >= y
        void equals(); // check if x == y

        DatumStack calculator; 
        bool got_int(string s, int *resultp); // provided funtion to check
        // if the given input is an integer
        bool exec(); // execute the commands in the rstring at the 
        // top of the stack
        bool file(string file_name); // to execute the commands in the file 
        // thats given at the top of the stack in an rstring
        string fix_rString(string name); // removes the brackets and 
        // extraneous spaces off of an rString
        string file_support(); // pops and stores element from stack and 
        // calls fix_rString on it. - to support file 
        void if_command(); // either exec the top most rstring or the 
        // rstring second from the top (depending on conditional)
        string parseRString(std::istream &input);
        
};

#endif