/*
*  unit_tests.h
*  Hazel Scullin
*  October 18, 2022
* 
*  CS 15 Project 2: CalcYouLater
*
*  testing file for functions included in the DatumStack class
*
*/

#include "Datum.h"
#include "DatumStack.h"
#include "RPNCalc.h"
#include <cassert>

using namespace std;

void dummy_test() {
    
} 

void constructor_test() {
    DatumStack test_stack;
}

void second_constructor_test() {
    Datum integerD(1);
    Datum integerD2(2);
    Datum integerD3(3);
    Datum integerD4(4);
    Datum integerD5(5);
    Datum integerD6(6);
    Datum arr [6] = {integerD, integerD2, integerD3, integerD4, integerD5, 
    integerD6};
    DatumStack test_stack(arr, 6);
}

// tests the isEmpty function with an empty list
void isEmpty_test() {
    DatumStack test_stack;
    assert(test_stack.isEmpty() == true);
}

// tests the isEmpty function with a filled list
void isEmpty_test_filled(){
    DatumStack test_stack;
    // create datum objects to use 
    Datum integerD(1);
    Datum integerD2(2);
    Datum integerD3(3);

    // add them to the stack 
    test_stack.push(integerD);
    test_stack.push(integerD2);
    test_stack.push(integerD3);
    assert(test_stack.isEmpty() == false);
}

// tests the size function with an empty list
void size_test() {
    DatumStack test_stack;
    assert(test_stack.size() == 0);
}

// tests the size function with a filled list
void size_test_filled() {
    DatumStack test_stack;
    // create datum objects to use 
    Datum integerD(1);
    Datum integerD2(2);
    Datum integerD3(3);

    // add them to the stack 
    test_stack.push(integerD);
    test_stack.push(integerD2);
    test_stack.push(integerD3);
    assert(test_stack.size() == 3);
}

// tests the top function with a filled list
void top_test(){
    DatumStack test_stack;
    // create datum objects to use 
    Datum integerD(1);
    Datum integerD2(2);
    Datum integerD3(3);

    // add them to the stack 
    test_stack.push(integerD);
    test_stack.push(integerD2);
    test_stack.push(integerD3);
    assert(test_stack.top() == integerD3);
}

void pop_test(){
    DatumStack test_stack;
    // create datum objects to use 
    Datum integerD(1);
    Datum integerD2(2);
    Datum integerD3(3);

    // add them to the stack 
    test_stack.push(integerD);
    test_stack.push(integerD2);
    test_stack.push(integerD3);
    assert(test_stack.top() == integerD3);
    test_stack.pop();
    assert(test_stack.top() == integerD2);
    test_stack.pop();
    assert(test_stack.top() == integerD);
    assert(test_stack.size() == 1);
}

// checks the top function after having constructed the 
// datum stack with the second constructor
void top_size_w_constructor2() {
    Datum integerD(1);
    Datum integerD2(2);
    Datum integerD3(3);
    Datum integerD4(4);
    Datum integerD5(5);
    Datum integerD6(6);
    Datum arr [6] = {integerD, integerD2, integerD3, integerD4, integerD5, 
    integerD6};
    DatumStack test_stack(arr, 6);
    assert(test_stack.top() == integerD6);
    assert(test_stack.size() == 6);
}

