#ifndef INTEGER_H
#define INTEGER_H

#include "natural.h"

class Integer {
private:
    Natural m_absolute;
    int m_sign;

public:
    Integer();
    Integer(const Natural& nat);                    // из натурального (положительное)
    Integer(const Natural& abs, int sgn);          // из абсолютной величины и знака
    Integer(const std::string&);            // из строки

    Integer ABS_Z_Z() const;                       // Абсолютная величина
    int POZ_Z_D() const;                           // Знак: -1, 0, 1
    Integer MUL_ZM_Z() const;                      // Умножение на (-1)

    Natural TRANS_Z_N() const;                     // Целое неотрицательное в натуральное
    Integer TRANS_N_Z(const Natural& nat);         // Натуральное в целое

    Integer ADD_ZZ_Z(const Integer& other) const;  // Сложение
    Integer SUB_ZZ_Z(const Integer& other) const;  // Вычитание
    Integer MUL_ZZ_Z(const Integer& other) const;  // Умножение
    Integer DIV_ZZ_Z(const Integer& divisor) const; // Частное от деления
    Integer MOD_ZZ_Z(const Integer& divisor) const; // Остаток от деления

    std::string toString() const; //??
    bool isZero() const { return m_sign == 0; } //??
    bool isPositive() const { return m_sign > 0; } //?
    bool isNegative() const { return m_sign < 0; } //?

    Natural getAbsolute() const { return m_absolute; } //??
    int getSign() const { return m_sign; } //?
};

#endif // INTEGER_H
