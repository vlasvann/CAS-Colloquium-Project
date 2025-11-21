#include "controller.h"
#include <stdexcept>

/**
 * Developed by Danil Babin group 4381
 * @brief Конструктор контроллера
 *
 * Инициализирует доступные операции и их метаданные при создании объекта.
 */
Controller::Controller() {
    initializeOperations();
}

/**
 * @brief Инициализация доступных операций
 *
 * Заполняет контейнеры метаданными всех поддерживаемых операций для каждого типа данных.
 */
void Controller::initializeOperations() {
    // Операции с натуральными числами
    m_typeMethods["Natural"] = {"ADD_NN_N", "SUB_NN_N", "MUL_NN_N", "DIV_NN_N", "MOD_NN_N", "GCF_NN_N", "LCM_NN_N"};
    m_methodOperands["ADD_NN_N"] = 2;
    m_methodOperands["SUB_NN_N"] = 2;
    m_methodOperands["MUL_NN_N"] = 2;
    m_methodOperands["DIV_NN_N"] = 2;
    m_methodOperands["MOD_NN_N"] = 2;
    m_methodOperands["GCF_NN_N"] = 2;
    m_methodOperands["LCM_NN_N"] = 2;
    m_methodDisplayNames["ADD_NN_N"] = "Сложение натуральных чисел";
    m_methodDisplayNames["SUB_NN_N"] = "Вычитание натуральных чисел";
    m_methodDisplayNames["MUL_NN_N"] = "Умножение натуральных чисел";
    m_methodDisplayNames["DIV_NN_N"] = "Деление натуральных чисел";
    m_methodDisplayNames["MOD_NN_N"] = "Остаток от деления натуральных чисел";
    m_methodDisplayNames["GCF_NN_N"] = "НОД натуральных чисел";
    m_methodDisplayNames["LCM_NN_N"] = "НОК натуральных чисел";

    // Операции с целыми числами
    m_typeMethods["Integer"] = {"ABS_Z_Z", "ADD_ZZ_Z", "SUB_ZZ_Z", "MUL_ZZ_Z", "DIV_ZZ_Z", "MOD_ZZ_Z"};
    m_methodOperands["ABS_Z_Z"] = 1;
    m_methodOperands["ADD_ZZ_Z"] = 2;
    m_methodOperands["SUB_ZZ_Z"] = 2;
    m_methodOperands["MUL_ZZ_Z"] = 2;
    m_methodOperands["DIV_ZZ_Z"] = 2;
    m_methodOperands["MOD_ZZ_Z"] = 2;
    m_methodDisplayNames["ABS_Z_Z"] = "Модуль целого числа";
    m_methodDisplayNames["ADD_ZZ_Z"] = "Сложение целых чисел";
    m_methodDisplayNames["SUB_ZZ_Z"] = "Вычитание целых чисел";
    m_methodDisplayNames["MUL_ZZ_Z"] = "Умножение целых чисел";
    m_methodDisplayNames["DIV_ZZ_Z"] = "Деление целых чисел";
    m_methodDisplayNames["MOD_ZZ_Z"] = "Остаток от деления целых чисел";

    // Операции с рациональными числами
    m_typeMethods["Rational"] = {"ADD_QQ_Q", "SUB_QQ_Q", "MUL_QQ_Q", "DIV_QQ_Q", "RED_Q_Q"};
    m_methodOperands["ADD_QQ_Q"] = 2;
    m_methodOperands["SUB_QQ_Q"] = 2;
    m_methodOperands["MUL_QQ_Q"] = 2;
    m_methodOperands["DIV_QQ_Q"] = 2;
    m_methodOperands["RED_Q_Q"] = 1;
    m_methodDisplayNames["RED_Q_Q"] = "Сокращение дроби";
    m_methodDisplayNames["ADD_QQ_Q"] = "Сложение дробей";
    m_methodDisplayNames["SUB_QQ_Q"] = "Вычитание дробей";
    m_methodDisplayNames["MUL_QQ_Q"] = "Умножение дробей";
    m_methodDisplayNames["DIV_QQ_Q"] = "Деление дробей";

    // Операции с многочленами
    m_typeMethods["Polynomial"] = {"ADD_PP_P", "SUB_PP_P", "MUL_PQ_P", "LED_P_Q", "DEG_P_N", "MUL_PP_P", "DIV_PP_P", "MOD_PP_P", "GCF_PP_P", "DER_P_P"};
    m_methodOperands["ADD_PP_P"] = 2;
    m_methodOperands["SUB_PP_P"] = 2;
    m_methodOperands["MUL_PQ_P"] = 2;
    m_methodOperands["LED_P_Q"] = 1;
    m_methodOperands["DEG_P_N"] = 1;
    m_methodOperands["MUL_PP_P"] = 2;
    m_methodOperands["DIV_PP_P"] = 2;
    m_methodOperands["MOD_PP_P"] = 2;
    m_methodOperands["GCF_PP_P"] = 2;
    m_methodOperands["DER_P_P"] = 1;
    m_methodOperands["NMR_P_P"] = 1;
    m_methodOperands["MUL_Pxk_P"] = 2;
    m_methodOperands["FAC_P_Q"] = 1;
    m_methodDisplayNames["ADD_PP_P"] = "Сложение многочленов";
    m_methodDisplayNames["SUB_PP_P"] = "Вычитание многочленов";
    m_methodDisplayNames["MUL_PQ_P"] = "Умножение многочлена на рациональное число";
    m_methodDisplayNames["LED_P_Q"] = "Старший коэффициент многочлена";
    m_methodDisplayNames["DEG_P_N"] = "Степень многочлена";
    m_methodDisplayNames["MUL_PP_P"] = "Умножение многочленов";
    m_methodDisplayNames["DIV_PP_P"] = "Частное от деления многочленов";
    m_methodDisplayNames["MOD_PP_P"] = "Остаток от деления многочленов";
    m_methodDisplayNames["GCF_PP_P"] = "НОД многочленов";
    m_methodDisplayNames["DER_P_P"] = "Производная многочлена";
    m_methodDisplayNames["NMR_P_P"] = "Преобразование многочлена — кратные корни в простые";
    m_methodDisplayNames["MUL_Pxk_P"] = "Умножения полинома на x^k";
    m_methodDisplayNames["FAC_P_Q"] = "Вычисления НОК знаменателей и НОД числителей многочлена";


    //Дополнительные математические операции
    m_typeMethods["Extra Methods"] = {"TRANS_BIN_ZN_Z", "TRANS_DECFAC_Z_Z", "TRANS_FACDEC_Z_Z", "FINDOUT_LUCKYNUMBER_N_B", "EXP_ZN_Z", "TRANS_PQ_STRNN_STR"};
    m_methodOperands["TRANS_BIN_ZN_Z"] = 2;
    m_methodOperands["TRANS_DECFAC_Z_Z"] = 1;
    m_methodOperands["TRANS_FACDEC_Z_Z"] = 1;
    m_methodOperands["FINDOUT_LUCKYNUMBER_N_B"] = 1;
    m_methodOperands["EXP_ZN_Z"] = 2;
    m_methodOperands["TRANS_PQ_STRNN_STR"] = 3;
    m_methodDisplayNames["TRANS_BIN_ZN_Z"] = "Преобразование в двоичное представление";
    m_methodDisplayNames["TRANS_DECFAC_Z_Z"] = "Преобразование в факториальное представление";
    m_methodDisplayNames["TRANS_FACDEC_Z_Z"] = "Преобразование из факториальной системы";
    m_methodDisplayNames["FINDOUT_LUCKYNUMBER_N_B"] = "Проверка на счастливое число";
    m_methodDisplayNames["EXP_ZN_Z"] = "Возведение в степень";
    m_methodDisplayNames["TRANS_PQ_STRNN_STR"] = "Преобразование между системами счисления";
}

