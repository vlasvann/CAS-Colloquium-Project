#include "integer.h"

/*
 * Developed by Buraya Vera and Pisarenko Aleksandra group 4382
 * Integer - реализация целых чисел с поддержкой основных арифметических операций
 */

/**
 * @brief Конструктор по умолчанию
 *
 * Создает целое число со значением ноль. Знак устанавливается в 0,
 * абсолютное значение инициализируется как натуральный ноль.
 */
Integer::Integer() : m_absolute(0), m_sign(0) {}

/**
 * @brief Конструктор из натурального числа
 * @param nat Натуральное число для преобразования
 *
 * Создает положительное целое число на основе переданного натурального числа.
 * Знак автоматически устанавливается в 0 (положительное число).
 */
Integer::Integer(const Natural &nat) : m_absolute(nat), m_sign(0) {}

/**
 * @brief Конструктор с явным указанием знака
 * @param abs Абсолютное значение числа
 * @param sgn Знак числа (0 - положительное, 1 - отрицательное)
 *
 * Позволяет создать целое число с заданным абсолютным значением и знаком.
 * Гарантирует корректное представление нуля (знак всегда 0 для нуля).
 */
Integer::Integer(const Natural &abs, int sgn) : m_absolute(abs), m_sign(sgn) {}

/**
 * @brief Конструктор из строкового представления
 * @param str Строковое представление целого числа
 *
 * Парсит строку в целое число. Поддерживает положительные числа без знака,
 * отрицательные числа с префиксом '-' и ноль. Выполняет базовую валидацию
 * формата входной строки.
 */
Integer::Integer(const std::string &str)
{
    if (str.empty() || str == "0")
    {
        Integer();
    }
    else if (str[0] == '-')
    {
        Integer(Natural(str.substr(1)), 1);
    }
    else
    {
        Integer(Natural(str));
    }
}

/**
 * @brief Получение абсолютного значения
 * @return Натуральное число - модуль целого числа
 *
 * Возвращает абсолютное значение целого числа как натуральное число.
 * Для нуля возвращает натуральный ноль, для положительных и отрицательных
 * чисел - соответствующее натуральное значение.
 */
Natural Integer::ABS_Z_N() const
{
    return m_absolute;
}

/**
 * @brief Определение знака числа
 * @return Целое число: 0 - ноль, 1 - положительное, -1 - отрицательное
 *
 * Анализирует знак и значение числа. Проверяет является ли число нулем,
 * положительным или отрицательным. Корректно обрабатывает пограничные случаи.
 */
int Integer::POZ_Z_D() const
{
    if (m_absolute == 0)
    {
        return 0;
    }
    if (m_sign == 0)
    {
        return 1;
    }
    if (m_sign == 1)
    {
        return -1;
    }
}

/**
 * @brief Умножение числа на -1
 * @return Новое целое число с противоположным знаком
 *
 * Изменяет знак числа на противоположный. Для нуля возвращает ноль,
 * для положительных чисел - отрицательные, для отрицательных - положительные.
 * Сохраняет абсолютное значение неизменным.
 */
Integer Integer::MUL_ZM_Z() const
{
    if (m_absolute == 0)
    {
        return Integer();
    }
    int new_sign = (m_sign == 0) ? 1 : 0;
    return Integer(m_absolute, new_sign);
}

/**
 * @brief Преобразование натурального числа в целое
 * @param natural Натуральное число для преобразования
 * @return Целое число с тем же абсолютным значением
 *
 * Выполняет преобразование натурального числа в целое. Результирующее
 * число всегда положительное с нулевым знаком.
 */
Integer Integer::TRANS_N_Z(const Natural &natural)
{
    return Integer(natural);
}

/**
 * @brief Преобразование целого числа в натуральное
 * @return Натуральное число - абсолютное значение
 * @throws std::invalid_argument если число отрицательное или ноль
 *
 * Преобразует положительное целое число в натуральное. Выбрасывает исключение
 * для отрицательных чисел и нуля, так как они не являются натуральными.
 */
Natural Integer::TRANS_Z_N() const
{
    if (m_absolute == 0)
    {
        throw std::invalid_argument("Ноль не натуральное число!");
    }
    if (m_sign == 0)
    {
        return m_absolute;
    }
}

/**
 * @brief Сложение двух целых чисел
 * @param other Второе слагаемое
 * @return Результат сложения
 *
 * Выполняет арифметическое сложение двух целых чисел. Корректно обрабатывает
 * все комбинации знаков: положительные, отрицательные и нулевые значения.
 * Использует алгоритмы сложения и вычитания натуральных чисел.
 */
