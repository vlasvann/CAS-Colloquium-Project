#include "parser.h"
#include "polynomial.h"
/*
 * Developed by Kim Karina, group - 4382,
 * Parser — реализация класса для разбора строк в объекты типов Natural, Integer, Rational и Polynomial.
 */

/**
 * @brief Вспомогательная функция для обрезки пробелов и проверки непустоты строки.
 * @param str исходная строка
 * @param errorMessage сообщение об ошибке при пустом вводе
 * @return Очищенная строка без начальных и конечных пробелов
 *
*/
std::string Parser::trimAndValidate(const std::string& str, const std::string& errorMessage) const {
    size_t start = str.find_first_not_of(' ');
    if (start == std::string::npos)
        throw std::invalid_argument(errorMessage);
    size_t end = str.find_last_not_of(' ');
    return str.substr(start, end - start + 1);
}

/**
 * @brief Разбор строки в натуральное число.
 * @param input строка, содержащая число
 * @return Объект класса Natural
 *
 * Проверяет, что строка состоит только из цифр.
 * Удаляет ведущие нули и создаёт объект Natural.
 * В случае пустой строки или недопустимых символов выбрасывает исключение.
*/
Natural Parser::parseNatural(const std::string& input) {
    std::string s = trimAndValidate(input, "Пустой ввод");

    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            throw std::invalid_argument("Число должно состоять только из цифр");
    }

    size_t nonZero = s.find_first_not_of('0');
    if (nonZero == std::string::npos)
        s = "0";
    else
        s = s.substr(nonZero);

    return Natural(s);
}

/**
 * @brief Разбор строки в целое число.
 * @param input строка, содержащая число (с возможным знаком)
 * @return Объект класса Integer
 *
 * Поддерживает знаки '+' и '-'. Проверяет корректность формата числа.
 * Убирает ведущие нули и создаёт объект Integer с соответствующим знаком.
*/
Integer Parser::parseInteger(const std::string& input) {
    std::string s = trimAndValidate(input, "Пустой ввод");

    int sign = 0;
    if (s[0] == '-' || s[0] == '+') {
        sign = (s[0] == '-') ? 1 : 0;
        s.erase(0, 1);
        s = trimAndValidate(s, "Отсутствует числовая часть после знака");
    }

    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            throw std::invalid_argument("Число должно состоять только из цифр");
    }

    size_t nz = s.find_first_not_of('0');
    if (nz == std::string::npos)
        s = "0";
    else
        s = s.substr(nz);
    
    Natural absValue(s);
    return Integer(absValue, sign);
}

