#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "natural.h"
#include "integer.h"
#include "rational.h"
#include "polynomial.h"
#include "parser.h"
#include <map>
#include <vector>
#include <string>

/**
 * Developed by Danil Babin group 4381
 * @class Controller
 * @brief Основной контроллер системы компьютерной алгебры
 *
 * Управляет выполнением математических операций для различных типов данных,
 * предоставляет интерфейс для доступа к доступным операциям и их описаниям.
 */
class Controller {
public:
    /**
     * @brief Конструктор контроллера
     *
     * Инициализирует доступные операции и их метаданные.
     */
    Controller();

    /**
     * @brief Получить список доступных типов данных
     * @return Вектор строк с названиями типов данных
     */
    std::vector<std::string> getAvailableTypes() const;

    /**
     * @brief Получить список методов для конкретного типа
     * @param type Тип данных для которого запрашиваются методы
     * @return Вектор строк с техническими именами методов
     */
    std::vector<std::string> getMethodsForType(const std::string& type) const;

    /**
     * @brief Получить количество операндов для метода
     * @param method Техническое имя метода
     * @return Количество требуемых операндов
     */
    int getOperandCount(const std::string& method) const;

    /**
     * @brief Получить описание метода
     * @param method Техническое имя метода
     * @return Человеко-читаемое описание метода
     */
    std::string getMethodDescription(const std::string& method) const;

    /**
     * @brief Выполнить математическую операцию
     * @param type Тип данных для операции
     * @param method Техническое имя метода
     * @param inputs Вектор входных данных
     * @return Результат выполнения операции в строковом представлении
     */
    std::string executeOperation(const std::string& type,
                                 const std::string& method,
                                 const std::vector<std::string>& inputs);

private:
	Parser m_parser;													///< Объект парсера
    // Контейнеры для хранения метаданных операций
    std::map<std::string, std::vector<std::string>> m_typeMethods;      ///< Соответствие типов данных и доступных методов
    std::map<std::string, int> m_methodOperands;                        ///< Количество операндов для каждого метода
    std::map<std::string, std::string> m_methodDescriptions;            ///< Описания методов
    std::map<std::string, std::string> m_methodDisplayNames;            ///< Отображаемые имена методов

    /**
     * @brief Инициализация доступных операций
     *
     * Заполняет контейнеры метаданными всех поддерживаемых операций.
     */
    void initializeOperations();

    // Методы выполнения операций по типам данных
    std::string executeNaturalOperation(const std::string& method, const std::vector<std::string>& inputs);    ///< Операции с натуральными числами
    std::string executeIntegerOperation(const std::string& method, const std::vector<std::string>& inputs);    ///< Операции с целыми числами
    std::string executeRationalOperation(const std::string& method, const std::vector<std::string>& inputs);   ///< Операции с рациональными числами
    std::string executePolynomialOperation(const std::string& method, const std::vector<std::string>& inputs); ///< Операции с многочленами
};

#endif // CONTROLLER_H
