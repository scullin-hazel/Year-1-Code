/*
 * HuffmanCoder.h
 * Hazel Scullin
 * November 17, 2022
 *
 * CS 15 Project 3: Zap
 *
 * This is the interface for the HuffmanCoder class. The HuffmanCoder class 
 * allows for the compression and decompression of text files. To do so it 
 * follows much of the logic of a Huffman coding algorithm. The class has 
 * two main functions in within it. One for "zapping" the text by compressing
 * it and one for "unzapping" by decompressing both of which enlist the 
 * help of a huffman tree.
 *
 */

#ifndef __HUFFMANCODER_H
#define __HUFFMANCODER_H

#include "BinaryIO.h"
#include "HuffmanTreeNode.h"
#include <fstream>
#include <ostream>
#include <queue>
#include <string>

using namespace std;

class HuffmanCoder {
public:
    HuffmanCoder(); // constructor for memeber variables of the class
    void encoder(string input_file, string output_file);
    // takes a text file named input_file, compresses its text, and
    // stores the result in a file named output_file.
    void decoder(string input_file, string output_file);
    // takes a zapped file named input_file, decompresses it, and
    // stores the resulting text in a file named output_file.
    void count_freqs(std::istream &text);
    // counts the frequencies of characters in the inputfile
    void build_tree(); // builds a huffman tree
    template<typename streamtype>
    void open_or_die(streamtype &stream, string file_name);
    // tries to open a given file
    void encode_string(HuffmanTreeNode *root, string encoding);
    // generate the binary codes for each character by following the
    // path to the character from the root
    void encode_text(std::istream &text, string outfile_name);
    // iterate over the original text, look up each character's code,
    // and append that code to the  original encoded binary string
    string serialize_tree(HuffmanTreeNode *root);
    // to serialize the given tree
    void serialize_helper(HuffmanTreeNode *root, string *stringy);
    // traverses tree and stores the values of it as a preorder traversal
    HuffmanTreeNode *deserialize_tree(string serial_tree);
    // given a serialized tree as input, it reconstructs the
    // Huffman tree and returns a pointer to its root.
    void build(HuffmanTreeNode *root, string serial_tree, int *count);
    // given a serialized tree as input, it reconstructs the
    // Huffman tree and returns a pointer to its root
    void decode_tree(HuffmanTreeNode *root);
    // read in bits one at a time wand traverse tree until you reach
    // then a leaf node, append the character in that leaf node to the
    // overall decoded message.
    void delete_tree(HuffmanTreeNode *root);
    // deletes the tree, freeing the heap data


private:
    int freq_array[256] = {0};
    priority_queue<HuffmanTreeNode *, vector<HuffmanTreeNode *>, NodeComparator>
                     my_pq;
    HuffmanTreeNode *primary_root;
    string           encoding_arr[256];
    string           encoded_text;
    ofstream         output_file_stream;
};

#endif