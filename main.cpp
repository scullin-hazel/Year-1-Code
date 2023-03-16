/*
 * main.cpp
 * Hazel Scullin
 * November 17, 2022
 *
 * CS 15 Project 3: Zap
 *
 * The purpose of this file is to create and run one instance of the
 * HuffmanCoder class.
 *
 */

#include "HuffmanCoder.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    string command = argv[1];

    // Enforce correct usage: must have exactly 4 command line args.
    if (((argc != 4)) or ((command != "zap") and (command != "unzap"))) {
        cerr << "Usage: ./zap [zap | unzap] inputFile outputFile" << endl;
        exit(1);
    }
    
    // call either encoder or decoder
    HuffmanCoder coder;
    if (command == "zap") {
        coder.encoder(argv[2], argv[3]);
    } else if (command == "unzap") {
        coder.decoder(argv[2], argv[3]);
    }
}
