#include "polynomial.h"

Polynomial::Polynomial() : m_degree(0) {}

Polynomial::Polynomial(const std::vector<Rational>& coeffs) 
    : m_degree(coeffs.empty() ? 0 : coeffs.size() - 1),
      m_coefficients(coeffs) {
}

Polynomial::Polynomial(const std::vector<Integer>& coeffs) : m_degree(coeffs.empty() ? 0 : coeffs.size() - 1) {
    // временная заглушка
}

Polynomial Polynomial::ADD_PP_P(const Polynomial&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::SUB_PP_P(const Polynomial&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::MUL_PQ_P(const Rational&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::MUL_Pxk_P(int) const {
    return Polynomial(); // временная заглушка
}

Rational Polynomial::LED_P_Q() const {
    return Rational(); // временная заглушка
}

Natural Polynomial::DEG_P_N() const {
    return Natural(); // временная заглушка
}

Rational Polynomial::FAC_P_Q() const {
    return Rational(); // временная заглушка
}

Polynomial Polynomial::MUL_PP_P(const Polynomial&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::DIV_PP_P(const Polynomial&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::MOD_PP_P(const Polynomial&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::GCF_PP_P(const Polynomial&) const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::DER_P_P() const {
    return Polynomial(); // временная заглушка
}

Polynomial Polynomial::NMR_P_P() const {
    return Polynomial(); // временная заглушка
}

bool Polynomial::isZero() const {
    return false; // временная заглушка
}

Rational Polynomial::evaluate(const Rational&) const {
    return Rational(); // временная заглушка
}

Rational Polynomial::getCoefficient(int) const {
    return Rational(); // временная заглушка
}

