#include "natural.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

/*
 * Developed by Gozhchenko Vasilina and Deikina Angelina group 4382
 * Natural - реализация класса натуральных чисел
 * Формат: младший разряд первый (1234 = [4,3,2,1])
 */

/**
 * @brief Конструктор по умолчанию. Создает число 0.
 */
Natural::Natural() : m_digits({0}) {}

/**
 * @brief Конструктор из строки.
 * @param number строка, содержащая натуральное число
 */
Natural::Natural(const std::string& number) { 
    for (int i = number.size() - 1; i >= 0; i--) {
        m_digits.push_back(number[i] - '0');
    }
}

/**
 * @brief Конструктор из целого числа.
 * @param number целое неотрицательное число
 * @throw std::invalid_argument если число отрицательное
 */
Natural::Natural(int number) {
    if (number < 0) {
        throw std::invalid_argument("Натуральное число не может быть отрицательным");
    }
    
    if (number == 0) {
        m_digits = {0};
        return;
    }
    
    // Преобразуем число в цифры (младший разряд первый)
    while (number > 0) {
        m_digits.push_back(number % 10);
        number /= 10;
    }
}

/**
 * @brief Конструктор из вектора цифр.
 * @param digits вектор цифр в формате младший разряд первый
 */
Natural::Natural(const std::vector<int>& digits) : m_digits(digits) {}

/**
 * @brief Сравнение натуральных чисел.
 * @param other второе натуральное число для сравнения
 * @return 1 - если первое больше второго, 0 - если равно, -1 - если меньше
 */
int Natural::COM_NN_D(const Natural& other) const { 
    if (m_digits.size() > other.m_digits.size()) return 1;    
    if (m_digits.size() < other.m_digits.size()) return -1;   
     
    for (int i = m_digits.size() - 1; i >= 0; i--) {
        if (m_digits[i] > other.m_digits[i]) return 1;       
        if (m_digits[i] < other.m_digits[i]) return -1;       
    }
    
    return 0; 
}

/**
 * @brief Проверка на ноль.
 * @return true - если число не равно нулю, false - если равно нулю
 */
bool Natural::NZER_N_B() const { 
    return !(m_digits.size() == 1 && m_digits[0] == 0);
}

/**
 * @brief Добавление 1 к натуральному числу.
 * @return результат сложения числа с 1
 */
Natural Natural::ADD_1N_N() const { 
    std::vector<int> result = m_digits;
    int carry = 1; 
    for (size_t i = 0; i < result.size() && carry > 0; i++) {
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    } 
    if (carry > 0) {
        result.push_back(carry);
    }
    
    return Natural(result);
}

/**
 * @brief Сложение натуральных чисел.
 * @param other второе слагаемое
 * @return сумма двух натуральных чисел
 */
Natural Natural::ADD_NN_N(const Natural& other) const {
    std::vector<int> result;
    int carry = 0;
    size_t max_len = std::max(m_digits.size(), other.m_digits.size());
    
    for (size_t i = 0; i < max_len || carry > 0; i++) {
        int digit1 = (i < m_digits.size()) ? m_digits[i] : 0;
        int digit2 = (i < other.m_digits.size()) ? other.m_digits[i] : 0;
        
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_back(sum % 10);
    }
    
    return Natural(result);
}

/**
 * @brief Вычитание натуральных чисел.
 * @param other вычитаемое
 * @return разность чисел (this - other)
 * @throw std::invalid_argument если результат отрицательный
 */
Natural Natural::SUB_NN_N(const Natural& other) const {
    if (this->COM_NN_D(other) == -1) {
        throw std::invalid_argument("Первое число должно быть больше или равно второму");
    }
    if (this->COM_NN_D(other) == 0) {
        return Natural("0");
    }
    
    std::vector<int> result;
    int borrow = 0;
    
    for (size_t i = 0; i < m_digits.size(); i++) {
        int digit1 = m_digits[i] - borrow;
        int digit2 = (i < other.m_digits.size()) ? other.m_digits[i] : 0;
        
        if (digit1 < digit2) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.push_back(digit1 - digit2);
    }
    
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    
    return Natural(result);
}

/**
 * @brief Умножение натурального числа на цифру.
 * @param digit цифра для умножения (0-9)
 * @return произведение числа на цифру
 * @throw std::invalid_argument если digit не в диапазоне 0-9
 */
Natural Natural::MUL_ND_N(int digit) const { 
    if (digit < 0 || digit > 9) {
        throw std::invalid_argument("Цифра должна быть в диапазоне от 0 до 9");
    }
    
    if (digit == 0 || !NZER_N_B()) {
        return Natural("0");
    }
    
    std::vector<int> result;
    int carry = 0;
    
    for (size_t i = 0; i < m_digits.size(); i++) {
        int product = m_digits[i] * digit + carry;
        carry = product / 10;
        result.push_back(product % 10);
    }
    
    if (carry > 0) {
        result.push_back(carry);
    }
    
    return Natural(result);
}

/**
 * @brief Умножение натурального числа на 10^k.
 * @param k показатель степени
 * @return число, умноженное на 10^k
 * @throw std::invalid_argument если k отрицательное
 */
