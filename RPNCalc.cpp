/*
 * RPNCalc.cpp
 * Hazel Scullin
 * October 18, 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * The purpose of this file is to be the implementation of the RPNCalc class. 
 * There are funtions within this file to perform basic mathmatical operations
 * and comparisons. There are also functions to execute operations on files as
 * well as strings. It operates as a loop that reads in commands.
 * 
 * 
 */
#include "RPNCalc.h"
#include "DatumStack.h"

#include <sstream>
#include <fstream>
#include <iostream>


using namespace std;

/*
 * name:      RPNCalc constructor
 * purpose:   constuct the RPNCalc object
 * arguments: none
 * returns:   none 
 * effects:   creates a DatumStack named calculator
 */
RPNCalc::RPNCalc() {
        keep_looping = false;
}

/*
 * name:      run
 * purpose:   call command loop 
 * arguments: none
 * returns:   none 
 * effects:   calls command loop to get program on its feet
 */
void RPNCalc::run() {
        keep_looping = true;
        command_loop(cin);
        cerr << "Thank you for using CalcYouLater." << endl;
}

/*
 * name:      command_loop
 * purpose:   handles all the inputs and calling the according functions
 * arguments: command source to read from
 * returns:   none 
 * effects:   works with the stack to make edits and perform operations
 */
void RPNCalc::command_loop(istream &command_source) {
        string command = "";
        int result;
        while ((keep_looping != false) and (command_source >> command)) {
        try {
                
        if (command == "#t") {
                add_true();
        }
        else if (command == "#f") {
                add_false();
        }
        else if (command == "print") {
                print();
        }
        else if (command == "clear") {
                clear();
        }
        else if (command == "drop") {
                drop();
        }
        else if (command == "dup") {
                dup();
        }
        else if (command == "swap") {
                swap();
        }
        else if (command == "+") {
                add();
        }
        else if (command == "-") {
                subtract();
        }
        else if (command == "*") {
               multiply();
        }
        else if (command == "/") {
                divide();
        }
        else if (command == "mod") {
                mod();
        }
        else if (command == "<") {
                less_than();
        }
        else if (command == "<=") {
                less_than_or_equal();
        }
        else if (command == ">") {
                greater_than();
        }
        else if (command == ">=") {
                greater_than_or_equal();
        }
        else if (command == "==") {
                equals();
        }
        else if (got_int(command, &result)) {
                Datum integer(result);
                add_num(integer);
        }
        else if (command == "exec") {
                keep_looping = exec();
                
        }
        else if (command == "{") {
                string parsed_string = parseRString(command_source);
                Datum rstring(parsed_string);
                calculator.push(rstring);
        }
        else if (command == "quit") {
                keep_looping = false;
        }
        else if (command == "file") {
                string file_name = file_support();
                if (file(file_name) == false) {
                         keep_looping = false;
                }
        }
        else if (command == "if") {
                if_command();
        }
        else if (command == "not") {
                not_command();
        }
        else {
                cerr << command << ": unimplemented" << endl;
        }
        }
        catch (exception &e) {
                cerr << "Error: " << e.what() << endl;
        }
        }
}

/*
 * name:      add_num
 * purpose:   pushes a Datum object containing the number onto the stack
 * arguments: a datum object to push onto the stack
 * returns:   none 
 * effects:   adds a number datum to the stack 
 */
void RPNCalc::add_num(Datum number) {
        calculator.push(number);
}

/*
 * name:      got_int
 * purpose:   tests if the string is an integer, returns true or false 
 *            and updates what the pointer is pointing to
 * arguments: string to be tested and the pointer to the integer we will
 *            update if the boolean returns true
 * returns:   Return true if the string s can be interpreted as an 
 *            integer number 
 * effects:   places the associated integer into the location pointed 
 *            to by resultp.
 */
