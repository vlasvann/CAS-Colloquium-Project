#include "../src/rational.h"

#include <cassert>
#include <stdexcept>
#include <iostream>

void test_TRANS_Z_Q() {
    std::cout << "Testing TRANS_Z_Q..." << std::endl;

    Integer i("4");
    Rational r;
    assert(r.TRANS_Z_Q(i).toString() == "4/1");

    std::cout << "TRANS_Z_Q tests passed!" << std::endl;
}

void test_toString() {
    std::cout << "Testing toString..." << std::endl;

    Rational r("4/5");
    assert(r.toString() == "4/5");

    std::cout << "toString tests passed!" << std::endl;
}

void test_default_constructor() {
    std::cout << "Testing Rational default constructor..." << std::endl;

    Rational r;
    assert(r.toString() == "0/1");

    std::cout << "Rational default constructor tests passed!" << std::endl;
}

void test_parameterized_constructor_1() {
    std::cout << "Testing Rational parameterized constructor 1..." << std::endl;

    Integer num("3");
    Natural den("4");
    Rational r(num, den);
    assert(r.toString() == "3/4");

    std::cout << "Rational parameterized constructor test 1 passed!" << std::endl;
}

void test_parameterized_constructor_2() {
    std::cout << "Testing Rational parameterized constructor 2..." << std::endl;

    Integer num("3");
    Natural den("0");
    bool exception_thrown = false;
    try{
        Rational r(num, den);
    }
    catch (const std::invalid_argument& e){
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "Rational parameterized constructor test 2 passed!" << std::endl;
}

void test_string_constructor_1(){
    std::cout << "Testing Rational string constructor 1..." << std::endl;

    Rational r("5");
    assert(r.toString() == "5/1");

    std::cout << "Rational string constructor test 1 passed!" << std::endl;
}

void test_string_constructor_2(){
    std::cout << "Testing Rational string constructor 2..." << std::endl;

    Rational r("3/4");
    assert(r.toString() == "3/4");

    std::cout << "Rational string constructor test 2 passed!" << std::endl;
}

void test_string_constuctor_3(){
    std::cout << "Testing Rational string constructor 3..." << std::endl;

    bool exception_thrown = false;
    try{
        Rational r("3/0");
    }
    catch (const std::invalid_argument& e){
        exception_thrown = true;
    }
    assert(exception_thrown);

    std::cout << "Rational string constructor test 3 passed!" << std::endl;
}

void test_RED_Q_Q_1() {
    std::cout << "Testing RED_Q_Q 1..." << std::endl;

    Rational r("2/3");
    Rational reduced = r.RED_Q_Q();
    assert(reduced.toString() == "2/3");

    std::cout << "RED_Q_Q test 1 passed!" << std::endl;
}

void test_RED_Q_Q_2() {
    std::cout << "Testing RED_Q_Q 2..." << std::endl;

    Rational r("4/6");
    Rational reduced = r.RED_Q_Q();
    assert(reduced.toString() == "2/3");

    std::cout << "RED_Q_Q test 2 passed!" << std::endl;
}

void test_RED_Q_Q_3() {
    std::cout << "Testing RED_Q_Q 3..." << std::endl;

    Rational r("0/6");
    Rational reduced = r.RED_Q_Q();
    assert(reduced.toString() == "0/1");

    std::cout << "RED_Q_Q test 3 passed!" << std::endl;
}

void test_INT_Q_B_1() {
    std::cout << "Testing INT_Q_B 1..." << std::endl;
    
    Rational r("5");
    assert(r.INT_Q_B() == true);

    std::cout << "INT_Q_B test 1 passed!" << std::endl;
}

void test_INT_Q_B_2() {
    std::cout << "Testing INT_Q_B 2..." << std::endl;

    Rational r("3/4");
    assert(r.INT_Q_B() == false);

    std::cout << "INT_Q_B test 2 passed!" << std::endl;
}

void test_INT_Q_B_3() {
    std::cout << "Testing INT_Q_B 3..." << std::endl;

    Rational r("8/4");
    assert(r.INT_Q_B() == true);

    std::cout << "INT_Q_B test 3 passed!" << std::endl;
}

void test_TRANS_Q_Z_1() {
    std::cout << "Testing TRANS_Q_Z 1..." << std::endl;
    
    Rational r("7");
    Integer i = r.TRANS_Q_Z();
    assert(i.toString() == "7");

    std::cout << "TRANS_Q_Z test 1 passed!" << std::endl;
}    

void test_TRANS_Q_Z_2() {
    std::cout << "Testing TRANS_Q_Z 2..." << std::endl;

    Rational r("10/5");
    Integer i = r.TRANS_Q_Z();
    assert(i.toString() == "2");
    
    std::cout << "TRANS_Q_Z test 2 passed!" << std::endl;
}

void test_TRANS_Q_Z_3(){
    std::cout << "Testing TRANS_Q_Z 3..." << std::endl;

    bool exception_thrown = false;
    try {
        Rational r("3/4");
        Integer i = r.TRANS_Q_Z();
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
    }
    assert(exception_thrown);

    std::cout << "TRANS_Q_Z test 3 passed!" << std::endl;
}

void test_isZero_1() {
    std::cout << "Testing isZero 1..." << std::endl;

    Rational r("0");
    assert(r.isZero() == true);

    std::cout << "isZero test 1 passed!" << std::endl;
}

void test_isZero_2() {
    std::cout << "Testing isZero 2..." << std::endl;

    Rational r("0/1");
    assert(r.isZero() == true);

    std::cout << "isZero test 2 passed!" << std::endl;
}

void test_isZero_3() {
    std::cout << "Testing isZero 3..." << std::endl;

    Rational r("1/2");
    assert(r.isZero() == false);

    std::cout << "isZero test 3 passed!" << std::endl;
}

void test_ADD_QQ_Q_1(){
    std::cout << "Testing ADD_QQ_Q 1..." << std::endl;

    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("1"), Natural("2"));

    Rational ans = a1 + a2;
    assert(ans.toString() == "17/14");

    std::cout << "ADD_QQ_Q test 1 passed!" << std::endl;
}

