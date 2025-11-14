#ifndef EXTRAMETHODS_H
#define EXTRAMETHODS_H

#include "integer.h"

/**
 * Developed by Gamaga Georgii group 4383
 * @class ExtraMethods
 * @brief Дополнительные методы и алгоритмы для работы с числами
 *
 * Предоставляет дополнительные математические операции и преобразования
 * для работы с целыми и натуральными числами.
 */
class ExtraMethods
{
private:
    std::vector<Natural> GETDIGITS_NN_VECN(const Natural& num, const Natural& base) const; ///< Получение цифр числа в системе счисления
    Natural TRANS_PDEC_STRN_N(const std::string& num, const Natural& base) const; ///< Преобразование строки в число в системе счисления

public:
    Integer TRANS_BIN_ZN_Z(const Integer& num, const Natural& bitLength) const; ///< Преобразование в двоичное представление

    Integer TRANS_DECFAC_Z_Z(const Integer& num) const; ///< Преобразование в факториальное представление
    Integer TRANS_FACDEC_Z_Z(const Integer& num) const; ///< Преобразование из факториальной системы

    bool FINDOUT_LUCKYNUMBER_N_B(const Natural& num) const; ///< Проверка на счастливое число

    Integer EXP_ZN_Z(const Integer& num, const Natural& exp) const; ///< Возведение в степень

    std::string TRANS_PQ_STRNN_STR(const std::pair<std::string, int> num, const Natural& baseP, const Natural& baseQ) const; ///< Преобразование между системами счисления
};
#endif