/**
 * @brief Получить список доступных типов данных
 * @return Вектор строк с названиями типов данных
 */
std::vector<std::string> Controller::getAvailableTypes() const {
    return {"Greeting", "Natural", "Integer", "Rational", "Polynomial", "Extra Methods"};
}

/**
 * @brief Получить список методов для конкретного типа
 * @param type Тип данных для которого запрашиваются методы
 * @return Вектор строк с техническими именами методов
 */
std::vector<std::string> Controller::getMethodsForType(const std::string& type) const {
    auto it = m_typeMethods.find(type);
    if (it != m_typeMethods.end()) {
        return it->second;
    }
    return {};
}

/**
 * @brief Получить количество операндов для метода
 * @param method Техническое имя метода
 * @return Количество требуемых операндов
 */
int Controller::getOperandCount(const std::string& method) const {
    auto it = m_methodOperands.find(method);
    if (it != m_methodOperands.end()) {
        return it->second;
    }
    return 0;
}

/**
 * @brief Получить описание метода
 * @param method Техническое имя метода
 * @return Человеко-читаемое описание метода
 */
std::string Controller::getMethodDescription(const std::string& method) const {
    auto it = m_methodDisplayNames.find(method);
    if (it != m_methodDisplayNames.end()) {
        return it->second;
    }
    return "Описание недоступно для метода: " + method;
}

