#include "parser.h"

Parser::Parser() {}

Natural Parser::parseNatural(const std::string &input)
{
    return Natural();
}

Integer Parser::parseInteger(const std::string &input)
{
    return Integer();
}

Rational Parser::parseRational(const std::string &input)
{
    return Rational();
}

Polynomial Parser::parsePolynomial(const std::string &input)
{
    return Polynomial();
}

std::string Parser::toString(const Natural &num)
{
    std::string str = "52ngg";
    return str;
}

std::string Parser::toString(const Integer &num)
{
    std::string str = "52ngg";
    return str;
}

std::string Parser::toString(const Rational &num)
{
    std::string str = "52ngg";
    return str;
}

std::string Parser::toString(const Polynomial &poly)
{
    std::string str = "52ngg";
    return str;
}
