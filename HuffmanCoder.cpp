/*
 * HuffmanCoder.cpp
 * Hazel Scullin
 * November 17, 2022
 *
 * CS 15 Project 3: Zap
 *
 * This is the implementation for the HuffmanCoder class. The HuffmanCoder class
 * allows for the compression and decompression of text files. To do so it 
 * follows much of the logic of a Huffman coding algorithm. The class has 
 * two main functions in within it. One for "zapping" the text by compressing
 * it and one for "unzapping" by decompressing both of which enlist the 
 * help of a huffman tree. To support these main encoding and decoding 
 * functions are helper functions that cover the individual steps. Theres one
 * for counting the number of instances of a charcter. Theres a function for
 * creatign a huffman tree. Theres also a function for following the huffman 
 * tree to decode the binary sequence for unzapping the file.  
 *
 */
#include "HuffmanCoder.h"
#include "BinaryIO.h"
#include "HuffmanTreeNode.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

/*
 * name:      HuffmanCoder
 * purpose:   initialize the member variables to
 * arguments: none
 * returns:   none
 * effects:   updates memeber variables
 */
HuffmanCoder::HuffmanCoder() {
    for (int i = 0; i < 256; i++) {
        encoding_arr[i] = "";
    }
    primary_root = nullptr;
}

/*
 * name:      encoder
 * purpose:   compreses the text in the input file and puts the new 
 *            compressed version into the output file
 * arguments: the name of the input and output file
 * returns:   none
 * effects:   prints to the output file 
 */
void HuffmanCoder::encoder(string input_file, string output_file) {
    ifstream instream;
    ofstream outstream;

    open_or_die(instream, input_file);

    count_freqs(instream);
    build_tree();

    encode_string(primary_root, "");
    encode_text(instream, output_file);

    instream.close();
    outstream.close();
}

/*
 * name:      decoder
 * purpose:   decompresses a previously zapped file, and saves the
 *            resulting ASCII text to an output file
 * arguments: the name of the input file and output file
 * returns:   none
 * effects:   prints to an output file 
 */
void HuffmanCoder::decoder(string input_file, string output_file) {
    BinaryIO reader;

    // Reads from zapped file named ++filename++.
    // returns a 2-element string vector.
    vector<string> zapped_file_info = reader.readFile(input_file);

    string serialized_tree = zapped_file_info[0];
    encoded_text           = zapped_file_info[1];

    HuffmanTreeNode *root = deserialize_tree(serialized_tree);

    open_or_die(output_file_stream, output_file);

    decode_tree(root);
    delete_tree(root);
}

/*
 * name:      count_freqs
 * purpose:   to count the frequencies of each of the characters in the
 *            input file
 * arguments: the istream from which we read the characters
 * returns:   none
 * effects:   pushes the characters and their counts as nodes onto a
 *            priority queue
 */
void HuffmanCoder::count_freqs(std::istream &text) {
    char character;

    while (text.get(character)) {
        freq_array[int(character)] += 1;
    }

    for (int i = 0; i < 256; i++) {
        if (freq_array[i] > 0) {
            HuffmanTreeNode *node = new HuffmanTreeNode(char(i), freq_array[i]);
            // push onto priority queue
            my_pq.push(node);
        }
    }

    text.clear();
    text.seekg(0);
}

/*
 * name:      build_tree
 * purpose:   builds a huffman tree where leaves correspond to characters
 *            and the Characters that occur less frequently are be further
 *            from the root, and characters that occur more frequently
 *            should be closer to the root.
 * arguments: none
 * returns:   none
 * effects:   takes nodes from a prioity queue and constructs a tree from them
 */
