#ifndef RATIONAL_H
#define RATIONAL_H

#include "integer.h"

class Rational {
private:
    Integer m_numerator;    // числитель
    Natural m_denominator;  // знаменатель

public:
    // Конструкторы
    Rational();
    Rational(const Integer& num, const Natural& den);

    Rational RED_Q_Q() const;                      // Сокращение дроби
    bool INT_Q_B() const;                          // Проверка на целое
    Integer TRANS_Q_Z() const;                     // Дробное в целое (если знам. = 1)
    Rational TRANS_Z_Q(const Integer& integer); // Целое в дробное

    Rational ADD_QQ_Q(const Rational& other) const; // Сложение
    Rational SUB_QQ_Q(const Rational& other) const; // Вычитание
    Rational MUL_QQ_Q(const Rational& other) const; // Умножение
    Rational DIV_QQ_Q(const Rational& other) const; // Деление

    bool isZero() const; //?
    bool isInteger() const; //?

    Integer getNumerator() const { return m_numerator; } //??
    Natural getDenominator() const { return m_denominator; } //??

private:
    void reduceFraction(); // Сокращение дроби (НОД)
};

#endif // RATIONAL_H