/**
 * @brief Выполнить математическую операцию
 * @param type Тип данных для операции
 * @param method Техническое имя метода
 * @param inputs Вектор входных данных
 * @return Результат выполнения операции в строковом представлении
 */
std::string Controller::executeOperation(const std::string& type,
                                         const std::string& method,
                                         const std::vector<std::string>& inputs) {
    std::string result = "";
    if(type == "Natural") result = executeNaturalOperation(method, inputs);
    else if(type == "Integer") result = executeIntegerOperation(method, inputs);
    else if (type == "Rational") result = executeRationalOperation(method, inputs);
    else if(type == "Polynomial") result = executePolynomialOperation(method, inputs);
    else if(type == "Extra Methods") result = executeExtraOperation(method, inputs);

    return result;
}

/**
 * @brief Выполнить операцию с натуральными числами
 * @param method Техническое имя метода
 * @param inputs Вектор входных данных
 * @return Результат операции в строковом представлении
 */
std::string Controller::executeNaturalOperation(const std::string& method, const std::vector<std::string>& inputs) {

    if(method == "ADD_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.ADD_NN_N(b);
        return m_parser.toString(result);
    }
    else if(method == "SUB_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.SUB_NN_N(b);
        return m_parser.toString(result);
    }
    else if(method == "MUL_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.MUL_NN_N(b);
        return m_parser.toString(result);
    }
    else if(method == "DIV_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.DIV_NN_N(b);
        return m_parser.toString(result);
    }
    else if(method == "MOD_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.MOD_NN_N(b);
        return m_parser.toString(result);
    }
    else if(method == "GCF_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.GCF_NN_N(b);
        return m_parser.toString(result);
    }
    else if(method == "LCM_NN_N"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Natural result = a.LCM_NN_N(b);
        return m_parser.toString(result);
    }
    else throw std::invalid_argument("Неизвестный метод!");
}

/**
 * @brief Выполнить операцию с целыми числами
 * @param method Техническое имя метода
 * @param inputs Вектор входных данных
 * @return Результат операции в строковом представлении
 */
std::string Controller::executeIntegerOperation(const std::string& method, const std::vector<std::string>& inputs) {

    if(method == "ABS_Z_Z"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer result = a.ABS_Z_N();
        return m_parser.toString(result);
    }
    else if(method == "ADD_ZZ_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer b = m_parser.parseInteger(inputs[1]);
        Integer result = a.ADD_ZZ_Z(b);
        return m_parser.toString(result);
    }
    else if(method == "SUB_ZZ_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer b = m_parser.parseInteger(inputs[1]);
        Integer result = a.SUB_ZZ_Z(b);
        return m_parser.toString(result);
    }
    else if(method == "MUL_ZZ_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer b = m_parser.parseInteger(inputs[1]);
        Integer result = a.MUL_ZZ_Z(b);
        return m_parser.toString(result);
    }
    else if(method == "DIV_ZZ_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer b = m_parser.parseInteger(inputs[1]);
        Integer result = a.DIV_ZZ_Z(b);
        return m_parser.toString(result);
    }
    else if(method == "MOD_ZZ_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer b = m_parser.parseInteger(inputs[1]);
        Integer result = a.MOD_ZZ_Z(b);
        return m_parser.toString(result);
    }
    else throw std::invalid_argument("Неизвестный метод!");
}

/**
 * @brief Выполнить операцию с рациональными числами
 * @param method Техническое имя метода
 * @param inputs Вектор входных данных
 * @return Результат операции в строковом представлении
 */
std::string Controller::executeRationalOperation(const std::string& method, const std::vector<std::string>& inputs) {

    if(method == "ADD_QQ_Q"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Rational a = m_parser.parseRational(inputs[0]);
        Rational b = m_parser.parseRational(inputs[1]);
        Rational result = a.ADD_QQ_Q(b);
        return m_parser.toString(result);
    }
    else if(method == "SUB_QQ_Q"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Rational a = m_parser.parseRational(inputs[0]);
        Rational b = m_parser.parseRational(inputs[1]);
        Rational result = a.SUB_QQ_Q(b);
        return m_parser.toString(result);
    }
    else if(method == "MUL_QQ_Q"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Rational a = m_parser.parseRational(inputs[0]);
        Rational b = m_parser.parseRational(inputs[1]);
        Rational result = a.MUL_QQ_Q(b);
        return m_parser.toString(result);
    }
    else if(method == "DIV_QQ_Q"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Rational a = m_parser.parseRational(inputs[0]);
        Rational b = m_parser.parseRational(inputs[1]);
        Rational result = a.DIV_QQ_Q(b);
        return m_parser.toString(result);
    }
    else if(method == "RED_Q_Q"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Rational a = m_parser.parseRational(inputs[0]);
        Rational result = a.RED_Q_Q();
        return m_parser.toString(result);
    }
    else throw std::invalid_argument("Неизвестный метод!");
}

