#include "rational.h"
#include <stdexcept>

/*
 * Developed by Smirnov Aleksandr Dmitrievich group 4382,
 * Vyaznikov Nikita 4382 and Shlei Nikita 4382
 * Rational - реализация класса рациональных чисел
 */

/**
 * @brief Конструктор класса Rational по умолчанию.
 * @return Объект класса Rational
 * 
 * Создаёт Rational с числителем 0 и знаменателем 1
*/
Rational::Rational() : m_numerator(Integer("0")), m_denominator(Natural("1")) {}

/**
 * @brief Параметризированный конструктор класса Rational.
 * @param num целый числитель в формате const Integer&
 * @param den натуральный знаменатель в формате const Natural&
 * @return Объект класса Rational
 * @throw std::invalid_argument, если den равен 0
 * 
 * Создаёт Rational с заданным числителем и знаменателем
*/
Rational::Rational(const Integer& num, const Natural& den) : m_numerator(num), m_denominator(den) {
    if (!(this->m_denominator.NZER_N_B())){
        throw std::invalid_argument("Ноль в знаменателе рационального числа");
    }
}

/**
 * @brief Конструктор класса Rational из строки.
 * @param number исходное число в формате const string&
 * @return Объект класса Rational
 * @throw std::invalid_argument, если в знаменателе 0
 * 
 * Создаёт Rational из заданной строки. Предполагается, что формат изначально верен.
 * Если получается так, что знаменатель получившейся дроби равен 0, то выбрасывается исключение
*/
Rational::Rational(const std::string& number) {
    size_t slashPos = number.find('/');
    if (slashPos == std::string::npos){
        this->m_numerator = Integer(number);
        this->m_denominator = Natural("1");
    }
    else{
        this->m_numerator = Integer(number.substr(0, slashPos));
        this->m_denominator = Natural(number.substr(slashPos + 1));
        if (this->m_denominator == Natural("0")){
            throw std::invalid_argument("Ноль в знаменателе рационального числа");
        }
    }
}

/**
 * @brief Метод сокращения дроби
 * @return Rational сокращённая дробь
 * 
 * Находит НОД числителя и знаменателя и делит их на него.
*/
Rational Rational::RED_Q_Q() const {
    Natural abs_num = this->m_numerator.ABS_Z_N();
    Natural GCF = abs_num.GCF_NN_N(this->m_denominator);
    Integer red_num = this->m_numerator / GCF;
    Natural red_den = this->m_denominator / GCF;
    return Rational(red_num, red_den);
}

/**
 * @brief Метод проверки сокращённого дробного на целое
 * @return true, если можно перевести в целое, иначе - false
 * 
 * Сокращает дробь и проверяет, равен ли знаменатель единице
*/
bool Rational::INT_Q_B() const {
    Rational red_q = this->RED_Q_Q();
    Natural red_den = red_q.getDenominator();
    return (red_den == Natural("1"));
}

/**
 * @brief Метод перевода целого в рациональное
 * @return Rational полученное рациональное число
 * 
 * Создаёт рациональное число с числителем из исходного целого числа,
 * а знаменатель равен единице
*/
Rational Rational::TRANS_Z_Q(const Integer& num) {
    return Rational(num, Natural("1"));
}

/**
 * @brief Метод перевода рационального в целое
 * @return Integer полученное целое число
 * @throw std::runtime_error, если знаменатель не равен 1
 * 
 * Сокращает дробь, проверяет на целое с помощью INT_Q_B.
 * Если не является целым, то выбрасывает исключение, иначе возвращает числитель
*/
Integer Rational::TRANS_Q_Z() const {
    Rational red_q = this->RED_Q_Q();
    if (red_q.INT_Q_B()){
        return red_q.m_numerator;
    }
    throw std::runtime_error("Попытка перевести рациональное число со знаменателем, не равным единице, в целое");
}

/**
* @brief Суммирует два рациональных числа
* @param other Второе слагаемое
* @return Rational Результат суммирования
*
* Вычисляет НОК знаменателей;
* Числитель = числитель1*НОК/знаменатель1 + числитель2*НОК/знаменатель2;
* Знаменатель = НОК;
*/
Rational Rational::ADD_QQ_Q(const Rational& other) const {
    Natural newDen = this->m_denominator.LCM_NN_N(other.m_denominator);
    Integer newNum = this->m_numerator * (newDen / this->m_denominator) + other.m_numerator * (newDen / other.m_denominator);
    return Rational(newNum, newDen).RED_Q_Q();
}