// tests the runtime error associated with the top function
void error_test_top() {
    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    string error_message = "";

    DatumStack test_stack;
    try {
        test_stack.top();
    }
    catch (const runtime_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        runtime_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// tests the runtime error associated with the pop function
void error_test_pop() {
    // var to track whether range_error is thrown
    bool runtime_error_thrown = false;

    // var to track any error messages raised
    string error_message = "";

    DatumStack test_stack;
    try {
        test_stack.pop();
    }
    catch (const runtime_error &e) {
        // if insertAt is correctly implemented, a range_error will be thrown,
        // and we will end up here
        runtime_error_thrown = true;
        error_message = e.what();
    }

    // out here, we make our assertions
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void test_add_true() {
    RPNCalc calc; 

    Datum true_bool(true);

    calc.add_true();

    assert(calc.calculator.top() == true_bool);
}

void test_add_false() {
    RPNCalc calc; 

    Datum false_bool(false);

    calc.add_false();

    assert(calc.calculator.top() == false_bool);
}

// tests if clear function works on a stack of booleans
void test_clear() {
    RPNCalc calc; 

    Datum false_bool(false);

    calc.add_false();
    calc.add_false();
    calc.add_false();

    assert(calc.calculator.top() == false_bool);
    assert(calc.calculator.size() == 3);

    calc.clear();

    assert(calc.calculator.size() == 0);
}

// tests if drop function works on a stack of booleans
void test_drop() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    calc.add_false();
    calc.add_true();
    calc.add_false();

    assert(calc.calculator.top() == false_bool);
    assert(calc.calculator.size() == 3);

    calc.drop();
    assert(calc.calculator.top() == true_bool);
    assert(calc.calculator.size() == 2);

    calc.drop();
    assert(calc.calculator.top() == false_bool);
    assert(calc.calculator.size() == 1);
}

// check this one           ///////////////////////////////////////////////////
void test_print_on_Bool() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    calc.add_false();
    calc.add_true();
    calc.add_false();

    calc.print();

    calc.drop();
    calc.print();

    calc.drop();
    calc.print();
}

void test_add_num() {
    RPNCalc calc;

    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum four(4);

    calc.add_num(one);
    //calc.print();
    assert(calc.calculator.top() == one);
    assert(calc.calculator.size() == 1);

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 2);

    calc.add_num(three);
    //calc.print();
    assert(calc.calculator.top() == three);
    assert(calc.calculator.size() == 3);

    calc.add_num(four);
    //calc.print();
    assert(calc.calculator.top() == four);
    assert(calc.calculator.size() == 4);
}

void test_dup() {
    RPNCalc calc;

    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum four(4);
    Datum five(5);

    calc.add_num(one);
    //calc.print();
    assert(calc.calculator.top() == one);
    assert(calc.calculator.size() == 1);

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 2);

    calc.add_num(three);
    //calc.print();
    assert(calc.calculator.top() == three);
    assert(calc.calculator.size() == 3);

    calc.add_num(four);
    //calc.print();
    assert(calc.calculator.top() == four);
    assert(calc.calculator.size() == 4);

    calc.dup();
    //calc.print();
    assert(calc.calculator.top() == four);
    assert(calc.calculator.size() == 5);

    calc.add_num(five);
    //calc.print();
    assert(calc.calculator.top() == five);
    assert(calc.calculator.size() == 6);

    calc.dup();
    //calc.print();
    assert(calc.calculator.top() == five);
    assert(calc.calculator.size() == 7);
}

void test_dup_on_bool() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    calc.add_false();
    //calc.print();
    calc.add_true();
    //calc.print();
    calc.add_false();
    //calc.print();
    assert(calc.calculator.size() == 3);

    calc.dup();
    //calc.print();

    assert(calc.calculator.top() == false_bool);
    assert(calc.calculator.size() == 4);
}

void test_swap() {
    RPNCalc calc;

    Datum one(1);
    Datum two(2);
    Datum three(3);
    Datum four(4);

    calc.add_num(one);
    //calc.print();

    calc.add_num(two);
    //calc.print();

    calc.add_num(three);
    //calc.print();
    assert(calc.calculator.top() == three);
    assert(calc.calculator.size() == 3);

    calc.add_num(four);
    //calc.print();
    assert(calc.calculator.top() == four);
    assert(calc.calculator.size() == 4);

    calc.swap();
    //calc.print();
    assert(calc.calculator.top() == three);
    assert(calc.calculator.size() == 4);
}

// testing swap on stack of booleans
void test_swap_on_bool() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    calc.add_false();
    //calc.print();
    calc.add_true();
    //calc.print();
    calc.add_false();
    //calc.print();

    assert(calc.calculator.top() == false_bool);
    assert(calc.calculator.size() == 3);

    calc.swap();
    //calc.print();

    assert(calc.calculator.top() == true_bool);
    assert(calc.calculator.size() == 3);
}

void test_add() {
    RPNCalc calc;

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    Datum twelve(12);

    calc.add_num(one);
    //calc.print();

    calc.add_num(three);
    //calc.print();

    calc.add_num(ten);
    //calc.print();

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.add();
    //calc.print();
    assert(calc.calculator.size() == 3);
    assert(calc.calculator.top() == twelve);
}

