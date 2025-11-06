#include "polynomial.h"

/**
 * Developed by Smirnov Nikolay 4382,
 * Sozinov Denis 4382,
 * Isaev Andrei 4382
 * Polynomial - реализация класса полиномов
 * 
 */
/**
 * @brief Конструктор класса Polynomial по умолчанию
 * @return Объект класса Polynomial
 *
 * Создает нулевой полином (степень и коэффициент - 0)
 */

Polynomial::Polynomial() : m_degree(0) 
{
    m_value[m_degree] = Rational();
}

/**
 * @brief Конструктор класса Polynomial на основе пар степень - рациональное число, где каждая пара это моном в составе полинома
 * @param value пары степень - рациональное число в формате const std::unordered_map
 * @return Объект класса Polynomial
 *
 * Создает полином с заданными степенями и рациональными коэффициентами
 */

Polynomial::Polynomial(const std::unordered_map<int, Rational>& value)
    : m_degree(0)
{
    for (auto curr = value.begin(); curr != value.end(); ++curr)
    {
        if (curr->second.isZero())
            continue;

        if (curr->first > m_degree)
            m_degree = curr->first;

        m_value[curr->first] = curr->second;
    }

    if (m_degree == 0 && m_value.empty())
        m_value[m_degree] = Rational();
}

/**
 * @brief Конструктор класса Polynomial на основе пар степень - целое число, где каждая пара это моном в составе полинома
 * @param value пары степень - целое число в формате const std::unordered_map
 * @return Объект класса Polynomial
 *
 * Создает полином с заданными степенями и рациональными (целые -> рациональные) коэффициентами
 */

Polynomial::Polynomial(const std::unordered_map<int, Integer>& value)
    : m_degree(0)
{
    for (auto curr = value.begin(); curr != value.end(); ++curr)
    {
        if (curr->second.isZero())
            continue;

        if (curr->first > m_degree)
            m_degree = curr->first;

        m_value[curr->first] = Rational::TRANS_Z_Q(curr->second);
    }

    if (m_degree == 0 && m_value.empty())
        m_value[m_degree] = Rational();
}

/**
 * @brief Метод сложения двух полиномов
 * @param other второй полином
 * @return Полином после операции сложения
 * 
 * Складывает два полинома (ax^i + bx^i = (a+b)x^i) i = 0...max(deg)
*/

Polynomial Polynomial::ADD_PP_P(const Polynomial& other) const {
    std::unordered_map<int, Rational> res;

    for(const auto& [degree, coeff] : other.m_value) {
        if (coeff.isZero())
            continue;

        if (m_value.find(degree) != m_value.end())
            res[degree] = res[degree] + coeff;

        else
            res[degree] = coeff;
    }

    return Polynomial(res);
}

/**
 * @brief Метод вычитания двух полиномов
 * @param other второй полином
 * @return Полином после операции вычитания
 *
 * Вычитает два полинома (ax^i - bx^i = (a-b)x^i) i = 0...max(deg)
*/

Polynomial Polynomial::SUB_PP_P(const Polynomial& other) const {
    std::unordered_map<int, Rational> res;

    for(const auto& [degree, coeff] : other.m_value) {
        if (coeff.isZero())
            continue;

        if (m_value.find(degree) != m_value.end())
            res[degree] = res[degree] + coeff;

        else
            res[degree] = Rational() - coeff;
    }

    return Polynomial(res);
}

/**
 * @brief Метод умножения полинома на рациональное число
 * @param otherCoeff рациональное число
 * @return Полином после операции умножения на рац. число
 * 
 * Умножает полином на рац. число (ax^i * b = (a*b)x^i i = 0...m_degree)
*/

Polynomial Polynomial::MUL_PQ_P(const Rational& otherCoeff) const {
    if (isZero() || otherCoeff.isZero())
        return Polynomial();

    std::unordered_map<int, Rational> res;

    for(const auto& [degree, coeff] : m_value)
        res[degree] = coeff.MUL_QQ_Q(otherCoeff);

    return Polynomial(res);
}

/**
 * @brief Метод умножения полинома на x^k
 * @param otherDeg степень
 * @return Полином после операции умножения на x^otherDeg
 * 
 * Умножает полином на x^otherDeg (ax^i * x^otherDeg = ax^(i+otherDeg) i = 0...m_degree)
*/

Polynomial Polynomial::MUL_Pxk_P(Natural otherDeg) const {
    if (isZero())
        return Polynomial();

    std::unordered_map<int, Rational> res;
    
    int otherDegree = std::stoi(otherDeg.toString());

    for (const auto& [degree, coeff] : m_value)
        res[degree + otherDegree] = coeff;

    return Polynomial(res);
}