/**
 * @brief Разбор строки в рациональное число.
 * @param input строка в формате "a/b" или просто "a"
 * @return Объект класса Rational
 *
 * Поддерживает как целые, так и дробные формы.
 * Проверяет корректность числителя и знаменателя.
 * При ошибке выбрасывает исключение с пояснением.
*/
Rational Parser::parseRational(const std::string& input) {
    try {
        std::string s = trimAndValidate(input, "Пустой ввод");
        size_t slashPos = s.find('/');

        if (slashPos == std::string::npos) {
            Integer num = parseInteger(s);
            Natural den("1");
            return Rational(num, den);
        }

        std::string numStr = s.substr(0, slashPos);
        std::string denStr = s.substr(slashPos + 1);

        numStr = trimAndValidate(numStr, "Отсутствует числитель");
        denStr = trimAndValidate(denStr, "Отсутствует знаменатель");

        Integer numerator = parseInteger(numStr);
        Natural denominator = parseNatural(denStr);

        return Rational(numerator, denominator);
    }
    catch (const std::invalid_argument& e) {
        throw std::runtime_error(e.what());
    }
    catch (const std::exception& e) {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief Разбор строки в многочлен.
 * @param input строка, представляющая многочлен
 * @return Объект класса Polynomial
 *
 * Удаляет пробелы, добавляет знак '+' при необходимости.
 * Использует регулярные выражения для выделения членов вида:
 *   ±(число или дробь)x^степень
 * Поддерживает сложение коэффициентов при одинаковых степенях.
 * При некорректном формате выбрасывает исключение.
*/
Polynomial Parser::parsePolynomial(const std::string& input) {
    std::string s = input;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    if (s.empty())
        throw std::invalid_argument("Пустой ввод");

    if (s[0] != '+' && s[0] != '-')
        s = "+" + s;

    std::map<Natural, Rational> terms;

    std::regex termRegex(R"(([+-])(\d*(?:/\d+)?)?(x(?:\^(\d+))?)?)");
    std::smatch match;
    auto it = s.cbegin();

    auto parseNat = [&](const std::string& str) -> int {
        if (str.empty())
            return 1; 
        int v = 0;
        for (char c : str) {
            if (!isdigit(c))
                throw std::invalid_argument("Некорректная степень: " + str);
            v = v * 10 + (c - '0');
        }
        return v;
    };

    while (std::regex_search(it, s.cend(), match, termRegex)) {
        std::string signStr = match[1];  // "+" или "-"
        std::string coeffStr = match[2]; // числитель/дробь
        std::string xPart    = match[3]; // x или x^k
        std::string expStr   = match[4]; // k

        if (coeffStr.empty() && xPart.empty() && match[0].length() <= 1) {
            it = match.suffix().first;
            continue;
        }

        bool negative = (signStr == "-");

        Rational coeff;
        if (coeffStr.empty()) {
            coeff = Rational(Integer("1"), Natural("1"));
        } else {
            coeff = parseRational(coeffStr);
        }

        if (negative) {
            std::string negStr = "-" + coeff.getNumerator().toString();
            Integer negNum = parseInteger(negStr);
            coeff = Rational(negNum, coeff.getDenominator());
        }

        int exp = 0;
        if (!xPart.empty()) {
            exp = parseNat(expStr);
        }
        Natural expNat(std::to_string(exp));

        if (terms.find(expNat) != terms.end()) {
            terms[expNat] = terms[expNat] + coeff;
        } else {
            terms.emplace(expNat, coeff);
        }

        it = match.suffix().first;
    }

    if (terms.empty())
        throw std::invalid_argument("Не найдено ни одного корректного члена многочлена");

    return Polynomial(terms);
}

std::pair<std::string, int> Parser::TRANS_PQ_STRNN_STR(
    std::string numStrInput,
    Natural* baseP) const
{
    if (baseP == nullptr)
        throw std::invalid_argument("Указатель на основание системы счисления равен nullptr");

    std::string numStr = trimAndValidate(numStrInput, "Пустой ввод для числа");

    int signInt = 0;

    if (numStr[0] == '+' || numStr[0] == '-')
    {
        signInt = (numStr[0] == '-') ? 1 : 0;
        numStr.erase(0, 1);
        numStr = trimAndValidate(numStr, "Отсутствует числовая часть после знака");
    }

    std::transform(numStr.begin(), numStr.end(), numStr.begin(),
                   [](unsigned char c){ return std::toupper(c); });

    for (char c : numStr)
    {
        int value = charToDigitValue(c);
        if (value < 0)
            throw std::invalid_argument(std::string("Недопустимый символ в числе: ") + c);

        Natural digit(std::to_string(value));
        if (digit >= *baseP)
            throw std::invalid_argument("Цифра не принадлежит системе счисления");
    }

    return {numStr, signInt}; //Строка и int(знак 0 или 1(отр))
}

/**
 * @brief Преобразует символ в его числовое значение в зависимости от системы счисления.
 * @param c символ, который нужно интерпретировать как цифру (0–9, A–Z, a–z)
 * @return Целое значение, соответствующее символу: 
 *         0–9 для цифр, 10–35 для латинских букв (без учета регистра).
 *         Если символ не является допустимым — возвращает -1.
 *
 * Используется при разборе чисел в произвольной системе счисления.
 * Например, 'A' или 'a' → 10, 'F' → 15, '9' → 9.
 */
int Parser::charToDigitValue(char c) const
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'A' && c <= 'Z')
        return 10 + (c - 'A');
    if (c >= 'a' && c <= 'z')
        return 10 + (c - 'a');
    return -1;
}

/**
 * @brief Разбирает строку числа в указанной системе счисления.
 * @param numStrInput строка, содержащая представление числа (может иметь знак '+' или '-')
 * @param baseP указатель на объект класса Natural, задающий основание системы счисления
 * @return Пара, состоящая из:
 *         - очищенной и приведённой к верхнему регистру строки числа (без знака);
 *         - целого признака знака (0 — положительное, 1 — отрицательное).
 *
 * Пример:
 *   base = 16, numStrInput = "-1F" → вернёт {"1F", 1}.
 */
std::pair<std::string, int> Parser::parseBaseNumber(
    std::string numStrInput,
    Natural* baseP) const
{
    if (baseP == nullptr)
        throw std::invalid_argument("Указатель на основание системы счисления равен nullptr");

    std::string numStr = trimAndValidate(numStrInput, "Пустой ввод для числа");

    int signInt = 0;

    if (numStr[0] == '+' || numStr[0] == '-')
    {
        signInt = (numStr[0] == '-') ? 1 : 0;
        numStr.erase(0, 1);
        numStr = trimAndValidate(numStr, "Отсутствует числовая часть после знака");
    }

    std::transform(numStr.begin(), numStr.end(), numStr.begin(),
                   [](unsigned char c){ return std::toupper(c); });

    for (char c : numStr)
    {
        int value = charToDigitValue(c);
        if (value < 0)
            throw std::invalid_argument(std::string("Недопустимый символ в числе: ") + c);

        Natural digit(std::to_string(value));
        if (digit >= *baseP)
            throw std::invalid_argument("Цифра не принадлежит системе счисления");
    }

    return {numStr, signInt}; 
}

/**
 * @brief Преобразует объект Natural в строку.
 * @param value объект класса Natural
 * @return Строковое представление натурального числа
*/
std::string Parser::toString(const Natural& value) const {
    return value.toString();
}

/**
 * @brief Преобразует объект Integer в строку.
 * @param value объект класса Integer
 * @return Строковое представление целого числа
*/
std::string Parser::toString(const Integer& value) const {
    return value.toString();
}

/**
 * @brief Преобразует объект Rational в строку.
 * @param value объект класса Rational
 * @return Строковое представление рационального числа
*/
std::string Parser::toString(const Rational& value) const {
    return value.toString();
}

/**
 * @brief Преобразует объект Polynomial в строку.
 * @param value объект класса Polynomial
 * @return Строковое представление многочлена
*/
std::string Parser::toString(const Polynomial& value) const {
    return value.toString();
}
