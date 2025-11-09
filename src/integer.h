#ifndef INTEGER_H
#define INTEGER_H

#include "natural.h"
#include <stdexcept>
#include <string>

/**
 * Developed by Buraya Vera and Pisarenko Aleksandra group 4382
 * @class Integer
 * @brief Класс целых чисел
 *
 * Представляет целые числа со знаком и абсолютным значением.
 * Поддерживает основные арифметические операции и преобразования между типами.
 */
class Integer {
private:
    Natural m_absolute;  ///< Абсолютное значение целого числа
    int m_sign;          ///< Знак целого числа (0 - положительное, 1 - отрицательное)

public:
    Integer(); ///< Конструктор по умолчанию
    Integer(const Natural& nat); ///< Конструктор из натурального числа
    Integer(const Natural& abs, int sgn); ///< Конструктор с явным указанием знака
    Integer(const std::string& str); ///< Конструктор из строкового представления

    Natural ABS_Z_N() const; ///< Получение абсолютного значения
    int POZ_Z_D() const; ///< Определение знака числа
    Integer MUL_ZM_Z() const; ///< Умножение числа на -1
    Integer TRANS_N_Z(const Natural& natural); ///< Преобразование натурального числа в целое
    Natural TRANS_Z_N() const; ///< Преобразование целого числа в натуральное
    Integer ADD_ZZ_Z(const Integer& other) const; ///< Сложение двух целых чисел
    Integer SUB_ZZ_Z(const Integer& other) const; ///< Вычитание целых чисел
    Integer MUL_ZZ_Z(const Integer& other) const; ///< Умножение целых чисел
    Integer DIV_ZZ_Z(const Integer& divisor) const; ///< Целочисленное деление
    Integer MOD_ZZ_Z(const Integer& divisor) const; ///< Остаток от деления
    std::string toString() const; ///< Строковое представление числа

    int getSign() const { return m_sign; } ///< Получение знака числа

    Integer operator+(const Integer& other) const { return ADD_ZZ_Z(other); } ///< Оператор сложения для целых чисел
    Integer operator-(const Integer& other) const { return SUB_ZZ_Z(other); } ///< Оператор вычитания для целых чисел
    Integer operator*(const Integer& other) const { return MUL_ZZ_Z(other); } ///< Оператор умножения для целых чисел
    Integer operator/(const Integer& other) const { return DIV_ZZ_Z(other); } ///< Оператор деления для целых чисел
    Integer operator%(const Integer& other) const { return MOD_ZZ_Z(other); } ///< Оператор взятия остатка для целых чисел

    bool operator>(const Integer& other) const { return (this->SUB_ZZ_Z(other)).POZ_Z_D() == 1; } ///< Оператор больше для целых чисел
    bool operator<(const Integer& other) const { return (this->SUB_ZZ_Z(other)).POZ_Z_D() == -1; } ///< Оператор меньше для целых чисел
    bool operator>=(const Integer& other) const { return (this->SUB_ZZ_Z(other)).POZ_Z_D() >= 0; } ///< Оператор больше или равно для целых чисел
    bool operator<=(const Integer& other) const { return (this->SUB_ZZ_Z(other)).POZ_Z_D() <= 0; } ///< Оператор меньше или равно для целых чисел
    bool operator==(const Integer& other) const { return (this->SUB_ZZ_Z(other)).POZ_Z_D() == 0; } ///< Оператор равенства для целых чисел
    bool operator!=(const Integer& other) const { return (this->SUB_ZZ_Z(other)).POZ_Z_D() != 0; } ///< Оператор неравенства для целых чисел
};

#endif // INTEGER_H