void test_ADD_QQ_Q_2(){
    std::cout << "Testing ADD_QQ_Q 2..." << std::endl;

    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("5"), Natural("2"));

    Rational ans = a1 + a2;
    assert(ans.toString() == "23/9");

    std::cout << "ADD_QQ_Q test 2 passed!" << std::endl;
}

void test_SUB_QQ_Q_1(){
    std::cout << "Testing SUB_QQ_Q 1..." << std::endl;

    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("1"), Natural("2"));

    Rational ans = a1 - a2;
    assert(ans.toString() == "3/14");

    std::cout << "SUB_QQ_Q test 1 passed!" << std::endl;
}

void test_SUB_QQ_Q_2(){
    std::cout << "Testing SUB_QQ_Q 2..." << std::endl;

    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("5"), Natural("2"));

    Rational ans = a1 - a2;
    assert(ans.toString() == "-22/9");

    std::cout << "SUB_QQ_Q test 2 passed!" << std::endl;
}

void test_MUL_QQ_Q_1(){
    std::cout << "Testing MUL_QQ_Q 1..." << std::endl;

    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("3"), Natural("2"));

    Rational ans = a1 * a2;
    assert(ans.toString() == "15/14");

    std::cout << "MUL_QQ_Q test 1 passed!" << std::endl;
}

void test_MUL_QQ_Q_2(){
    std::cout << "Testing MUL_QQ_Q 2..." << std::endl;

    Rational a1(Integer("-1"), Natural("18"));
    Rational a2(Integer("5"), Natural("2"));

    Rational ans = a1 * a2;
    assert(ans.toString() == "-5/36");

    std::cout << "MUL_QQ_Q test 2 passed!" << std::endl;
}

