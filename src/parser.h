#ifndef ALGEBRAPARSER_H
#define ALGEBRAPARSER_H

#include "natural.h"
#include "integer.h"
#include "rational.h"
#include "polynomial.h"
#include <string>
#include <vector>

class Parser {
public:
	Parser() = default;
    // Парсинг строк в объекты
    Natural parseNatural(const std::string& input);
    Integer parseInteger(const std::string& input);
    Rational parseRational(const std::string& input);
    Polynomial parsePolynomial(const std::string& input);

    // Преобразование объектов в строки
    std::string toString(const Natural& num);
    std::string toString(const Integer& num);
    std::string toString(const Rational& num);
    std::string toString(const Polynomial& poly);
};
#endif
