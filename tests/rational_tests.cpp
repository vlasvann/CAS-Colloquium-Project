#include "../rational.h"

#include <cassert>
#include <stdexcept>

void test_TRANS_Z_Q() {

    Integer i("4");
    Rational r;
    assert(r.TRANS_Z_Q(i).toString() == "4/1");
}

void test_toString() {

    Rational r("4/5");
    assert(r.toString() == "4/5");
}

void test_default_constructor() {

    Rational r;
    assert(r.toString() == "0/1");
}

void test_parameterized_constructor_1() {
    
    Integer num("3");
    Natural den("4");
    Rational r(num, den);
    assert(r.toString() == "3/4");
}

void test_parameterized_constructor_2() {
    
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
}

void test_string_constructor_1(){

    Rational r("5");
    assert(r.toString() == "5/1");
}

void test_string_constructor_2(){

    Rational r("3/4");
    assert(r.toString() == "3/4");
}

void test_string_constuctor_3(){

    bool exception_thrown = false;
    try{
        Rational r("3/0");
    }
    catch (const std::invalid_argument& e){
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void test_RED_Q_Q_1() {

    Rational r("2/3");
    Rational reduced = r.RED_Q_Q();
    assert(reduced.toString() == "2/3");
}

void test_RED_Q_Q_2() {

    Rational r("4/6");
    Rational reduced = r.RED_Q_Q();
    assert(reduced.toString() == "2/3");
}

void test_RED_Q_Q_3() {

    Rational r("0/6");
    Rational reduced = r.RED_Q_Q();
    assert(reduced.toString() == "0/1");
}

void test_INT_Q_B_1() {
    
    Rational r("5");
    assert(r.INT_Q_B() == true);
}

void test_INT_Q_B_2() {

    Rational r("3/4");
    assert(r.INT_Q_B() == false);
}

void test_INT_Q_B_3() {

    Rational r("8/4");
    assert(r.INT_Q_B() == true);
}

void test_TRANS_Q_Z_1() {
    
    Rational r("7");
    Integer i = r.TRANS_Q_Z();
    assert(i.toString() == "7");
}    

void test_TRANS_Q_Z_2() {

    Rational r("10/5");
    Integer i = r.TRANS_Q_Z();
    assert(i.toString() == "2");
    
}

void test_TRANS_Q_Z_exception(){

    bool exception_thrown = false;
    try {
        Rational r("3/4");
        Integer i = r.TRANS_Q_Z();
    } catch (const std::runtime_error& e) {
        exception_thrown = true;
    }
    assert(exception_thrown);
}

void test_isZero_1() {

    Rational r("0");
    assert(r.isZero() == true);
}

void test_isZero_2() {

    Rational r("0/1");
    assert(r.isZero() == true);
}

void test_isZero_3() {

    Rational r("1/2");
    assert(r.isZero() == false);
}

void test_ADD_QQ_Q_1()
{
    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("1"), Natural("2"));

    Rational ans = a1 + a2;
    assert(ans.getNumerator().toString() == "17");
    assert(ans.getDenominator().COM_NN_D(Natural("14")));
}

void test_ADD_QQ_Q_2()
{
    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("5"), Natural("2"));

    Rational ans = a1 + a2;
    assert(ans.getNumerator().toString() == "46");
    assert(ans.getDenominator().COM_NN_D(Natural("18")));
}

void test_SUB_QQ_Q_1()
{
    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("1"), Natural("2"));

    Rational ans = a1 - a2;
    assert(ans.getNumerator().toString() == "3");
    assert(ans.getDenominator().COM_NN_D(Natural("14")));
}

void test_SUB_QQ_Q_2()
{
    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("5"), Natural("2"));

    Rational ans = a1 - a2;
    assert(ans.getNumerator().toString() == "-44");
    assert(ans.getDenominator().COM_NN_D(Natural("18")));
}

void test_MUL_QQ_Q_1()
{
    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("3"), Natural("2"));

    Rational ans = a1 * a2;
    assert(ans.getNumerator().toString() == "15");
    assert(ans.getDenominator().COM_NN_D(Natural("14")));
}

void test_MUL_QQ_Q_2()
{
    Rational a1(Integer("-1"), Natural("18"));
    Rational a2(Integer("5"), Natural("2"));

    Rational ans = a1 * a2;
    assert(ans.getNumerator().toString() == "-5");
    assert(ans.getDenominator().COM_NN_D(Natural("36")));
}

void test_DIV_QQ_Q_1()
{
    Rational a1(Integer("5"), Natural("7"));
    Rational a2(Integer("3"), Natural("2"));

    Rational ans = a1 / a2;
    assert(ans.getNumerator().toString() == "10");
    assert(ans.getDenominator().COM_NN_D(Natural("21")));
}

void test_DIV_QQ_Q_2()
{
    Rational a1(Integer("1"), Natural("18"));
    Rational a2(Integer("-5"), Natural("2"));

    Rational ans = a1 / a2;
    assert(ans.getNumerator().toString() == "-1");
    assert(ans.getDenominator().COM_NN_D(Natural("45")));
}

void test_DIV_QQ_Q_3()
{
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
}