void test_DIV_QQ_Q_1(){
    std::cout << "Testing DIV_QQ_Q 1..." << std::endl;

    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("3"), Natural("2"));

    Rational ans = a1 / a2;
    assert(ans.toString() == "10/21");

    std::cout << "DIV_QQ_Q test 1 passed!" << std::endl;
}

void test_DIV_QQ_Q_2(){
    std::cout << "Testing DIV_QQ_Q 2..." << std::endl;

    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("-5"), Natural("2"));

    Rational ans = a1 / a2;
    assert(ans.toString() == "-1/45");

    std::cout << "DIV_QQ_Q test 2 passed!" << std::endl;
}

void test_DIV_QQ_Q_3(){
    std::cout << "Testing DIV_QQ_Q 3..." << std::endl;

    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("0"), Natural("2"));

    bool isExeptionThrown = false;

    try
    {
        Rational ans = a1 / a2;
    }
    catch (...)
    {
        isExeptionThrown = true;
    }
    assert(isExeptionThrown);

    std::cout << "DIV_QQ_Q test 3 passed!" << std::endl;
}

void test_bigger(){
    std::cout << "Testing bigger operator..." << std::endl;

    Rational r1 = Rational("1/2");
    Rational r2 = Rational("1/4");
    assert(r1 > r2);

    std::cout << "Bigger operator tests passed!" << std::endl;
}

void test_smaller(){
    std::cout << "Testing smaller operator..." << std::endl;

    Rational r1 = Rational("1/2");
    Rational r2 = Rational("1/4");
    assert(r2 < r1);

    std::cout << "Smaller operator tests passed!" << std::endl;
}

void test_smaller_equal(){
    std::cout << "Testing smaller equal operator..." << std::endl;

    Rational r1 = Rational("1/2");
    Rational r2 = Rational("1/4");
    assert(r2 <= r1);

    std::cout << "Smaller equal operator tests passed!" << std::endl;
}

void test_bigger_equal(){
    std::cout << "Testing bigger equal operator..." << std::endl;

    Rational r1 = Rational("1/2");
    Rational r2 = Rational("1/4");
    assert(r1 >= r2);

    std::cout << "Bigger equal operator tests passed!" << std::endl;
}

void test_equal(){
    std::cout << "Testing equal operator..." << std::endl;

    Rational r1 = Rational("1/2");
    Rational r2 = Rational("1/2");
    assert(r1 == r2);

    std::cout << "Equal operator tests passed!" << std::endl;
}

void test_not_equal(){
    std::cout << "Testing not equal operator..." << std::endl;

    Rational r1 = Rational("1/4");
    Rational r2 = Rational("1/2");
    assert(r1 != r2);

    std::cout << "Not equal operator tests passed!" << std::endl;
}

void runAllTests() {
    std::cout << "Starting all tests...\n" << std::endl;
    
    test_toString();
    test_TRANS_Q_Z_1();
    test_TRANS_Q_Z_2();
    test_TRANS_Q_Z_3();
    test_RED_Q_Q_1();
    test_RED_Q_Q_2();
    test_RED_Q_Q_3();
    test_isZero_1();
    test_isZero_2();
    test_isZero_3();
    test_INT_Q_B_1();
    test_INT_Q_B_2();
    test_INT_Q_B_3();
    test_ADD_QQ_Q_1();
    test_ADD_QQ_Q_2();
    test_SUB_QQ_Q_1();
    test_SUB_QQ_Q_2();
    test_DIV_QQ_Q_1();
    test_DIV_QQ_Q_2();
    test_DIV_QQ_Q_3();
    test_MUL_QQ_Q_1();
    test_MUL_QQ_Q_2();
    test_default_constructor();
    test_parameterized_constructor_1();
    test_parameterized_constructor_2();
    test_string_constructor_1();
    test_string_constructor_2();
    test_string_constuctor_3();
    test_bigger();
    test_bigger_equal();
    test_smaller();
    test_smaller_equal();
    test_equal();
    test_not_equal();
    
    std::cout << "\nAll tests passed successfully!" << std::endl;
}

int main() {
    try {
        runAllTests();
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}