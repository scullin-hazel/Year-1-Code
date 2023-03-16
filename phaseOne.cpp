/*
 * phaseOne.cpp
 * Hazel Scullin
 * November 7, 2022
 *
 * CS 15 Project 3: Zap
 *
 * This is the implementation for three main functions in the ZAP program.
 * Count_freqs is for counting the frequencies of each character in a given
 * input. It accounts for spaces and newlines. Serialize_tree converts a
 * huffman tree into string format, AKA the tree is serialized. And
 * deserialize_tree takes the serialized tree string as input
 * and it reconstructs the Huffman tree. I implemented these functions
 * using two helper functions named serialize_helper and build. They
 * supported the main functions above.
 */

#include "phaseOne.h"
#include "HuffmanTreeNode.h"
#include <iostream>

using namespace std;

/*
 * name:      count_freqs
 * purpose:   to count the frequencies of each of the characters in the
 *            array
 * arguments: the istream from which we read the characters
 * returns:   none
 * effects:   prints to cout the frequencies
 */
void count_freqs(std::istream &text) {
    int  freq_array[256] = {0};
    char character;

    while (text.get(character)) {
        freq_array[int(character)] += 1;
    }

    for (int i = 0; i < 256; i++) {
        if (freq_array[i] > 0) {
            cout << char(i) << ": " << freq_array[i] << endl;
        }
    }
}

/*
 * name:      serialize_tree
 * purpose:   to serialize the given tree
 * arguments: the root of the huffman tree to be serialized
 * returns:   the string containing the serialized version of the tree
 * effects:   adds to the string named serialized passed into the helper func
 */
string serialize_tree(HuffmanTreeNode *root) {
    string serialized;
    serialize_helper(root, &serialized);
    return serialized;
}

/*
 * name:      serialize_helper
 * purpose:   traverses tree and stores the values of it as a preorder
 *            traversal
 * arguments: the root of the huffman tree to be processed and the string
 *            to be added to with the tree values
 * returns:   none
 * effects:   adds to the string named stringy thats passed into the function
 */
void serialize_helper(HuffmanTreeNode *root, std::string *stringy) {
    if (root == nullptr) { return; }
    if (root->get_left() == nullptr) {
        *stringy += "L";
        *stringy += root->get_val();
    } else {
        *stringy += "I";
    }
    serialize_helper(root->get_left(), stringy);
    serialize_helper(root->get_right(), stringy);
}

/*
 * name:      deserialize_tree
 * purpose:   given a serialized tree as input, it reconstructs the
 *            Huffman tree and returns a pointer to its root.
 * arguments: the serialized string
 * returns:   a pointer to the new tree's root
 * effects:   builds a new huffman tree
 */
HuffmanTreeNode *deserialize_tree(std::string serial_tree) {
    int              count = 1;
    HuffmanTreeNode *root  = new HuffmanTreeNode('\0', 0);

    if (serial_tree.empty()) { return root; }

    build(root, serial_tree, &count);
    return root;
}

/*
 * name:      build
 * purpose:   given a serialized tree as input, it reconstructs the
 *            Huffman tree and returns a pointer to its root now that
 *            the root has been created by the deserialize_tree function
 *            and it has handled the case for if there is an empty input.
 * arguments: the root created by deserialize_tree, the serialized tree as
 *            input, and the counter variable.
 * returns:    none
 * effects:   builds a new huffman tree using the tree's string
 */
void build(HuffmanTreeNode *root, string serial_tree, int *count) {
    if ((serial_tree[*count] == 'I') and (root->get_left() == nullptr)) {
        HuffmanTreeNode *newNode = new HuffmanTreeNode('\0', 0);
        *count += 1;
        root->set_left(newNode);
        build(root->get_left(), serial_tree, count);
    }
    if ((serial_tree[*count] == 'L') and (root->get_left() == nullptr)) {
        *count += 1;
        HuffmanTreeNode *newNode = new HuffmanTreeNode(serial_tree[*count], 0);
        root->set_left(newNode);
        *count += 1;
    }
    if ((serial_tree[*count] == 'L') and (root->get_right() == nullptr)) {
        *count += 1;
        HuffmanTreeNode *newNode = new HuffmanTreeNode(serial_tree[*count], 0);
        root->set_right(newNode);
        *count += 1;
        return;
    }
    if ((serial_tree[*count] == 'I') and (root->get_right() == nullptr)) {
        HuffmanTreeNode *newNode = new HuffmanTreeNode('\0', 0);
        *count += 1;
        root->set_right(newNode);
        build(root->get_right(), serial_tree, count);
        return;
    }
}