#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "rational.h"
#include <map>
#include <algorithm>
#include <stdexcept>

/**
 * Developed by Smirnov Nikolay 4382,
 * Sozinov Denis 4382,
 * Isaev Andrei 4382
 * @class Polynomial
 * @brief Класс полиномов (многочленов)
 *
 * Предоставляет интерфейс полиномов
 * с соответствующими методами (операциями над полиномами)
 */

class Polynomial {
private:
    Natural m_degree; // старшая степень полинома
    std::map<Natural, Rational> m_value; // мономы в составе полинома
public:
    //Конструкторы (по умолчанию, с рациональными коэф., с целыми коэф.)
    Polynomial();
    Polynomial(const std::map<Natural, Rational>&);
    Polynomial(const std::map<Natural, Integer>&);

    Polynomial ADD_PP_P(const Polynomial&) const; // Сложение
    Polynomial SUB_PP_P(const Polynomial&) const; // Вычитание
    Polynomial MUL_PQ_P(const Rational&) const; // Умножение на рациональное число
    Polynomial MUL_Pxk_P(const Natural&) const; // Умножение на x^k

    Rational LED_P_Q() const; // Старший коэффициент
    Natural DEG_P_N() const; // Степень многочлена

    Rational FAC_P_Q() const; // НОК знаменателей и НОД числителей
    Polynomial MUL_PP_P(const Polynomial&) const; // Умножение многочленов
    Polynomial DIV_PP_P(const Polynomial&) const; // Частное от деления
    Polynomial MOD_PP_P(const Polynomial&) const; // Остаток от деления
    Polynomial GCF_PP_P(const Polynomial&) const; // НОД многочленов
    Polynomial DER_P_P() const; // Производная
    Polynomial NMR_P_P() const; // Преобразование кратных корней в простые
    std::string toString() const; // Представления полинома в строку

    bool isZero() const; // проверка на то, является ли данный многочлен нулевым
    const std::map<Natural, Rational>& getValue() const { return m_value; } //Получение пар мономов полинома

    Polynomial operator+(const Polynomial& other) const; //Оператор сложения для полиномов
    Polynomial operator-(const Polynomial& other) const; //Оператор вычитания для полиномов
    Polynomial operator*(const Polynomial& other) const; //Оператор умножения для полиномов
    Polynomial operator/(const Polynomial& other) const; //Оператор деления для полиномов
    Polynomial operator%(const Polynomial& other) const; //Оператор взятия остатка при делении полиномов
};

#endif // POLYNOMIAL_H