void HuffmanCoder::build_tree() {
    while (my_pq.size() > 1) {
        // stores top two nodes on the prioity queue
        // (minimum frequencies)
        HuffmanTreeNode *node1 = my_pq.top();
        my_pq.pop();
        HuffmanTreeNode *node2 = my_pq.top();
        my_pq.pop();

        // create node containing the freq of the two nodes on top
        // and connect it to the top two nodes
        HuffmanTreeNode *parent = new HuffmanTreeNode(
            '\0', (node1->get_freq() + node2->get_freq()), node1, node2);
        // adds this parent back onto the tree
        my_pq.push(parent);
    }
    primary_root = my_pq.top();
    my_pq.pop();
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
void HuffmanCoder::open_or_die(streamtype &stream, string file_name) {
    stream.open(file_name);
    if (not stream.is_open()) {
        throw runtime_error("Unable to open file " + file_name);
    }
}

/*
 * name:      encode_string
 * purpose:   generate the binary codes for each character by following
 *            the path to the character from the root
 * arguments: the root of the tree and the string in which to store the
 *            encoding (a series fo zeros and ones)
 * returns:   none
 * effects:   adds to the string "encoding"
 */
void HuffmanCoder::encode_string(HuffmanTreeNode *root, string encoding) {
    // base case for if we have reached the bottom of the tree where
    // a character is
    if (root->isLeaf()) {
        encoding_arr[int(root->get_val())] = encoding;
        return;
    }
    // recursive call
    encode_string(root->get_left(), encoding + "0");
    encode_string(root->get_right(), encoding + "1");
}

/*
 * name:      encode_text
 * purpose:   iterate over the original text, look up each character's code,
 *            and append that code to the  original encoded binary string
 * arguments: the input file and the name of the output file
 * returns:   none
 * effects:   stores the encoded binary string and huffman tree in the
 *            output file
 */
void HuffmanCoder::encode_text(std::istream &text, string outfile_name) {
    char   character;
    string input = "";

    // iterate over the original text, look up each character's code,
    // and append that code to the original encoded binary string
    while (text.get(character)) {
        input += encoding_arr[int(character)];
    }

    // store the encoded binary string and huffman tree in the output file
    BinaryIO writer;
    writer.writeFile(outfile_name, serialize_tree(primary_root), input);

    cout << "Success! Encoded given text using " << input.size() << " bits."
         << endl;
}

/*
 * name:      serialize_tree
 * purpose:   to serialize the given tree
 * arguments: the root of the huffman tree to be serialized
 * returns:   the string containing the serialized version of the tree
 * effects:   adds to the string named serialized passed into the helper func
 */
string HuffmanCoder::serialize_tree(HuffmanTreeNode *root) {
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
void HuffmanCoder::serialize_helper(HuffmanTreeNode *root, string *stringy) {
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
HuffmanTreeNode *HuffmanCoder::deserialize_tree(std::string serial_tree) {
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
 * returns:   none
 * effects:   builds a new huffman tree using the tree's string
 */
void HuffmanCoder::build(HuffmanTreeNode *root, string serial_tree,
                         int *count) {
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

/*
 * name:      decode_tree
 * purpose:   read in bits one at a time where for each 0, go to the left
 *            child, and for each 1, go to the right child. Once you
 *            reach a leaf node, append the character in that leaf node
 *            to the overall decoded message.
 * arguments: the root of the huffman tree used for decoding
 * returns:   none
 * effects:   decodes the binary string
 */
void HuffmanCoder::decode_tree(HuffmanTreeNode *root) {
    // repeat loop for as long as the encoded text is
    HuffmanTreeNode *OGroot = root;
    for (unsigned int i = 0; i < (encoded_text.size() + 1); i++) {
        if (root->isLeaf()) {
            output_file_stream << root->get_val();
            root = OGroot;
        }
        // if a zero is encountered, go left
        if (encoded_text[i] == '0') { root = root->get_left(); }
        // if a one is encountered, go right
        if (encoded_text[i] == '1') { root = root->get_right(); }
    }
    if (root != OGroot) {
        throw runtime_error("Encoding did not match Huffman tree.");
    }
}

/*
 * name:      delete_tree
 * purpose:   deletes the tree, freeing the heap data
 * arguments: the root of the tree to be deleted
 * returns:   none
 * effects:   deletes the tree
 */
void HuffmanCoder::delete_tree(HuffmanTreeNode *root) {
    // Base case (empty tree)
    if (root == nullptr) { return; }
    // delete left and right subtree first
    delete_tree(root->get_left());
    delete_tree(root->get_right());

    // then delete the current node
    delete root;
    root = nullptr;
}