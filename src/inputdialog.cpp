#include "inputdialog.h"

/*
 * Developed by Danil Babin group 4381
 * InputDialog - реализация диалогового окна ввода параметров
 */

/**
 * @brief Конструктор диалога ввода параметров
 * @param methodName Техническое имя математического метода
 * @param dataType Тип обрабатываемых данных
 * @param operandCount Количество требуемых операндов
 * @param parent Родительский виджет
 *
 * Инициализирует диалоговое окно с полями ввода, соответствующими
 * выбранной математической операции и типу данных.
 */
InputDialog::InputDialog(const std::string& methodName,
                         const std::string& dataType,
                         const std::string& russianType,
                         int operandCount,
                         QWidget* parent)
    : QDialog(parent),
    m_methodName(methodName),
    m_dataType(dataType),
    m_russianType(russianType),
    m_operandCount(operandCount),
    m_mainLayout(new QVBoxLayout(this)),
    m_descriptionLabel(new QLabel(this)),
    m_buttonLayout(new QHBoxLayout()),
    m_okButton(new QPushButton("OK", this)),
    m_cancelButton(new QPushButton("Cancel", this))
{
    setupUI();
    setupConnections();
}

/**
 * @brief Настройка пользовательского интерфейса диалога
 *
 * Создает и компонирует все элементы интерфейса: описание операции,
 * поля ввода операндов и кнопки управления. Применяет стили и настраивает
 * параметры окна в зависимости от количества операндов.
 */
void InputDialog::setupUI()
{
    // Применение базового стиля ко всему диалоговому окну
    setStyleSheet(
        "QDialog {"
        "    background-color: #F4FDF9;"      // Согласованный с главным окном фон
        "    color: #2C3E50;"
        "    font-family: 'Segoe UI', Arial;"
        "}"
        );

    // Создание описания операции с параметрами
    QString description = QString("Метод: %1\nТип данных: %2\nВведите %3:")
                              .arg(QString::fromStdString(m_russianType))
                              .arg(QString::fromStdString(m_dataType))
                              .arg(m_operandCount > 1 ? QString::number(m_operandCount) + " операнда" : QString::number(m_operandCount) + " операнд");

    m_descriptionLabel->setText(description);

    // Стилизация метки описания с акцентным оформлением
    m_descriptionLabel->setStyleSheet(
        "QLabel {"
        "    color: #5D6D7E;"
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    padding: 15px;"
        "    background-color: #E8F8F5;"      // Светлый бирюзовый фон
        "    border: 2px solid #76D7C4;"      // Акцентная бирюзовая рамка
        "    border-radius: 10px;"
        "    margin: 10px 0px;"
        "}"
        );
    m_mainLayout->addWidget(m_descriptionLabel);

    // Динамическое создание полей ввода для каждого операнда
    for (int i = 0; i < m_operandCount; ++i) {
        QLabel* label = new QLabel(getOperandLabel(i), this);
        QLineEdit* input = new QLineEdit(this);

        // Установка контекстной подсказки для поля ввода
        input->setPlaceholderText(getOperandPlaceholder(i));

        // Стилизация метки операнда
        label->setStyleSheet(
            "color: #16A085;"      // Бирюзовый цвет для меток
            "font-weight: 600;"
            "padding: 5px 0px;"
            );

        // Стилизация поля ввода с интерактивными состояниями
        input->setStyleSheet(
            "QLineEdit {"
            "    background-color: white;"
            "    border: 2px solid #76D7C4;"  // Согласованная с темой рамка
            "    border-radius: 6px;"
            "    padding: 8px;"
            "    margin-bottom: 10px;"
            "    color: #2C3E50;"
            "}"
            "QLineEdit:focus {"
            "    border-color: #5DADE2;"       // Синий акцент при фокусе
            "    background-color: #F8FDFE;"
            "    color: #2C3E50;"
            "}"
            );

        // Сохранение указателей для дальнейшего управления
        m_inputLabels.push_back(label);
        m_inputFields.push_back(input);

        // Добавление элементов в компоновщик
        m_mainLayout->addWidget(label);
        m_mainLayout->addWidget(input);
    }

    // Стилизация кнопки подтверждения ввода
    m_okButton->setStyleSheet(
        "QPushButton {"
        "    background-color: #76D7C4;"      // Бирюзовый основной цвет
        "    color: white;"
        "    border: none;"
        "    padding: 10px 20px;"
        "    border-radius: 6px;"
        "    font-weight: 600;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "    min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5DADE2;"      // Синий при наведении
        "}"
        );

    // Стилизация кнопки отмены ввода
    m_cancelButton->setStyleSheet(
        "QPushButton {"
        "    background-color: white;"
        "    color: #5D6D7E;"                 // Нейтральный серый текст
        "    border: 2px solid #BDC3C7;"      // Светлая серая рамка
        "    padding: 10px 20px;"
        "    border-radius: 6px;"
        "    font-weight: 600;"
        "    min-width: 80px;"
        "}"
        "QPushButton:hover {"
        "    border-color: #76D7C4;"          // Бирюзовая рамка при наведении
        "}"
        );

    // Компоновка кнопок с выравниванием по правому краю
    m_buttonLayout->addStretch();              // Растягивающее пространство
    m_buttonLayout->addWidget(m_okButton);
    m_buttonLayout->addWidget(m_cancelButton);
    m_mainLayout->addLayout(m_buttonLayout);

    // Настройка отступов и промежутков для визуального комфорта
    m_mainLayout->setContentsMargins(15, 15, 15, 15);
    m_mainLayout->setSpacing(5);

    // Конфигурация параметров диалогового окна
    setWindowTitle("Ввод параметров");
    setModal(true);                           // Модальный режим работы

    // Адаптивная высота окна в зависимости от количества полей ввода
    int baseHeight = 250;
    int fieldHeight = 70;
    int totalHeight = baseHeight + (m_operandCount * fieldHeight);
    resize(450, totalHeight);

    // Установка фокуса ввода на первое поле для удобства пользователя
    if (!m_inputFields.empty()) {
        m_inputFields[0]->setFocus();
    }
}

