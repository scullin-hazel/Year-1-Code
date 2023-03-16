/*
 *  unit_tests.h
 *  Hazel Scullin
 *  November 7, 2022
 *
 *  CS 15 Project 3: Zap
 *
 * testing file for functions included in phaseOne
 *
 */

#include "phaseOne.h"
#include <cassert>
#include <sstream>
#include <string>

using namespace std;

void dummy_test() {}

void count_freqs_test() {
    stringstream test_stream;
    test_stream << "bleep BLoop !";
    count_freqs(test_stream);
}

void count_freqs_test2() {
    stringstream test_stream;
    test_stream << "BaNana";
    count_freqs(test_stream);
}

void count_freqs_test3() {
    stringstream test_stream;
    test_stream << "oo \n la l a";
    count_freqs(test_stream);
}

void deserialize_test1() {
    string           huff_tree_encoding = "IIILaLbILeLfILcLd";
    HuffmanTreeNode *tree_root;
    string           re_serializing;

    tree_root      = deserialize_tree(huff_tree_encoding);
    re_serializing = serialize_tree(tree_root);

    assert(huff_tree_encoding == re_serializing);
}
