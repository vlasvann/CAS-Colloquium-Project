#include <iostream>
#include <string>
#include <cassert>
#include "parser.h"

void test_parseNatural() {
    Parser parser;

    assert(parser.parseNatural("0000").toString() == "0");
    assert(parser.parseNatural("000123").toString() == "123");
    assert(parser.parseNatural("123").toString() == "123");
    assert(parser.parseNatural("0000000009").toString() == "9");
    assert(parser.parseNatural("000000").toString() == "0");
    assert(parser.parseNatural("0").toString() == "0");
    assert(parser.parseNatural("999999999999").toString() == "999999999999");
    assert(parser.parseNatural("  0 ").toString() == "0");
    assert(parser.parseNatural("10").toString() == "10");
    
    bool caught = false;
    try { parser.parseNatural(""); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("   "); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("12a3"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("-123"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("000000 0009"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("1 2 3"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("meowmeow"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseNatural("43748 7"); } catch (...) { caught = true; }
    assert(caught);
    std::cout << "test_parseNatural() прошёл успешно\n";
}

void test_parseInteger() {
    Parser parser;

    assert(parser.parseInteger("000").toString() == "0");
    assert(parser.parseInteger("000123").toString() == "123");
    assert(parser.parseInteger("-123").toString() == "-123");
    assert(parser.parseInteger("-00045").toString() == "-45");
    assert(parser.parseInteger("+78").toString() == "78");
    assert(parser.parseInteger("123").toString() == "123");
    assert(parser.parseInteger("   +00456  ").toString() == "456");
    assert(parser.parseInteger("   -456  ").toString() == "-456");
    assert(parser.parseInteger("-0").toString() == "0");

    bool caught = false;
    try { parser.parseInteger(""); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("   "); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("--5"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("-+5"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("12a3"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("+"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("12 3"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("-45x"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseInteger("1 2 3"); } catch (...) { caught = true; }
    assert(caught);

    std::cout << "test_parseInteger() прошёл успешно\n";
}

void test_parseRational() {
    Parser parser;

    assert(parser.parseRational("3/4").toString() == "3/4");
    assert(parser.parseRational("3").toString() == "3/1");
    assert(parser.parseRational("-5/7").toString() == "-5/7");
    assert(parser.parseRational("+8/4").toString() == "8/4");
    assert(parser.parseRational("-9").toString() == "-9/1");
    assert(parser.parseRational("0/3").toString() == "0/3");
    assert(parser.parseRational("1/1").toString() == "1/1");
    assert(parser.parseRational("0003/4").toString() == "3/4");
    assert(parser.parseRational("3/0004").toString() == "3/4");
    assert(parser.parseRational("   3/4   ").toString() == "3/4");
    assert(parser.parseRational("3 / 4").toString() == "3/4");
    assert(parser.parseRational("999999/888888").toString() == "999999/888888");
    assert(parser.parseRational("1/001").toString() == "1/1");
    assert(parser.parseRational("-0005/00007").toString() == "-5/7");
    assert(parser.parseRational("   +8/4  ").toString() == "8/4");
    assert(parser.parseRational("  -5/7 ").toString() == "-5/7");
    assert(parser.parseRational("0").toString() == "0/1");
    assert(parser.parseRational("1").toString() == "1/1");
    assert(parser.parseRational("-0/5").toString() == "0/5");
    assert(parser.parseRational("+0/9").toString() == "0/9");

    bool caught = false;
    try { parser.parseRational(""); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("   "); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3/0"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("1/000"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3//4"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("/4"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("4/"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3/4a"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("a/4"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("a/b"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3/-4"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3/4 5"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3/x4"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parseRational("3/   "); } catch (...) { caught = true; }
    assert(caught);


    std::cout << "test_parseRational() прошёл успешно\n";
}

void test_parsePolynomial() {
    Parser parser;

    assert(parser.parsePolynomial("x").toString() == "x^1");
    assert(parser.parsePolynomial("5").toString() == "5");
    assert(parser.parsePolynomial("-5").toString() == "-5");
    assert(parser.parsePolynomial("x+1").toString() == "x^1+1");
    assert(parser.parsePolynomial("x^2-3x+5").toString() == "x^2-3x^1+5");
    assert(parser.parsePolynomial("x+x").toString() == "2x^1");
    assert(parser.parsePolynomial("x^3+x^2+x+1").toString() == "x^3+x^2+x^1+1");
    assert(parser.parsePolynomial("+1/2x^3-3/4x^2+5").toString() == "1/2x^3-3/4x^2+5");
    assert(parser.parsePolynomial("3/4x^2").toString() == "3/4x^2");
    assert(parser.parsePolynomial("-2x").toString() == "-2x^1");
    assert(parser.parsePolynomial("x^5+1").toString() == "x^5+1");
    assert(parser.parsePolynomial("  x^2 + 3  ").toString() == "x^2+3");
    assert(parser.parsePolynomial("x+x+x").toString() == "3x^1");
    assert(parser.parsePolynomial("7x^0").toString() == "7");
    assert(parser.parsePolynomial("0x^2+3").toString() == "3");
    assert(parser.parsePolynomial("x^0").toString() == "1");
    assert(parser.parsePolynomial("-x^0").toString() == "-1");
    assert(parser.parsePolynomial("x^1").toString() == "x^1");
    assert(parser.parsePolynomial("+x^3").toString() == "x^3");
    assert(parser.parsePolynomial("x^2+x^2-2x^2").toString() == "0");  
    assert(parser.parsePolynomial("0").toString() == "0");
    assert(parser.parsePolynomial("0x^5+0x^3+0x^2+0x+0").toString() == "0");
    assert(parser.parsePolynomial("x-x").toString() == "0");
    assert(parser.parsePolynomial("-x+x").toString() == "0");
    assert(parser.parsePolynomial("x^2+x^2").toString() == "2x^2");

    bool caught = false;
    try { parser.parsePolynomial(""); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("   "); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("x^a"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("++x"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("3//4x"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("x^"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("+"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("-x^2+"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("3x^2b"); } catch (...) { caught = true; }
    assert(caught);

    caught = false;
    try { parser.parsePolynomial("x^^2"); } catch (...) { caught = true; }
    assert(caught);

    std::cout << "test_parsePolynomial() прошёл успешно\n";
}

int main() {
    test_parseNatural();
    test_parseInteger();
    test_parseRational();
    test_parsePolynomial();
    std::cout << "\nВсе assert-тесты Parser успешно пройдены!\n";
    return 0;
}
