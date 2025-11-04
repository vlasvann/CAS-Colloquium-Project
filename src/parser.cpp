#include "parser.h"

Parser::Parser() {}

Natural Parser::parseNatural(const std::string &input)
{
	(void)input;
    return Natural();
}

Integer Parser::parseInteger(const std::string &input)
{
	(void)input;
    return Integer();
}

Rational Parser::parseRational(const std::string &input)
{
	(void)input;
    return Rational();
}

Polynomial Parser::parsePolynomial(const std::string &input)
{
	(void)input;
    return Polynomial();
}

std::string Parser::toString(const Natural &num)
{
	(void)num;
    std::string str = "52ngg";
    return str;
}

std::string Parser::toString(const Integer &num)
{
	(void)num;
    std::string str = "52ngg";
    return str;
}

std::string Parser::toString(const Rational &num)
{
	(void)num;
    std::string str = "52ngg";
    return str;
}

std::string Parser::toString(const Polynomial &poly)
{
	(void)poly;
    std::string str = "52ngg";
    return str;
}