bool RPNCalc::got_int(string s, int *resultp) {
        /* Holds the first non-whitespace character after the integer */
        char extra;
        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name:      add_true
 * purpose:   pushes a Datum with the boolean true on the stack
 * arguments: none
 * returns:   none 
 * effects:   adds a true boolean datum to the stack
 */
void RPNCalc::add_true() {
        Datum true_bool(true);
        calculator.push(true_bool);

}

/*
 * name:      add_false
 * purpose:   pushes a Datum with the boolean false on the stack
 * arguments: none
 * returns:   none 
 * effects:   adds a false boolean datum to the stack 
 */
void RPNCalc::add_false() {
        Datum false_bool(false); 
        calculator.push(false_bool);
}

/*
 * name:      print
 * purpose:   prints the value on the top of the stack to cout 
 *            (without popping it)
 * arguments: none
 * returns:   none 
 * effects:   prints value to cout 
 */
void RPNCalc::print() {
        cout << calculator.top().toString() << endl;
}

/*
 * name:      clear
 * purpose:   clears the calculator, emptying the stack
 * arguments: none
 * returns:   none 
 * effects:   makes the stack into an empty stack 
 */
void RPNCalc::clear() {
        calculator.clear();
}

/*
 * name:      drop
 * purpose:   removes top element from the stack
 * arguments: none
 * returns:   none 
 * effects:   removes top element from the stack
 */
void RPNCalc::drop() {
        calculator.pop();
}

/*
 * name:      dup
 * purpose:   duplicates the top element on the stack.
 * arguments: none
 * returns:   none 
 * effects:   duplicates the top element on the stack and adds it to the stack
 */
void RPNCalc::dup() {
        Datum temp_dup = calculator.top();
        calculator.push(temp_dup);
}

/*
 * name:      swap
 * purpose:   swaps the top two elements on the stack.
 * arguments: none
 * returns:   none 
 * effects:   swaps the top two elements on the stack.
 */
void RPNCalc::swap() {
        Datum first_pop = calculator.top();
        calculator.pop();

        Datum second_pop = calculator.top();
        calculator.pop();

        calculator.push(first_pop);
        calculator.push(second_pop);
}

/*
 * name:      add
 * purpose:   adds the top two elements on the stack.
 * arguments: none
 * returns:   none 
 * effects:   adds the top two elements on the stack, pops them off the stack,
 *            and adds their sum to the stack
 */
void RPNCalc::add() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();
        
        Datum result(first_operand + second_operand);

        calculator.push(result);
}

/*
 * name:      subtract
 * purpose:   subtract the top element on the stack from the one below it. 
 * arguments: none
 * returns:   none 
 * effects:   pops the top two elements off the stack, and adds their 
 *            result to the stack
 */
void RPNCalc::subtract() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();
        
        Datum result(first_operand - second_operand);

        calculator.push(result);
}

/*
 * name:      multiply
 * purpose:   multiplies the top two elements on the stack.
 * arguments: none
 * returns:   none 
 * effects:   multiplies the top two elements on the stack, pops them off the 
 *            stack, and adds their total to the stack
 */
void RPNCalc::multiply() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();
        
        Datum result(first_operand * second_operand);

        calculator.push(result);
}

/*
 * name:      divide
 * purpose:   divide the top element on the stack from the one below it. 
 * arguments: none
 * returns:   none 
 * effects:   pops the top two elements off the stack, and adds their 
 *            result to the stack
 */
void RPNCalc::divide() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();
        
        if (second_operand == 0) {
                throw runtime_error("division by 0.");
        }

        Datum result(first_operand / second_operand);

        calculator.push(result);
}

/*
 * name:      mod
 * purpose:   mod the top element on the stack from the one below it. 
 * arguments: none
 * returns:   none 
 * effects:   pops the top two elements off the stack, and adds their 
 *            result to the stack
 */
void RPNCalc::mod() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();
        
        if (second_operand == 0) {
                throw runtime_error("division by 0.");
        }

        Datum result(first_operand % second_operand);

        calculator.push(result);
}

/*
 * name:      less_than
 * purpose:   compares the second element on the stack with the first element
 *            to see if it is less than the first
 * arguments: none
 * returns:   none 
 * effects:   pops the first two elements off the stack, and if both are 
 *            integers then it pushes the boolean result on the stack.
 */
void RPNCalc::less_than() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();

        if (first_operand < second_operand) {
                add_true();
        }
        else {
                add_false();
        }
}

/*
 * name:      less_than_or_equal
 * purpose:   compares the second element on the stack with the first element
 *            to see if it is less than or equal to the first
 * arguments: none
 * returns:   none 
 * effects:   pops the first two elements off the stack, and if both are 
 *            integers then it pushes the boolean result on the stack.
 */
void RPNCalc::less_than_or_equal() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();

        if (first_operand <= second_operand) {
                add_true();
        }
        else {
                add_false();
        }
}

/*
 * name:      greater_than
 * purpose:   compares the second element on the stack with the first element
 *            to see if it is greater than the first
 * arguments: none
 * returns:   none 
 * effects:   pops the first two elements off the stack, and if both are 
 *            integers then it pushes the boolean result on the stack.
 */
void RPNCalc::greater_than() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();

        if (first_operand > second_operand) {
                add_true();
        }
        else {
                add_false();
        }

}

/*
 * name:      greater_than_or_equal
 * purpose:   compares the second element on the stack with the first element
 *            to see if it is greater than or equal to the first
 * arguments: none
 * returns:   none 
 * effects:   pops the first two elements off the stack, and if both are 
 *            integers then it pushes the boolean result on the stack.
 */
void RPNCalc::greater_than_or_equal() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();

        if (first_operand >= second_operand) {
                add_true();
        }
        else {
                add_false();
        }
}

/*
 * name:      equals
 * purpose:   compares the second element on the stack with the first element
 *            to see if they are equal
 * arguments: none
 * returns:   none 
 * effects:   pops the first two elements off the stack, and if both are 
 *            integers then it pushes the boolean result on the stack.
 */
void RPNCalc::equals() {
        Datum first_pop(calculator.top());
        calculator.pop();

        Datum second_pop(calculator.top());
        calculator.pop();

        int second_operand = first_pop.getInt();
        int first_operand = second_pop.getInt();

        if (first_operand == second_operand) {
                add_true();
        }
        else {
                add_false();
        }
}

