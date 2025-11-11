#include "extraMethods.h"

/**
     * @brief Разбивает число на вектор цифр в заданной системе счисления.
     *
     * Представляет число в виде последовательности цифр в СС с основанием base.
     * Наиболее младшая цифра располагается в конце вектора.
     *
     * @param num Число, подлежащее разложению на цифры.
     * @param base Основание СС (>= 2).
     * @throws std::invalid_argument Если base < 2.
     * @return Вектор цифр числа num в системе счисления с основанием base.
     */
std::vector<Natural> ExtraMethods::GETDIGITS_NN_VECN(const Natural& num, const Natural& base) const
{
    if (base < Natural("2"))
        throw std::invalid_argument("Неверное основание: base должен быть больше 1.");

    std::vector<Natural> digits;
    if (!num.NZER_N_B())
    {
        digits.push_back(Natural("0"));
        return digits;
    }

    Natural number = num;
    while (number.NZER_N_B())
    {
        digits.push_back(number.MOD_NN_N(base));
        number = number.DIV_NN_N(base);
    }

    std::reverse(digits.begin(), digits.end());
    return digits;
}

/**
     * @brief Преобразует число из P-ичной системы счисления в 10-ичную.
     *
     * Выполняет перевод натурального числа, представленного строкой num, из СС с основанием base
     * в 10-ичную СС. Проверяет корректность цифр в строке относительно указанного основания.
     *
     * @param num Строковое представление числа в P-ичной CC.
     * @param base Основание исходной CC (2 ≤ base ≤ 36).
     * @throws std::invalid_argument Если строка num содержит недопустимые символы для данной CC или основание base < 2.
     * @return Натуральное исходное число в 10-ичной СС.
     */
Natural ExtraMethods::TRANS_PDEC_STRN_N(const std::string& num, const Natural& base) const
{
    if (base < Natural("2"))
        throw std::invalid_argument("Неверное основание: base должен быть больше 1");

    for (auto& c : num)
    {
        Natural digit;
        if (c >= '0' && c <= '9')
            digit = Natural(c - '0');
        else
            digit = Natural(10 + (c - 'A'));
        if (digit >= base)
            throw std::invalid_argument("Неверная начальная система счисления!");
    }
    Natural N("0");
    for (auto& c : num) {
        Natural digit;
        if (c >= '0' && c <= '9')
            digit = Natural(c - '0');
        else
            digit = Natural(10 + (c - 'A'));
        N = N.MUL_NN_N(base).ADD_NN_N(digit);
    }
    return N;
}

/**
     * @brief Преобразует целое число в его двоичное представление с фиксированной длиной в памяти.
     *
     * Если число отрицательное, применяется инвертирование битов и добавляется единица (дополнительный код).
     * Для положительных чисел выполняется обычное преобразование в двоичную форму.
     *
     * @param num Целое число для преобразования.
     * @param bitLength Требуемая длина двоичного представления (в битах).
     * @throws std::invalid_argument Если bitLength меньше или равна длине num в 2-ичной СС.
     * @return Целое число, представляющее двоичный код исходного.
     */
Integer ExtraMethods::TRANS_BIN_ZN_Z(const Integer& num, const Natural& bitLength) const
{
    auto binDigits = GETDIGITS_NN_VECN(num.ABS_Z_N(), Natural("2"));
    
    if (bitLength <= binDigits.size())
        throw std::invalid_argument("Неверный аргумент: bitLength должна превышать длину двоичного представления num");

    for (size_t i = 0; bitLength > (Natural(std::to_string(binDigits.size()))); ++i)
        binDigits.insert(binDigits.begin(), Natural("0"));

    if (num.POZ_Z_D() == -1)
    {
        for (size_t i = binDigits.size(); i > 0; --i)
            binDigits[i - 1] = binDigits[i - 1].NZER_N_B() ? Natural("0") : Natural("1");

        size_t index = binDigits.size() - 1;
        if (binDigits[index].NZER_N_B())
        {
            binDigits[index] = Natural("0");
            while (binDigits[index - 1].NZER_N_B())
            {
                binDigits[index - 1] = Natural("0");
                index--;
            }
            binDigits[index - 1] = Natural("1");
        }
        else
            binDigits[index] = binDigits[index].ADD_1N_N();
    }

    std::string binInteger = "";
    for (auto& digit : binDigits)
        binInteger += digit.toString();
    return Integer(Natural(binInteger));
}

/**
     * @brief Переводит целое число в факториальную систему счисления, сохраняя знак.
     * @param num Целое число для преобразования.
     * @return Целое число в факториальной СС.
     */