/**
 * @brief Метод возвращающий коэффициент при старшей степени
 * @return Rational - старший коэффициент
 * 
 * Если полином нулевой, то возвращает 0, иначе поиск коэффициента
 * при старшей степени и его возврат
*/

Rational Polynomial::LED_P_Q() const {
    if (isZero()) 
        return Rational();
    
    auto highestValue = m_value.find(m_degree);
    return highestValue->second;
}

/**
 * @brief Метод возвращающий старшую степень
 * @return Natural - старшая степень
 * 
 * Если полином нулевой, то возвращает 0, иначе возврат старшей степени
*/

Natural Polynomial::DEG_P_N() const {
    return Natural(m_degree);
}

/**
 * @brief Метод вычисления НОК знаменателей и НОД числителей
 * @return Rational - дробь НОД/НОК
 * 
 * Если полином нулевой, то возвращает 0, 
 * иначе высчитывает НОД и НОК, используя ассоциативность НОД и НОК,
 * возвращает дробь
*/

Rational Polynomial::FAC_P_Q() const {
    if (isZero())
        throw std::logic_error("Это нулевой полином, выносить нечего.");

    auto it = m_value.begin();
    Integer gcf = it->second.getNumerator().ABS_Z_N();
    Natural lcm = it->second.getDenominator();
    ++it;

    for (; it !=m_value.end(); it++){
        const Rational& coeff = it->second;
        Integer num = coeff.getNumerator().ABS_Z_N();
        Natural den = coeff.getDenominator();

        Natural nextGcf = gcf.TRANS_Z_N().GCF_NN_N(num.TRANS_Z_N());
        gcf = gcf.TRANS_N_Z(nextGcf);

        lcm = lcm.LCM_NN_N(den);
    }

    return Rational(gcf, lcm);
}

/**
 * @brief Метод умножения двух полиномов
 * @return Итоговый полином
 * 
 * Если один из полиномов нулевой, возвращает 0. 
 * Иначе выполняется следующее:
 * 1. Каждое слагаемое a*x^i первого полинома умножается на коэффициент b второго полинома:
 *      a*x^i * b = (a*b)*x^i
 * 2. Затем результат умножается на x^k степени текущего слагаемого второго полинома:
 *      (a*b)*x^i * x^k = (a*b)*x^(i+k)
 * 3. Полученный моном прибавляется к общему результату
 */

Polynomial Polynomial::MUL_PP_P(const Polynomial& other) const {
    Polynomial result{};
    
    if (this->isZero() || other.isZero())
        return result;

    for (const auto& [deg, coeff]: other.getValue()){
        Polynomial tmp = this->MUL_PQ_P(coeff);
        tmp = tmp.MUL_Pxk_P(deg);
        result = result + tmp;
    }
    
    return result;
}

/**
 * @brief Метод деления полиномов (получение частного)
 * @param divisor Делитель
 * @return Частное от деления
 * 
 * Если делитель - нулевой полином, выбрасывается исключение.
 * Иначе происходит алгоритм деления
 * Возвращаем частное
 */

Polynomial Polynomial::DIV_PP_P(const Polynomial& divisor) const {
    if (divisor.isZero())
        throw std::logic_error("На 0 делить нельзя!");
    
    if (!divisor.DEG_P_N().NZER_N_B())
        throw std::logic_error("Введите полином, а не константу!");

    Polynomial quotient;
    Polynomial remainder{ m_value };

    while (remainder.DEG_P_N() >= divisor.DEG_P_N())
    {
        Natural tempDegree = remainder.DEG_P_N() - divisor.DEG_P_N();
        Rational tempCoeff = remainder.LED_P_Q() / divisor.LED_P_Q();
        Polynomial temp = Polynomial(std::unordered_map<int, Rational>{{std::stoi(tempDegree.toString()), tempCoeff}});
        remainder = remainder - divisor.MUL_Pxk_P(tempDegree).MUL_PQ_P(tempCoeff);
        quotient = quotient + temp;
    }

    return quotient;
}

/**
 * @brief Метод нахождения остатка от деления полиномов
 * @param divisor Делитель
 * @return Остаток от деления
 * 
 * Если делитель - нулевой полином, выбрасывается исключение.
 * Иначе происходит деление
 * Дальше вычисляется остаток, как полином - частное * делитель  
 */

Polynomial Polynomial::MOD_PP_P(const Polynomial& divisor) const {
    if (divisor.isZero())
        throw std::logic_error("На 0 делить нельзя!");

    Polynomial quotient = DIV_PP_P(divisor);
    return *this - quotient * divisor;
}

