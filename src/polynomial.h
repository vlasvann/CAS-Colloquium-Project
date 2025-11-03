#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "rational.h"
#include <vector>

class Polynomial {
private:
    int m_degree;
    std::vector<Rational> m_coefficients;

public:
    Polynomial();
    Polynomial(const std::vector<Rational>& coeffs);
    Polynomial(const std::vector<Integer>& coeffs);

    Polynomial ADD_PP_P(const Polynomial& other) const; // Сложение
    Polynomial SUB_PP_P(const Polynomial& other) const; // Вычитание
    Polynomial MUL_PQ_P(const Rational& number) const; // Умножение на рациональное число
    Polynomial MUL_Pxk_P(int k) const; // Умножение на x^k

    Rational LED_P_Q() const; // Старший коэффициент
    Natural DEG_P_N() const; // Степень многочлена

    Rational FAC_P_Q() const; // НОК знаменателей и НОД числителей
    Polynomial MUL_PP_P(const Polynomial& other) const; // Умножение многочленов
    Polynomial DIV_PP_P(const Polynomial& divisor) const; // Частное от деления
    Polynomial MOD_PP_P(const Polynomial& divisor) const; // Остаток от деления
    Polynomial GCF_PP_P(const Polynomial& other) const; // НОД многочленов
    Polynomial DER_P_P() const; // Производная
    Polynomial NMR_P_P() const; // Преобразование кратных корней в простые

    bool isZero() const; //?
    Rational evaluate(const Rational& x) const; // ?

    int getDegree() const { return m_degree; } //?
    const std::vector<Rational>& getCoefficients() const { return m_coefficients; } //?
    Rational getCoefficient(int index) const; //?
};

#endif // POLYNOMIAL_H