Integer ExtraMethods::TRANS_DECFAC_Z_Z(const Integer& num) const
{
    Natural number = num.ABS_Z_N();
    if (!number.NZER_N_B())
        return Integer(number);

    std::vector<Natural> fac;
    Natural base("2");

    while (number > Natural("0"))
    {
        fac.push_back(number.MOD_NN_N(base));
        number = number.DIV_NN_N(base);
        base = base.ADD_1N_N();
    }

    std::string factorial = "";
    for (size_t i = 0; i < fac.size(); ++i)
        factorial += fac[fac.size() - i - 1].toString();

    return Integer(Natural(factorial), num.POZ_Z_D() == -1 ? 1 : 0);
}

/**
     * @brief Преобразует число из факториальной СС обратно в десятичную, сохраняя знак.
     * @param num Целое число в факториальной СС.
     * @return Целое число в 10-ичной СС.
     */
Integer ExtraMethods::TRANS_FACDEC_Z_Z(const Integer& num) const
{
    auto digits = GETDIGITS_NN_VECN(num.ABS_Z_N(), Natural("10"));
    Natural N("0");
    Natural base(std::to_string(digits.size() + 1));
    for (auto& digit : digits)
    {
        N = N.MUL_NN_N(base).ADD_NN_N(digit);
        base = base.SUB_NN_N(Natural("1"));
    }

    return Integer(N, num.POZ_Z_D() == -1 ? 1 : 0);
}

/**
     * @brief Проверяет, является ли число "счастливым".
     *
     * Последовательно заменяет число суммой квадратов его цифр,
     * пока либо не получит 1 (тогда число — счастливое), либо не зациклится.
     *
     * @param num Проверяемое натуральное число.
     * @return true, если число счастливое, иначе false.
     */
bool ExtraMethods::FINDOUT_LUCKYNUMBER_N_B(const Natural& num) const
{
    Natural sum("0");
    Natural number = num;
    std::set<Natural> numbers;
    while (!numbers.count(sum))
    {
        numbers.insert(sum);
        sum = Natural("0");
        for (auto& digit : GETDIGITS_NN_VECN(number, Natural("10")))
            sum = sum + (digit * digit);
        if (sum == Natural("1"))
            return true;
        number = sum;
    }

    return false;
}

/**
     * @brief Возводит целое число в целую неотрицательную степень.
     *
     * Использует двоичное разложение показателя для оптимизации (метод быстрого возведения в степень).
     *
     * @param num Основание степени.
     * @param exp Показатель степени (>= 0).
     * @return Целое число, результат num^exp.
     */
Integer ExtraMethods::EXP_ZN_Z(const Integer& num, const Natural& exp) const {
    std::vector<Natural> binNumberVec = GETDIGITS_NN_VECN(exp, Natural(2));
    Integer P = Integer(1, 0);
    for (int i = 0; i < binNumberVec.size(); i++)
    {
        if (binNumberVec[i] == Natural(0))
            P = P * P;
        else
            P = num * P * P;
    }

    return P;
}

/**
     * @brief Переводит число из одной системы счисления в другую.
     *
     * Сначала преобразует строковое представление числа num.first из CC baseP
     * в десятичную, затем из 10-ичной в CC baseQ. Учитывает знак числа (num.second).
     *
     * @param num Пара, где num.first — строка с числом, а num.second — знак (0 для положительного, 1 для отрицательного).
     * @param baseP Основание исходной СС (2 ≤ baseP ≤ 36).
     * @param baseQ Основание целевой СС (2 ≤ baseQ ≤ 36).
     * @throws std::invalid_argument Если num.first содержит недопустимые символы для системы baseP.
     * @return Строковое представление числа в СС baseQ (с учётом знака).
     */
std::string ExtraMethods::TRANS_PQ_STRNN_STR(const std::pair<std::string, int> num, const Natural& baseP, const Natural& baseQ) const {
    for (auto& c : num.first)
    {
        Natural digit;
        if (c >= '0' && c <= '9')
            digit = Natural(c - '0');
        else
            digit = Natural(10 + (c - 'A'));
        if (digit > baseP || digit == baseP)
            throw std::invalid_argument("Неверная начальная система счисления!");
    }
    
    std::vector<Natural> QNumVec = GETDIGITS_NN_VECN(TRANS_PDEC_STRN_N(num.first, baseP), baseQ);

    std::string res = "";

    for (auto& digit : QNumVec)
    {
        if (digit < Natural("10"))
            res += digit.toString();
        else
            res += ('A' + std::stoi(digit.toString()) - 10);
    }
    return num.second == 1 ? "-" + res : res;
}