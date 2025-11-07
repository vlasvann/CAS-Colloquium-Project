#include "integer.h"

Integer::Integer() : m_sign(0) {}

Integer::Integer(const Natural& nat) : m_absolute(nat), m_sign(1) {}

Integer::Integer(const Natural& abs, int sgn) : m_absolute(abs), m_sign(sgn) {}

Integer::Integer(const std::string&) : m_sign(0) {}

Natural Integer::ABS_Z_N() const {
    return Natural(); // временная заглушка
}

int Integer::POZ_Z_D() const {
    return 0; // временная заглушка
}

Integer Integer::MUL_ZM_Z() const {
    return Integer(); // временная заглушка
}

Natural Integer::TRANS_Z_N() const {
    return Natural(); // временная заглушка
}

Integer Integer::TRANS_N_Z(const Natural&) {
    return Integer(); // временная заглушка
}

Integer Integer::ADD_ZZ_Z(const Integer&) const {
    return Integer(); // временная заглушка
}

Integer Integer::SUB_ZZ_Z(const Integer&) const {
    return Integer(); // временная заглушка
}

Integer Integer::MUL_ZZ_Z(const Integer&) const {
    return Integer(); // временная заглушка
}

Integer Integer::DIV_ZZ_Z(const Integer&) const {
    return Integer(); // временная заглушка
}

Integer Integer::MOD_ZZ_Z(const Integer&) const {
    return Integer(); // временная заглушка
}