/**
 * @brief Применение дополнительных стилей к диалогу
 *
 * Устанавливает визуальное оформление диалогового окна, включая
 * скругление углов и цветовую схему.
 */
void InputDialog::applyStyle()
{
    setStyleSheet(
        "QDialog {"
        "    background-color: #F4FDF9;"
        "    color: #2C3E50;"
        "    font-family: 'Segoe UI', Arial;"
        "    border-radius: 12px;"            // Скругленные углы окна
        "}"
        );
}

/**
 * @brief Настройка сигнально-слотовых соединений
 *
 * Связывает пользовательские действия (нажатия кнопок) с соответствующими
 * обработчиками бизнес-логики.
 */
void InputDialog::setupConnections()
{
    connect(m_okButton, &QPushButton::clicked, this, &InputDialog::onOkClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &InputDialog::onCancelClicked);
}

/**
 * @brief Обработчик нажатия кнопки подтверждения
 *
 * Выполняет валидацию введенных данных и при успешной проверке
 * сохраняет результаты и закрывает диалог с положительным результатом.
 */
void InputDialog::onOkClicked()
{
    if (validateInputs()) {
        // Очистка предыдущих данных перед сохранением новых
        m_inputs.clear();

        // Сохранение введенных значений из всех полей ввода
        for (QLineEdit* field : m_inputFields) {
            m_inputs.push_back(field->text().toStdString());
        }

        // Закрытие диалога с результатом Accepted
        accept();
    }
}

/**
 * @brief Обработчик нажатия кнопки отмены
 *
 * Закрывает диалоговое окно без сохранения введенных данных.
 */
void InputDialog::onCancelClicked()
{
    reject(); // Закрытие диалога с результатом Rejected
}

/**
 * @brief Валидация введенных пользователем данных
 * @return true если все поля заполнены корректно, иначе false
 *
 * Выполняет базовую проверку заполнения полей. В будущем может быть
 * расширена для проверки формата данных в зависимости от типа.
 */
bool InputDialog::validateInputs()
{
    // Проверка что все обязательные поля заполнены
    for (QLineEdit* field : m_inputFields) {
        if (field->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Все поля должны быть заполнены");
            field->setFocus(); // Установка фокуса на незаполненное поле
            return false;
        }
    }

    // Зарезервировано для расширенной валидации формата данных
    // в зависимости от m_dataType и m_methodName

    return true;
}

/**
 * @brief Получение введенных пользователем данных
 * @return Вектор строк с значениями операндов
 */
std::vector<std::string> InputDialog::getInputs() const
{
    return m_inputs;
}

/**
 * @brief Генерация текста метки для операнда
 * @param index Порядковый номер операнда (0-based)
 * @return Текст метки с учетом контекста операции
 *
 * Создает контекстно-зависимые метки для полей ввода, обеспечивая
 * лучшую пользовательскую понятность для специальных операций.
 */
QString InputDialog::getOperandLabel(int index) const
{
    // Специальные случаи для операций со смешанными типами данных
    if (m_methodName == "MUL_PQ_P") {
        if (index == 0) return "Многочлен:";
        else if (index == 1) return "Рациональное число:";
    }
    else if (m_methodName == "DIV_PP_P") {
        if (index == 0) return "Делимое (многочлен):";
        else if (index == 1) return "Делитель (многочлен):";
    }  
    else if(m_methodName == "TRANS_PQ_STRNN_STR"){
        if(index == 0) return "Исходное число";
        else if(index == 1) return "Исходная СС";
        else if(index == 2) return "Целевая СС";
    }
    else if(m_methodName == "EXP_ZN_Z"){
        if(index == 0) return "Исходное число";
        else return "Степень";
    }

    // Стандартная нумерация операндов для большинства операций
    return QString("Операнд %1:").arg(index + 1);
}

/**
 * @brief Генерация подсказки для поля ввода операнда
 * @param index Порядковый номер операнда (0-based)
 * @return Текст подсказки с примерами формата ввода
 *
 * Предоставляет пользователю примеры ожидаемого формата данных
 * в зависимости от типа операции и типа данных.
 */
QString InputDialog::getOperandPlaceholder(int index) const
{
    // Специальные случаи для операций со смешанными типами
    if (m_methodName == "MUL_PQ_P") {
        if (index == 0) return "например: 3x^2 + 2x + 1 или x^3 - 5x";
        if (index == 1) return "например: 2/3 или -5/2 или 7";
    }
    else if(m_methodName == "EXP_ZN_Z") {
        if(index == 0)  return "например: -123 или +456";
        else return "например: 12345";
    }
    else if(m_methodName == "TRANS_PQ_STRNN_STR"){
        if(index == 0) return "например: -123 или +456";
        else if(index == 1) return "например: 12345";
        else return "например: 12345";
    }

    // Общие шаблоны ввода по типам данных
    if (m_dataType == "Natural") return "например: 12345";
    else if (m_dataType == "Integer") return "например: -123 или +456";
    else if (m_dataType == "Rational") return "например: 3/4 или -5/2";
    else if (m_dataType == "Polynomial") return "например: 3x^3 + 2x + 1";
    else if(m_dataType == "Extra Methods") return "например: -123 или +456";

    // Подсказка по умолчанию для неизвестных типов
    return "введите значение";
}
