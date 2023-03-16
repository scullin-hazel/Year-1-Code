/*
 * parser.cpp
 * Hazel Scullin
 * October 15, 2022
 * 
 * CS 15 Project 2: CalcYouLater
 * 
 * The purpose of this file is to to turn whatever is in the input 
 * stream into a string. It is comprised of one functions which 
 * takes a reference to an istream as a parameter to continue 
 * reading input from while it converts it all into string form. 
 * 
 */

#include <sstream>
#include <iostream>

// std::string parseRString(std::istream &input);

// int main() { 
//     std::string output = parseRString(std::cin);

//     std::cout << output << std::endl;
//     return 0;
// }

/*
 * name:      parseRString
 * purpose:   to turn whatever is in the input stream into a string
 * arguments: takes a reference to an istream as a parameter to 
 *            continue reading input from
 * returns:   it returns an rstring
 * effects:   creates a string
 */
std::string parseRString(std::istream &input) {
    
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


