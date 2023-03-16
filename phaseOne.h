/*
 * phaseOne.h
 * Hazel Scullin
 * November 7, 2022
 *
 * CS 15 Project 3: Zap
 *
 * This is the interface for three main functions in the ZAP program.
 * Count_freqs is for counting the frequencies of each character in a given
 * input. It accounts for spaces and newlines. Serialize_tree converts a
 * huffman tree into string format, AKA the tree is serialized. And
 * deserialize_tree takes the serialized tree string as input
 * and it reconstructs the Huffman tree.
 *
 */

#ifndef __PHASEONE_H
#define __PHASEONE_H

#include "HuffmanTreeNode.h"
#include <iostream>

using namespace std;

void count_freqs(std::istream &text); // count the frequencies of each
// of the characters in the array
string serialize_tree(HuffmanTreeNode *root);
// to serialize the given tree
HuffmanTreeNode *deserialize_tree(std::string serial_tree);
// given a serialized tree as input reconstructs the Huffman tree and
// returns a pointer to its root.
void serialize_helper(HuffmanTreeNode *root, std::string *stringy);
// traverses tree and stores the values of it as a preorder traversal
void build(HuffmanTreeNode *root, string serial_tree, int *count);
// given a serialized tree as input, it reconstructs the Huffman tree
// and returns a pointer to its root

#endif