#ifndef ALGEBRAPARSER_H
#define ALGEBRAPARSER_H

#include "natural.h"
#include "integer.h"
#include "rational.h"
#include "polynomial.h"
#include <string>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

class Parser {
public:
	Parser() = default;
    // Вспомогательный метод
    std::string trimAndValidate(const std::string& str, const std::string& errorMessage);

    // Парсинг строк в объекты
    Natural parseNatural(const std::string& input);
    Integer parseInteger(const std::string& input);
    Rational parseRational(const std::string& input);
    Polynomial parsePolynomial(const std::string& input);

    // Преобразование объектов в строки
    std::string toString(const Natural& num) const;
    std::string toString(const Integer& num) const;
    std::string toString(const Rational& num) const;
    std::string toString(const Polynomial& poly) const;
};
#endif
