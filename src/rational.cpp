#include "rational.h"

Rational::Rational() {}

Rational::Rational(const Integer& num, const Natural& den) : m_numerator(num), m_denominator(den) {}

Rational Rational::RED_Q_Q() const {
    return Rational(); // временная заглушка
}

bool Rational::INT_Q_B() const {
    return false; // временная заглушка
}

Integer Rational::TRANS_Q_Z() const {
    return Integer(); // временная заглушка
}

Rational Rational::TRANS_Z_Q(const Integer&) {
    return Rational(); // временная заглушка
}

Rational Rational::ADD_QQ_Q(const Rational&) const {
    return Rational(); // временная заглушка
}

Rational Rational::SUB_QQ_Q(const Rational&) const {
    return Rational(); // временная заглушка
}

Rational Rational::MUL_QQ_Q(const Rational&) const {
    return Rational(); // временная заглушка
}

Rational Rational::DIV_QQ_Q(const Rational&) const {
    return Rational(); // временная заглушка
}

bool Rational::isZero() const { 
    return false; 
}

bool Rational::isInteger() const { 
    return false; 
}

void Rational::reduceFraction() {
    // временная заглушка
}