Natural Natural::MUL_Nk_N(int k) const { 
    if (k < 0) {
        throw std::invalid_argument("k должно быть неотрицательным");
    }
    
    if (k == 0 || !NZER_N_B()) {
        return *this;
    }
    
    std::vector<int> result = m_digits; 
    result.insert(result.begin(), k, 0);
    
    return Natural(result);
}

/**
 * @brief Умножение натуральных чисел.
 * @param other второй множитель
 * @return произведение двух натуральных чисел
 */
Natural Natural::MUL_NN_N(const Natural& other) const { 
    if (!NZER_N_B() || !other.NZER_N_B()) {
        return Natural("0");
    }
    
    Natural result("0");
    
    for (size_t i = 0; i < other.m_digits.size(); i++) {
        Natural partial = this->MUL_ND_N(other.m_digits[i]);
        partial = partial.MUL_Nk_N(i); 
        result = result.ADD_NN_N(partial);
    }
    
    return result;
}

/**
 * @brief Вычитание произведения числа на цифру.
 * @param other число для умножения
 * @param digit цифра для умножения
 * @return разность this - (other * digit)
 * @throw std::invalid_argument если результат отрицательный
 */
Natural Natural::SUB_NDN_N(const Natural& other, int digit) const { 
    Natural other_times_digit = other.MUL_ND_N(digit);
    
    if (this->COM_NN_D(other_times_digit) == -1) {
        throw std::invalid_argument("Результат получится отрицательным");
    }
    
    return this->SUB_NN_N(other_times_digit);
}

/**
 * @brief Вычисление первой цифры деления с позицией.
 * @param divisor делитель
 * @return пара (цифра, позиция) для первой цифры частного
 */
std::pair<int, int> Natural::DIV_NN_Dk(const Natural& divisor) const { 
    if (this->COM_NN_D(divisor) == -1) {
        return {0, 0};
    } 

    int k = m_digits.size() - divisor.m_digits.size();
    
    for (int current_k = k; current_k >= 0; current_k--) {
        for (int d = 9; d >= 1; d--) {
            Natural candidate = divisor.MUL_ND_N(d).MUL_Nk_N(current_k);
            if (this->COM_NN_D(candidate) != -1) {
                return {d, current_k};
            }
        }
    }

    return {0, 0};
}

/**
 * @brief Неполное частное от деления.
 * @param divisor делитель
 * @return неполное частное
 * @throw std::invalid_argument если делитель равен нулю
 */
Natural Natural::DIV_NN_N(const Natural& divisor) const {
    if (!divisor.NZER_N_B()) {
        throw std::invalid_argument("Деление на ноль");
    }
    
    Natural quotient("0");
    Natural remainder = *this;
    
    while (remainder.COM_NN_D(divisor) != -1) {
        std::pair<int, int> digit_k = remainder.DIV_NN_Dk(divisor);
        int digit = digit_k.first;
        int k = digit_k.second;
        
        if (digit == 0) break;
        
        Natural subtractor = divisor.MUL_ND_N(digit).MUL_Nk_N(k);
        Natural digit_value = Natural(std::to_string(digit)).MUL_Nk_N(k);
        quotient = quotient.ADD_NN_N(digit_value);
        remainder = remainder.SUB_NN_N(subtractor);
    }
    
    return quotient;
}

/**
 * @brief Остаток от деления.
 * @param divisor делитель
 * @return остаток от деления
 * @throw std::invalid_argument если делитель равен нулю
 */
Natural Natural::MOD_NN_N(const Natural& divisor) const { 
    if (!divisor.NZER_N_B()) {
        throw std::invalid_argument("Деление на ноль");
    }
    
    if (this->COM_NN_D(divisor) == -1) {
        return *this;
    }
    
    if (this->COM_NN_D(divisor) == 0) {
        return Natural("0");
    }
    
    Natural quotient = this->DIV_NN_N(divisor);
    Natural product = quotient.MUL_NN_N(divisor);
    return this->SUB_NN_N(product);
}

/**
 * @brief Наибольший общий делитель.
 * @param other второе число
 * @return НОД двух чисел
 */
Natural Natural::GCF_NN_N(const Natural& other) const { 
    if (!this->NZER_N_B()) return other;
    if (!other.NZER_N_B()) return *this;
    
    Natural a = *this;
    Natural b = other;
    
    while (b.NZER_N_B()) {
        Natural r = a.MOD_NN_N(b);
        a = b;
        b = r;
    }
    
    return a;
}

/**
 * @brief Наименьшее общее кратное.
 * @param other второе число
 * @return НОК двух чисел
 */
Natural Natural::LCM_NN_N(const Natural& other) const { 
    if (!this->NZER_N_B() || !other.NZER_N_B()) {
        return Natural("0");
    }
    
    Natural gcd = this->GCF_NN_N(other);
    Natural product = this->MUL_NN_N(other);
    return product.DIV_NN_N(gcd);
}

/**
 * @brief Преобразование числа в строку.
 * @return строковое представление числа
 */
std::string Natural::toString() const {
    std::string result; 
    for (int i = m_digits.size() - 1; i >= 0; i--) {
        result += std::to_string(m_digits[i]);
    }
    return result;
}
