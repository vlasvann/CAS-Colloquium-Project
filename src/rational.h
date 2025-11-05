#ifndef RATIONAL_H
#define RATIONAL_H

#include "integer.h"

/**
 * Developed by Smirnov Aleksandr Dmitrievich group 4382
 * and Vyaznikov Nikita 4382
 * @class Rational
 * @brief Класс рациональных чисел
 *
 * Предоставляет  для ввода операндов в зависимости от выбранного
 * типа данных и математической операции.
 */
class Rational {
private:
    Integer m_numerator; ///< числитель рационального числа
    Natural m_denominator; ///< знаменатель рационального числа

public:
    Rational(); ///< Конструктор класса по умолчанию
    Rational(const Integer& num, const Natural& den); ///< Параметризированный конструктор класса
    Rational(const std::string& number); ///< Конструктор класса по строке

    Rational RED_Q_Q() const; ///< Сокращение дроби
    bool INT_Q_B() const; ///< Проверка на целое
    Integer TRANS_Q_Z() const; ///< Перевод рационального числа в целое (если знам. = 1)
    static Rational TRANS_Z_Q(const Integer& integer); ///< Перевод целого числа в рациональное

    Rational ADD_QQ_Q(const Rational& other) const; ///< Сумма рациональных чисел
    Rational SUB_QQ_Q(const Rational& other) const; ///< Разность рациональных чисел
    Rational MUL_QQ_Q(const Rational& other) const; ///< Произведение рациональных чисел
    Rational DIV_QQ_Q(const Rational& other) const; ///< Деление рациональных чисел

    std::string toString() const; ///< Перевод рационального числа в строку
    bool isZero() const; ///< Проверка на равенство нулю

    Integer getNumerator() const { return m_numerator; } ///< Получение числителя рационального числа
    Natural getDenominator() const { return m_denominator; } ///< Получение знаменателя рационального числа

    Rational operator+(const Rational& other) const { return ADD_QQ_Q(other); } ///< Оператор суммы для рациональных чисел
    Rational operator-(const Rational& other) const { return SUB_QQ_Q(other); } ///< Оператор разности для рациональных чисел
    Rational operator*(const Rational& other) const { return MUL_QQ_Q(other); } ///< Оператор произведения для рациональных чисел
    Rational operator/(const Rational& other) const { return DIV_QQ_Q(other); } ///< Оператор деления для рациональных чисел

};

#endif // RATIONAL_H