/**
 * @brief Метод нахождения наибольшего общего делителя (НОД) двух полиномов
 * @param other Второй полином
 * @return НОД(this, other)
 * 
 * 
 * 1. Если степень 2 полинома > степени 1 полинома, меняем местами
 * 2. Пока степень второго полинома != 0:
 *      вычисляется последний ненулевой остаток,
 *      используя алгоритм евклида. Возврат НОД
 */

Polynomial Polynomial::GCF_PP_P(const Polynomial& other) const {
    if (other.isZero())
        return *this;

    if (this->DEG_P_N() < other.DEG_P_N())
        return other.GCF_PP_P(*this);

    auto thisPolynomialCopy = Polynomial(m_value);
    auto otherPolynomialCopy = Polynomial(other.getValue());
    Polynomial remainder;

    while (otherPolynomialCopy.DEG_P_N().NZER_N_B())
    {
        remainder = thisPolynomialCopy % otherPolynomialCopy;
        thisPolynomialCopy = otherPolynomialCopy;
        otherPolynomialCopy = remainder;
    }

    return thisPolynomialCopy;
}
/**
 * @brief Метод вычисления производной полинома
 * @return Производная полинома
 * 
 * Для каждого члена a*x^i:
 *      если i > 0: (a*i) * x^(i-1)
 *      если i == 0: пропускаем
 * Если полином нулевой, возвращаем 0.
 */

Polynomial Polynomial::DER_P_P() const {
    if (isZero())
        throw std::logic_error("Нет смысла брать производную от нулевого полинома.");

    std::unordered_map<int, Rational> derivativeValue;
   
    for (const auto& [deg, coeff] : m_value)
    {
        if (deg == 0)
            continue;

        derivativeValue[deg - 1] = Rational(Integer(Natural(deg)), Natural(1)) * coeff;
    }

    return Polynomial(derivativeValue);
}

/**
 * @brief Метод получения полинома с простыми корнями
 * @return полином без кратных корней
 * 
 * Находится производная
 * Вычисляется НОД (полином, его производная)
 * Полином/НОД = полином без кратных корней
 */

Polynomial Polynomial::NMR_P_P() const {
    Polynomial derivative = this->DER_P_P();

    if (derivative.isZero())
        throw std::logic_error("Данный полином уже с простыми корнями (является полиномом вида ax + b)");
    
    Polynomial gcfResult = this->GCF_PP_P(derivative);

    if (!gcfResult.DEG_P_N().NZER_N_B())
        throw std::logic_error("Данный полином уже с простыми корнями");

    return *this / gcfResult;
}
/**
 * @brief Преобразование полинома в строку
 * @return Строковое представление полинома
 */

std::string Polynomial::toString() const {
    if (isZero())
        return "0";

    std::string result;
    std::vector<int> degrees;
    degrees.reserve(m_value.size());

    for (auto it = m_value.begin(); it != m_value.end(); ++it)
    {
        int deg = it->first;
        degrees.push_back(deg);
    }

    std::sort(degrees.begin(), degrees.end(), std::greater<int>());

    for (size_t i = 0; i < degrees.size(); ++i)
    {
        int deg = degrees[i];
        const Rational& coef = m_value.find(deg)->second;
        std::string coefStr = coef.toString();

        if (coefStr[0] != "-" && i > 0)
            result += "+";

        result += deg == 0 ? coefStr : coefStr != "1" ? coefStr + "x^" + std::to_string(deg) : "x^" + std::to_string(deg);
        
    }

    return result;
}
/**
 * @brief Проверка, является ли полином нулевым
 * @return true, если полином == 0, иначе false
 */


bool Polynomial::isZero() const {
    auto it = m_value.find(m_degree);
    return m_degree == 0 && it != m_value.end() && it->second.isZero();
}

/**
 * @brief Вычисление значения полинома в заданной точке
 * @param x Точка вычисления
 * @return Значение полинома в x
 */

/**
 * @brief Получение коэффициента при x^deg
 * @param deg Степень
 * @return Коэффициент при x^deg
 */

Polynomial Polynomial::operator+(const Polynomial& other) const {
    return ADD_PP_P(other);
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    return SUB_PP_P(other);
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    return MUL_PP_P(other);
}

Polynomial Polynomial::operator/(const Polynomial& other) const {
    return DIV_PP_P(other);
}

Polynomial Polynomial::operator%(const Polynomial& other) const {
    return MOD_PP_P(other);
}