Integer Integer::ADD_ZZ_Z(const Integer &other) const
{
    int sign1 = this->m_sign;
    int sign2 = other.m_sign;

    Natural abs1 = this->ABS_Z_N();
    Natural abs2 = other.ABS_Z_N();

    if (abs1 == 0 && abs2 == 0)
    {
        return Integer();
    }

    if (abs1 == 0)
    {
        return other;
    }

    if (abs2 == 0)
    {
        return *this;
    }

    // Обработка сложения чисел с одинаковыми знаками
    if (sign1 == sign2)
    {
        Natural sum = abs1 + abs2;
        if (this->POZ_Z_D() == -1)
        {
            Integer s = Integer(sum, 0);
            return s;
        }
        return Integer(sum);
    }
    // Обработка сложения чисел с разными знаками
    else
    {
        bool comp1 = abs1 > abs2;
        bool comp2 = abs1 < abs2;
        if (comp1 == true)
        {
            Natural difference = abs1 - abs2;
            if (this->POZ_Z_D() == 1)
            {
                return Integer(difference);
            }
            else
            {
                Integer s = Integer(difference);
                return s.MUL_ZM_Z();
            }
        }
        else if (comp2 == true)
        {
            Natural difference = abs2 - abs1;
            if (other.POZ_Z_D() == 1)
            {
                return Integer(difference);
            }
            else
            {
                Integer s = Integer(difference);
                return s.MUL_ZM_Z();
            }
        }
        else
        {
            return Integer();
        }
    }
}

/**
 * @brief Вычитание целых чисел
 * @param other Вычитаемое
 * @return Результат вычитания
 *
 * Реализует арифметическое вычитание через сложение с противоположным числом.
 * Преобразует операцию вычитания в операцию сложения с инвертированным знаком.
 */
Integer Integer::SUB_ZZ_Z(const Integer &other) const
{
    Natural abs1 = this->ABS_Z_N();
    Natural abs2 = other.ABS_Z_N();

    if (abs1 == 0 && abs2 == 0)
    {
        return Integer();
    }

    if (abs1 == 0)
    {
        return other.MUL_ZM_Z();
    }

    if (abs2 == 0)
    {
        return *this;
    }

    *this + other.MUL_ZM_Z();
}

/**
 * @brief Умножение целых чисел
 * @param other Второй множитель
 * @return Результат умножения
 *
 * Выполняет арифметическое умножение двух целых чисел. Учитывает правила знаков:
 * одинаковые знаки дают положительный результат, разные - отрицательный.
 * Ноль в любом множителе дает нулевой результат.
 */
Integer Integer::MUL_ZZ_Z(const Integer &other) const
{
    if (m_absolute == 0 || other.m_absolute == 0)
    {
        return Integer();
    }

    Natural product = m_absolute * other.m_absolute;

    int result_sign;
    if (this->m_sign == other.m_sign)
    {
        result_sign = 0;
    }
    else
    {
        result_sign = 1;
    }

    return Integer(product, result_sign);
}

/**
 * @brief Целочисленное деление
 * @param divisor Делитель
 * @return Результат деления
 * @throws std::invalid_argument при делении на ноль
 *
 * Реализует целочисленное деление с учетом знаков. Для отрицательных чисел
 * применяет правила математического целочисленного деления. Корректно
 * обрабатывает деление меньшего числа на большее.
 */
Integer Integer::DIV_ZZ_Z(const Integer &divisor) const
{
    if (divisor.m_absolute == 0)
    {
        throw std::invalid_argument("Деление на ноль");
    }

    if (m_absolute == 0)
    {
        return Integer();
    }

    Natural abs_dividend = this->ABS_Z_N();
    Natural abs_divisor = divisor.ABS_Z_N();

    bool comp = abs_dividend < abs_divisor;

    if (comp == true)
    {
        if (this->POZ_Z_D() >= 0)
        {
            return Integer();
        }
        else
        {
            if (divisor.POZ_Z_D() > 0)
            {
                return Integer(Natural(1), 1);
            }
            else
            {
                return Integer();
            }
        }
    }

    Natural quotient_abs = abs_dividend / abs_divisor;

    int quotient_sign;
    if (this->m_sign == divisor.m_sign)
    {
        quotient_sign = 0;
    }
    else
    {
        quotient_sign = 1;
    }

    if ((quotient_sign == 1) && ((abs_dividend % abs_divisor) != 0))
    {
        quotient_abs = quotient_abs + Natural(1);
    }

    return Integer(quotient_abs, quotient_sign);
}

/**
 * @brief Остаток от деления
 * @param divisor Делитель
 * @return Остаток от деления
 * @throws std::invalid_argument при делении на ноль
 *
 * Вычисляет остаток от целочисленного деления. Использует формулу:
 * remainder = dividend - (dividend / divisor) * divisor
 * Гарантирует корректное поведение для отрицательных чисел.
 */
Integer Integer::MOD_ZZ_Z(const Integer &divisor) const
{
    if (divisor.m_absolute == 0)
    {
        throw std::invalid_argument("Деление на ноль");
    }

    if (m_absolute == 0)
    {
        return Integer();
    }

    Integer quotient = *this / divisor;

    Integer product = quotient * divisor;

    Integer remainder = *this - product;

    return remainder;
}

/**
 * @brief Строковое представление числа
 * @return Строка, представляющая число
 *
 * Преобразует целое число в строковое представление. Для положительных чисел
 * возвращает строку без знака, для отрицательных - с префиксом '-',
 * для нуля возвращает "0".
 */
std::string Integer::toString() const
{
    if (m_absolute == 0)
    {
        return "0";
    }

    std::string absStr = m_absolute.toString();

    if (m_sign == 0)
    {
        return absStr;
    }
    else
    {
        return "-" + absStr;
    }
}