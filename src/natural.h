#ifndef NATURAL_H
#define NATURAL_H

#include <vector>
#include <string>

class Natural {
private:
    std::vector<int> m_digits;

public:
    Natural();
    Natural(const std::string& number);
    Natural(const std::vector<int>& digits);

    int COM_NN_D(const Natural& other) const; //сравнение
    bool NZER_N_B() const; //проверка на ноль

    Natural ADD_1N_N() const; // Добавление 1
    Natural ADD_NN_N(const Natural& other) const; // Сложение
    Natural SUB_NN_N(const Natural& other) const; // Вычитание (this >= other)
    Natural MUL_ND_N(int digit) const; // Умножение на цифру
    Natural MUL_Nk_N(int k) const; // Умножение на 10^k
    Natural MUL_NN_N(const Natural& other) const; // Умножение
    Natural SUB_NDN_N(const Natural& other, int digit) const; // Вычитание other * digit
    std::pair<int, int> DIV_NN_Dk(const Natural& divisor) const; // Первая цифра деления с позицией
    Natural DIV_NN_N(const Natural& divisor) const; // Неполное частное
    Natural MOD_NN_N(const Natural& divisor) const; // Остаток от деления

    Natural GCF_NN_N(const Natural& other) const; // НОД
    Natural LCM_NN_N(const Natural& other) const; // НОК
};

#endif // NATURAL_H
