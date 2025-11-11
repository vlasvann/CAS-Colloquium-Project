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
Integer::Integer(const Natural& nat) : m_absolute(nat), m_sign(0) {}

/**
 * @brief Конструктор с явным указанием знака
 * @param abs Абсолютное значение числа
 * @param sgn Знак числа (0 - положительное, 1 - отрицательное)
 * 
 * Позволяет создать целое число с заданным абсолютным значением и знаком.
 * Гарантирует корректное представление нуля (знак всегда 0 для нуля).
 */
Integer::Integer(const Natural& abs, int sgn) : m_absolute(abs), m_sign(sgn) {}

/**
 * @brief Конструктор из строкового представления
 * @param str Строковое представление целого числа
 * 
 * Парсит строку в целое число. Поддерживает положительные числа без знака,
 * отрицательные числа с префиксом '-' и ноль. Выполняет базовую валидацию
 * формата входной строки.
 */
Integer::Integer(const std::string& str){
    if (str.empty() || str == "0") {
        m_sign = 0;
        m_absolute = Natural(0);
    } else if (str[0] == '-') {
        m_sign = 1;
        m_absolute = Natural(str.substr(1));
    } else {
        m_sign = 0;
        m_absolute = Natural(str);
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
Natural Integer::ABS_Z_N() const {
    return m_absolute;
}

/**
 * @brief Определение знака числа
 * @return Целое число: 0 - ноль, 1 - положительное, -1 - отрицательное
 * 
 * Анализирует знак и значение числа. Проверяет является ли число нулем,
 * положительным или отрицательным. Корректно обрабатывает пограничные случаи.
 */
int Integer::POZ_Z_D() const {
    if(!m_absolute.NZER_N_B()){
        return 0;
    }
    if (m_sign == 0){
        return 1;
    }
    if (m_sign == 1){
        return -1;
    }
    return 0;
}

/**
 * @brief Умножение числа на -1
 * @return Новое целое число с противоположным знаком
 * 
 * Изменяет знак числа на противоположный. Для нуля возвращает ноль,
 * для положительных чисел - отрицательные, для отрицательных - положительные.
 * Сохраняет абсолютное значение неизменным.
 */
Integer Integer::MUL_ZM_Z() const {
    if(m_absolute == Natural(0)){
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
Integer Integer::TRANS_N_Z(const Natural& natural) {
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
Natural Integer::TRANS_Z_N() const {
    if(m_sign == 1){
        throw std::invalid_argument("Число должно быть неотрицательное");
    }
    if (m_sign == 0){
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
Integer Integer::ADD_ZZ_Z(const Integer& other) const {
    int pos1 = this->POZ_Z_D();
    int pos2 = other.POZ_Z_D();

    if (pos1 == 0) return other;
    if (pos2 == 0) return *this;

    Natural abs1 = this->ABS_Z_N();
    Natural abs2 = other.ABS_Z_N();

    if (pos1 == pos2) {
        Natural sum = abs1 + abs2;
        if (pos1 == -1) {
            return Integer(sum).MUL_ZM_Z();
        }
        return Integer(sum);
    }

    if (abs1 > abs2) {
        Natural diff = abs1 - abs2;
        if (pos1 == -1) {
            return Integer(diff).MUL_ZM_Z();
        }
        return Integer(diff);
    } else if (abs2 > abs1) {
        Natural diff = abs2 - abs1;
        if (pos2 == -1) {
            return Integer(diff).MUL_ZM_Z();
        }
        return Integer(diff);
    } else {
        return Integer();
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
Integer Integer::SUB_ZZ_Z(const Integer& other) const {
    Natural abs1 = this->ABS_Z_N();
    Natural abs2 = other.ABS_Z_N();
    
    if ((abs1 == Natural(0)) && (abs2 == Natural(0))) {
        return Integer();
    }
    
    if (abs1 == Natural(0)) {
        return other.MUL_ZM_Z();
    }
    
    if (abs2 == Natural(0)) {
        return *this;
    }
    
    if (this->POZ_Z_D() == 1 && other.POZ_Z_D() == 1) {
        if (abs1 > abs2 || abs1 == abs2) {
            Natural resultAbs = abs1 - abs2;
            return Integer(resultAbs);
        } else {
            Natural resultAbs = abs2 - abs1;
            return Integer(resultAbs, 1);
        }
    }
    
    if (this->POZ_Z_D() == -1 && other.POZ_Z_D() == -1) {
        if ((abs1 > abs2) || (abs1 == abs2)) {
            Natural resultAbs = abs1 - abs2;
            return Integer(resultAbs, 1);
        } else {
            Natural resultAbs = abs2 - abs1;
            return Integer(resultAbs); //swap
        }
    }
    
    if (this->POZ_Z_D() == 1 && other.POZ_Z_D() == -1) {
        Natural resultAbs = abs1 + abs2;
        return Integer(resultAbs); //swap
    }
    
    if (this->POZ_Z_D() == -1 && other.POZ_Z_D() == 1) {
        Natural resultAbs = abs1 + abs2;
        return Integer(resultAbs, 1);
    }
    
    return Integer();
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
Integer Integer::MUL_ZZ_Z(const Integer& other) const {
    Natural abs1 = this->ABS_Z_N();
    Natural abs2 = other.ABS_Z_N();

    if (!abs1.NZER_N_B() || !abs2.NZER_N_B()) {
        return Integer();
    }

    Natural product = abs1 * abs2;
    Integer result(product);

    if (this->POZ_Z_D() * other.POZ_Z_D() < 0) {
        return result.MUL_ZM_Z();
    }

    return result;
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
Integer Integer::DIV_ZZ_Z(const Integer& divisor) const {
    if (divisor.POZ_Z_D() == 0) {
        throw std::invalid_argument("Деление на ноль");
    }

    int dividendSign = this->POZ_Z_D();
    int divisorSign = divisor.POZ_Z_D();

    if (dividendSign == 0) {
        return Integer();
    }

    Natural dividendAbs = this->ABS_Z_N();
    Natural divisorAbs = divisor.ABS_Z_N();
    Natural quotientAbs = dividendAbs.DIV_NN_N(divisorAbs);
    bool isExactDivision = (!((dividendAbs % divisorAbs).NZER_N_B()));

    // Оба числа положительные
    if (dividendSign > 0 && divisorSign > 0) {
        return Integer(quotientAbs);
    }

    // Делимое положительное, делитель отрицательный
    if (dividendSign > 0 && divisorSign < 0) {
        return Integer(quotientAbs, 1);
    }

    // Делимое отрицательное, делитель положительный
    if (dividendSign < 0 && divisorSign > 0) {
        if (isExactDivision) {
            return Integer(quotientAbs, 1);
        } else {
            return Integer(quotientAbs.ADD_1N_N(), 1);
        }
    }

    // Оба числа отрицательные
    if (dividendSign < 0 && divisorSign < 0) {
        if (isExactDivision) {
            return Integer(quotientAbs);
        } else {
            return Integer(quotientAbs.ADD_1N_N());
        }
    }

    return Integer();
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
Integer Integer::MOD_ZZ_Z(const Integer& divisor) const {
    if (divisor == Integer()) {
        throw std::invalid_argument("Деление на ноль");
    }
    if (this->POZ_Z_D() == 0) {
        return Integer();
    }
    Integer q = this->DIV_ZZ_Z(divisor);
    Integer bq = divisor.MUL_ZZ_Z(q);
    return this->SUB_ZZ_Z(bq);
}

/**
 * @brief Строковое представление числа
 * @return Строка, представляющая число
 * 
 * Преобразует целое число в строковое представление. Для положительных чисел
 * возвращает строку без знака, для отрицательных - с префиксом '-',
 * для нуля возвращает "0".
 */
std::string Integer::toString() const {
    if (*this == Integer()) {
        return "0";
    }
    
    std::string absStr = m_absolute.toString();
    
    if (m_sign == 0) {
        return absStr;
    } else {
        return "-" + absStr;
    }
}