/**
 * @brief Выполнить операцию с многочленами
 * @param method Техническое имя метода
 * @param inputs Вектор входных данных
 * @return Результат операции в строковом представлении
 */
std::string Controller::executePolynomialOperation(const std::string& method, const std::vector<std::string>& inputs) {

    if(method == "ADD_PP_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial b = m_parser.parsePolynomial(inputs[1]);
        Polynomial result = a.ADD_PP_P(b);
        return m_parser.toString(result);
    }
    else if(method == "SUB_PP_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial b = m_parser.parsePolynomial(inputs[1]);
        Polynomial result = a.SUB_PP_P(b);
        return m_parser.toString(result);
    }
    else if(method == "MUL_PQ_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Rational b = m_parser.parseRational(inputs[1]);
        Polynomial result = a.MUL_PQ_P(b);
        return m_parser.toString(result);
    }
    else if(method == "LED_P_Q"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Rational result = a.LED_P_Q();
        return m_parser.toString(result);
    }
    else if(method == "DEG_P_N"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Natural result = a.DEG_P_N();
        return m_parser.toString(result);
    }
    else if(method == "MUL_PP_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial b = m_parser.parsePolynomial(inputs[1]);
        Polynomial result = a.MUL_PP_P(b);
        return m_parser.toString(result);
    }
    else if(method == "DIV_PP_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial b = m_parser.parsePolynomial(inputs[1]);
        Polynomial result = a.DIV_PP_P(b);
        return m_parser.toString(result);
    }
    else if(method == "MOD_PP_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial b = m_parser.parsePolynomial(inputs[1]);
        Polynomial result = a.MOD_PP_P(b);
        return m_parser.toString(result);
    }
    else if(method == "GCF_PP_P"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial b = m_parser.parsePolynomial(inputs[1]);
        Polynomial result = a.GCF_PP_P(b);
        return m_parser.toString(result);
    }
    else if(method == "DER_P_P"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial result = a.DER_P_P();
        return m_parser.toString(result);
    }
    else if(method == "NMR_P_P"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial result = a.NMR_P_P();
        return m_parser.toString(result);
    }
    else if(method == "MUL_Pxk_P"){
		if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Polynomial result = a.NMR_P_P(b);
        return m_parser.toString(result);
	}
	else if(method == "FAC_P_Q"){
		if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Polynomial a = m_parser.parsePolynomial(inputs[0]);
        Polynomial result = a.FAC_P_Q(b);
        return m_parser.toString(result);
	}

	
    else throw std::invalid_argument("Неизвестный метод!");
}

/**
 * @brief Выполнить дополнительные операции
 * @param method Техническое имя метода
 * @param inputs Вектор входных данных
 * @return Результат операции в строковом представлении
 */
std::string Controller::executeExtraOperation(const std::string& method, const std::vector<std::string>& inputs){
    if(method == "TRANS_BIN_ZN_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Integer result = m_extra.TRANS_BIN_ZN_Z(a, b);
        return m_parser.toString(result);
    }
    else if(method == "TRANS_DECFAC_Z_Z"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer result = m_extra.TRANS_DECFAC_Z_Z(a);
        return m_parser.toString(result);
    }
    else if(method == "TRANS_FACDEC_Z_Z"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Integer result = m_extra.TRANS_FACDEC_Z_Z(a);
        return m_parser.toString(result);
    }
    else if(method == "FINDOUT_LUCKYNUMBER_N_B"){
        if(inputs.size() < 1) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[0]);
        bool result = m_extra.FINDOUT_LUCKYNUMBER_N_B(a);
        return result ? "Счастливое" : "Несчастливое";
    }
    else if(method == "EXP_ZN_Z"){
        if(inputs.size() < 2) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Integer a = m_parser.parseInteger(inputs[0]);
        Natural b = m_parser.parseNatural(inputs[1]);
        Integer result = m_extra.EXP_ZN_Z(a, b);
        return m_parser.toString(result);
    }
    else if(method == "TRANS_PQ_STRNN_STR"){
        if(inputs.size() < 3) throw std::invalid_argument("Вы ввели слишком мало операндов!");
        Natural a = m_parser.parseNatural(inputs[1]);
        Natural b = m_parser.parseNatural(inputs[2]);
        return m_extra.TRANS_PQ_STRNN_STR(m_parser.TRANS_PQ_STRNN_STR(inputs[0], &a),a, b);
    }
    
    else throw std::invalid_argument("Неизвестный метод!");
}