/*
 * name:      exec
 * purpose:   to execute the ccommands in the rstring at the top of the stack
 * arguments: none
 * returns:   a boolean indicating whether or not the user "quit" the program 
 * effects:   throws an error if necessary, creates an sstream out of 
 *            the rstring and calls the command loop on it. 
 */
bool RPNCalc::exec() {
        string command_Rstring = "";

        // stores and pops the datum at the stop of the stack
        Datum temp = calculator.top();
        calculator.pop();

        // get the rstring and make it a stream, catches error if necessary
        try { 
                command_Rstring = temp.getRString();
        }
        catch (const runtime_error &e) {
                throw runtime_error("cannot execute non rstring");
        }

        // send it to the get_command function as an sstream 
        command_Rstring = fix_rString(command_Rstring);
        stringstream ss(command_Rstring);
        command_loop(ss);
        
        return true;
}

/*
 * name:      file
 * purpose:   to execute the commands in the file thats given at the top of
 *            the stack in an rstring
 * arguments: the name of the file to be opened
 * returns:   a boolean indicating whether or not the user "quit" the program 
 * effects:   throws an error if necessary, creates a file stream out of 
 *            the file and calls the command loop on it. 
 */
bool RPNCalc::file(string file_name) {
        ifstream file_info;
        
        // FILE IO like open_or_die
        file_info.open(file_name);
        if (not file_info.is_open()) {
                cerr << "Unable to read " + file_name << endl;
                return true;
        }

        command_loop(file_info);
        
        file_info.close();
        return true;
}

/*
 * name:      file_support
 * purpose:   support for file, pops and stores element from stack and calls 
 *            fix_rString on it. 
 * arguments: none
 * returns:   the fresh rString in the correct format
 * effects:   get rstring and makes the appropriate edits by calling 
 *            fix_rString
 */
string RPNCalc::file_support() {
        string command_Rstring = "";

        Datum temp = calculator.top();
        calculator.pop();

        // get the rstring and make it a stream
        try { 
                command_Rstring = temp.getRString();
        }
        catch (const runtime_error &e) {
                throw runtime_error("file operand not rstring");
        }

        command_Rstring = fix_rString(command_Rstring);

        return command_Rstring;
}

/*
 * name:      fix_rString
 * purpose:   a funtion to supprt file and exec that takes the brackets 
 *            and extraneous spaces off of an rString
 * arguments: the rstring to be fized
 * returns:   string of whatever was on the top of the stack (minus its 
 *            brackets and spaces).
 * effects:   takes brackets and spaces off of an rString
 */
string RPNCalc::fix_rString(string name) {
        // if its empty
        if (name.size() == 3) {
                name.clear();
                return name;
        }

        name.erase(name.begin());
        name.erase(name.begin());
        name.pop_back();
        name.pop_back();

        return name;
}

/*
 * name:      if_command
 * purpose:   depending on the conditional in the stack third from the top
 *            this function will either exec the top most rstring or the 
 *            rstring second from the top. 
 * arguments: none
 * returns:   none
 * effects:   executes one of the top two rstrings on the stack 
 *            (if they are rstrings)
 */
void RPNCalc::if_command() {
        // pop and store
        Datum false_case_first = calculator.top();
        calculator.pop();
        Datum true_case_second = calculator.top();
        calculator.pop();
        Datum bool_case = calculator.top();
        calculator.pop();

        try {
                // depending on the conditional do the first case or the second
                if (bool_case.getBool() == true) {
                        calculator.push(true_case_second);
                }
                else {
                        calculator.push(false_case_first);
                }    
        }
        catch (const runtime_error &e) { 
                throw runtime_error("expected boolean in if test");
        }

        try { 
                exec();
        }
        catch (const runtime_error &e) {
                throw runtime_error("expected rstring in if branch");
        }
}

/*
 * name:      parseRString
 * purpose:   to turn whatever is in the input stream into a string
 * arguments: takes a reference to an istream as a parameter to 
 *            continue reading input from
 * returns:   it returns an rstring
 * effects:   creates a string
 */
std::string RPNCalc::parseRString(std::istream &input) {

    std::string growing_string = "{";
    std::string read_in_char = " "; 

    while ((read_in_char != "}") and (not input.eof())) {
        input >> read_in_char;
        
        if (read_in_char == "{") {
            growing_string += " " + parseRString(input);
        }
        else {
            growing_string += " " + read_in_char;
        }
    }

    return growing_string;
}

/*
 * name:      not_command
 * purpose:   pushes a datum with the opposite boolean value of the popped 
 *            element to be pushed on the stack.
 * arguments: none
 * returns:   none
 * effects:   pushes a new opposite bool onto the stack
 */
void RPNCalc::not_command() {
        Datum bool_case = calculator.top();
        calculator.pop();
        
        if (bool_case.getBool() == true) {
                add_false();
        }
        else {
                add_true();
        }
}