void test_subtract() {
    RPNCalc calc;

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    Datum eight(8);

    calc.add_num(one);
    //calc.print();

    calc.add_num(three);
    //calc.print();

    calc.add_num(ten);
    //calc.print();

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.subtract();
    //calc.print();
    assert(calc.calculator.size() == 3);
    assert(calc.calculator.top() == eight);
}

void test_multiply() {
    RPNCalc calc;

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    Datum twenty(20);

    calc.add_num(one);
    //calc.print();

    calc.add_num(three);
    //calc.print();

    calc.add_num(ten);
    //calc.print();

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.multiply();
    //calc.print();
    assert(calc.calculator.size() == 3);
    assert(calc.calculator.top() == twenty);
}

void test_divide() {
    RPNCalc calc;

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    Datum five(5);

    calc.add_num(one);
    //calc.print();

    calc.add_num(three);
    //calc.print();

    calc.add_num(ten);
    //alc.print();

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.divide();
    //calc.print();
    assert(calc.calculator.size() == 3);
    assert(calc.calculator.top() == five);
}

// tests mod when the answer should be zero
void test_mod() {
    RPNCalc calc;

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    Datum zero(0);

    calc.add_num(one);
    //calc.print();

    calc.add_num(three);
    //calc.print();

    calc.add_num(ten);
    //alc.print();

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.mod();
    //calc.print();
    assert(calc.calculator.size() == 3);
    assert(calc.calculator.top() == zero);
}

// tests mod when the answer should be one 
void test_mod_alternate() {
    RPNCalc calc;

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(11);

    calc.add_num(one);
    //calc.print();

    calc.add_num(three);
    //calc.print();

    calc.add_num(ten);
    //alc.print();

    calc.add_num(two);
    //calc.print();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.mod();
    //calc.print();
    assert(calc.calculator.size() == 3);
    assert(calc.calculator.top() == one);
}

void test_less_than() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(two);
    calc.print();
    assert(calc.calculator.top() == two);

    calc.add_num(ten);
    calc.print();
    assert(calc.calculator.top() == ten);

    calc.less_than();
    assert(calc.calculator.top().getBool() == true);
}

void test_less_than_or_equal() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(two);
    calc.print();
    assert(calc.calculator.top() == two);

    calc.add_num(ten);
    calc.print();
    assert(calc.calculator.top() == ten);

    calc.dup();
    calc.print();

    calc.less_than_or_equal();
    assert(calc.calculator.top().getBool() == true);
}

void test_less_than_false() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(ten);
    calc.print();
    assert(calc.calculator.top() == ten);

    calc.add_num(two);
    calc.print();
    assert(calc.calculator.top() == two);

    calc.less_than();
    assert(calc.calculator.top().getBool() == false);
}

void test_greater_than_false() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(two);
    calc.print();
    assert(calc.calculator.top() == two);

    calc.add_num(ten);
    calc.print();
    assert(calc.calculator.top() == ten);

    calc.greater_than();
    assert(calc.calculator.top().getBool() == false);
}

void test_greater_than() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(ten);
    calc.print();
    assert(calc.calculator.top() == ten);

    calc.add_num(two);
    calc.print();
    assert(calc.calculator.top() == two);

    calc.greater_than();
    assert(calc.calculator.top().getBool() == true);
}

void test_greater_than_or_equal() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);
    Datum ten(10);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(two);
    calc.print();
    assert(calc.calculator.top() == two);

    calc.add_num(ten);
    calc.print();
    assert(calc.calculator.top() == ten);

    calc.dup();
    calc.print();

    calc.greater_than_or_equal();
    assert(calc.calculator.top().getBool() == true);
}

void test_isEqual() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(two);
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 3);
    calc.dup();
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 4);

    calc.equals();
    assert(calc.calculator.top() == true_bool);
    assert(calc.calculator.size() == 3);
}

void test_is_not_equal() {
    RPNCalc calc; 

    Datum false_bool(false);
    Datum true_bool(true);

    Datum one(1);
    Datum three(3);
    Datum two(2);

    calc.add_num(one);
    calc.print();

    calc.add_num(three);
    calc.print();

    calc.add_num(two);
    assert(calc.calculator.top() == two);
    assert(calc.calculator.size() == 3);

    calc.equals();
    assert(calc.calculator.top() == false_bool);
    assert(calc.calculator.size() == 2);
}