/**
* @brief Делает разницу двух рациональных чисел
* @param other Вычитаемое
* @return Rational Результат разности
*
* Вычисляет НОК знаменателей;
* Числитель = числитель1*НОК/знаменатель1 - числитель2*НОК/знаменатель2;
* Знаменатель = НОК;
*/
Rational Rational::SUB_QQ_Q(const Rational& other) const {
    Natural newDen = this->m_denominator.LCM_NN_N(other.m_denominator);
    Integer newNum = this->m_numerator * (newDen / this->m_denominator) - other.m_numerator * (newDen / other.m_denominator);
    return Rational(newNum, newDen).RED_Q_Q();
}

/**
* @brief Перемножает два рациональных числа
* @param other Второй множитель
* @return Rational Результат произведения
*
* Вычисляет два нода для числителя и знаменателя другой дроби
* и числителя другой дроби и знменателя
* Числитель = числитель1/нод1 * числитель2.нод2;
* Знаменатель = знаменатель1/нод2 * знаменатель2/нод1;
*/
Rational Rational::MUL_QQ_Q(const Rational& other) const {
    Natural gcf1 = Natural(this->m_numerator.ABS_Z_N()).GCF_NN_N(other.m_denominator); // нод1
    Natural gcf2 = Natural(other.m_numerator.ABS_Z_N()).GCF_NN_N(this->m_denominator); // нод2
    Rational result = Rational(this->m_numerator.DIV_ZZ_Z(Integer(gcf1,1)) * other.getNumerator().DIV_ZZ_Z(Integer(gcf2,1)), this->m_denominator.DIV_NN_N(gcf2) * other.getDenominator().DIV_NN_N(gcf1));
    return result.RED_Q_Q();
}

/**
* @brief Делит рациональное число на другое
* @param other Делимое
* @return Rational Результат деления
* @throw std::runtime_error, если делитель равен 0
*
* Вычисляет два нода для числителя и знаменателя
* и числителя другой дроби и знменателя другой дроби
* Числитель = числитель1/нод1 * знаменатель2/нод2;
* Знаменатель = знаменатель1/нод2 * числитель2/нод1;
* Для определения знака дроби складываем знаки числителей первой и второй дроби,
* если знаки разные (-1 и 1), то в сумме будет 0, значит дробь отрицательная, иначе она положительная
*/
Rational Rational::DIV_QQ_Q(const Rational& other) const {
    if(other.isZero()) // Проверка на деление на ноль
        throw std::runtime_error("Деление на ноль");

    int newSign = 0;
    if (this->m_numerator.POZ_Z_D() + other.m_numerator.POZ_Z_D() == 0){
        newSign = 1;
    }
    
    Natural gcf1 = Natural(this->m_numerator.ABS_Z_N()).GCF_NN_N(other.m_numerator.ABS_Z_N());    // нод1
    Natural gcf2 = Natural(other.m_denominator.GCF_NN_N(this->m_denominator));                            // нод2

    Integer newNum = Integer(this->m_numerator.ABS_Z_N().DIV_NN_N(gcf1) * other.m_denominator.DIV_NN_N(gcf2),
                             newSign);
    Natural newDenum = this->m_denominator.DIV_NN_N(gcf2) * other.getNumerator().ABS_Z_N().DIV_NN_N(gcf1);

    return Rational(newNum, newDenum).RED_Q_Q();
}

/**
* @brief Перевод рационального числа в строку
* @return string представляющая рациональное число строка
*/
std::string Rational::toString() const
{
    std::string res {this->m_numerator.toString()};
    if (!m_denominator.COM_NN_D(Natural("1")))
    {
        return res;
    }
    return res + "/" + this->m_denominator.toString();
}

/**
* @brief Проверка на равенство 0
* @return true, если 0, иначе - false 
*
* Проверяет, равен ли числитель 0
*/
bool Rational::isZero() const {
    return this->m_numerator.POZ_Z_D() == 0; 
}
