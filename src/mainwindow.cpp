#include "mainwindow.h"
#include "inputdialog.h"
#include <stdexcept>

/*
 * Developed by Danil Babin group 4381
 * MainWindow - реализация главного окна системы компьютерной алгебры
 */

/**
 * @brief Конструктор главного окна приложения
 * @param parent Родительский виджет
 *
 * Инициализирует все компоненты пользовательского интерфейса и настраивает
 * начальное состояние приложения.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_controller(),
    m_centralWidget(new QWidget(this)),
    m_mainLayout(new QVBoxLayout(m_centralWidget)),
    m_typeComboBox(new QComboBox(this)),
    m_typeLabel(new QLabel("Выберите тип данных:", this)),
    m_methodListWidget(new QListWidget(this)),
    m_methodLabel(new QLabel("Выберите метод:", this)),
    m_executeButton(new QPushButton("Выполнить", this)),
    m_resultTextEdit(new QTextEdit(this)),
    m_resultLabel(new QLabel("Результат:", this))
{
    setupUI();
    setupConnections();

    // Инициализация комбобокса доступными типами данных
    auto types = m_controller.getAvailableTypes();
    for (const auto& type : types) {
        m_typeComboBox->addItem(QString::fromStdString(type));
    }

    m_executeButton->setEnabled(false);  ///< Кнопка неактивна до выбора метода
    m_resultTextEdit->setReadOnly(true); ///< Поле результатов только для чтения
    showWelcomeDialog();
}

/**
 * @brief Настройка пользовательского интерфейса
 *
 * Конфигурирует визуальные компоненты, применяет стили и компоновку,
 * устанавливает параметры главного окна.
 */
void MainWindow::setupUI()
{
    setCentralWidget(m_centralWidget);

    // Применение кастомных стилей для согласованного внешнего вида
    setStyleSheet(
        "QMainWindow {"
        "    background-color: #F4FDF9;"      ///< Основной фон приложения
        "    color: #2C3E50;"                 ///< Основной цвет текста
        "    font-family: 'Segoe UI', Arial;" ///< Шрифтовая гарнитура
        "}"
        "QLabel {"
        "    color: #6C7A89;"                 ///< Цвет меток
        "    font-size: 14px;"
        "    font-weight: 500;"
        "    padding: 5px 0px;"
        "}"
        "QComboBox {"
        "    background-color: #FFFFFF;"
        "    color: #2C3E50;"
        "    border: 2px solid #76D7C4;"      ///< Акцентная бирюзовая рамка
        "    border-radius: 8px;"
        "    padding: 10px 15px;"
        "    font-family: 'Segoe UI', Arial;"
        "    font-size: 14px;"
        "    font-weight: 400;"
        "}"
        "QComboBox::drop-down {"
        "    border: none;"
        "    width: 25px;"
        "    background-color: #76D7C4;"      ///< Цвет стрелки комбобокса
        "    border-radius: 0px 6px 6px 0px;"
        "    font-family: 'Segoe UI', Arial;"
        "    font-size: 12px;"
        "    font-weight: 600;"
        "}"
        "QListWidget {"
        "    background-color: #FFFFFF;"
        "    color: #2C3E50;"
        "    border: 2px solid #EAFAF1;"      ///< Светлая бирюзовая рамка
        "    border-radius: 10px;"
        "    font-family: 'Segoe UI', Arial;"
        "    font-size: 12px;"
        "    font-weight: 500;"
        "}"
        "QListWidget::item:selected {"
        "    background-color: #76D7C4;"      ///< Цвет выделенного элемента
        "    color: white;"
        "    border-radius: 6px;"
        "}"
        "QTextEdit {"
        "    background-color: #FFFFFF;"
        "    color: #2C3E50;"
        "    border: 2px solid #EAFAF1;"
        "    border-radius: 10px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;" ///< Моноширинный шрифт для результатов
        "    padding: 12px;"
        "}"
        );

    // Стилизация кнопки выполнения с градиентным эффектом
    m_executeButton->setStyleSheet(
        "QPushButton {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #76D7C4, stop:1 #5DADE2);" ///< Градиент от бирюзового к синему
        "    color: white;"
        "    border: none;"
        "    padding: 12px 25px;"
        "    border-radius: 8px;"
        "    font-weight: 600;"
        "    font-size: 14px;"
        "    font-family: 'Segoe UI', Arial, sans-serif;"
        "}"
        "QPushButton:hover {"
        "    background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "        stop:0 #5DADE2, stop:1 #48C9B0);" ///< Инверсный градиент при наведении
        "}"
        "QPushButton:pressed {"
        "    background-color: #45B39D;"      ///< Темный оттенок при нажатии
        "}"
        );

    // Компоновка элементов интерфейса в вертикальном layout
    m_mainLayout->addWidget(m_typeLabel);
    m_mainLayout->addWidget(m_typeComboBox);
    m_mainLayout->addWidget(m_methodLabel);
    m_mainLayout->addWidget(m_methodListWidget);
    m_mainLayout->addWidget(m_executeButton);
    m_mainLayout->addWidget(m_resultLabel);
    m_mainLayout->addWidget(m_resultTextEdit);

    // Настройка параметров главного окна
    setWindowTitle("Система компьютерной алгебры");
    resize(700, 600); ///< Начальный размер окна
}

/**
 * @brief Настройка сигнально-слотовых соединений
 *
 * Устанавливает связи между пользовательскими действиями и обработчиками
 * для обеспечения интерактивности интерфейса.
 */
void MainWindow::setupConnections()
{
    // Соединение изменения выбора типа данных с обновлением списка методов
    connect(m_typeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onTypeSelected);

    // Соединение выбора метода с активацией кнопки выполнения
    connect(m_methodListWidget, &QListWidget::itemSelectionChanged,
            this, &MainWindow::onMethodSelected);

    // Соединение нажатия кнопки с выполнением операции
    connect(m_executeButton, &QPushButton::clicked,
            this, &MainWindow::onExecuteClicked);
}

/**
 * @brief Показ диалога приветствия
 *
 * Отображает приветственное сообщение и скрывает ненужные элементы интерфейса.
 */
void MainWindow::showWelcomeDialog()
{
    m_methodLabel->setVisible(false);
    m_methodListWidget->setVisible(false);
    m_executeButton->setVisible(false);
    m_resultLabel->setVisible(false);

    // Показать приветствие в поле результатов
    m_resultTextEdit->setVisible(true);
    m_resultTextEdit->setHtml(
        "<div style='text-align: center; font-family: \"Segoe UI\", Arial; color: #2C3E50;'>"
        "<h1 style='color: #76D7C4; margin-bottom: 20px;'>СИСТЕМА КОМПЬЮТЕРНОЙ АЛГЕБРЫ</h1>"
        "<h2 style='margin-bottom: 30px;'>Добро пожаловать!</h2>"
        "<p style='font-size: 16px; line-height: 1.6; text-align: left; margin: 20px;'>"
        "Эта система предоставляет комплексные возможности для работы с различными математическими объектами:"
        "</p>"
        "<ul style='font-size: 14px; line-height: 1.8; text-align: left; margin: 20px;'>"
        "<li><b>Натуральные числа</b> произвольной длины</li>"
        "<li><b>Целые числа</b> с поддержкой больших значений</li>"
        "<li><b>Рациональные числа</b> и дроби</li>"
        "<li><b>Многочлены</b> с рациональными коэффициентами</li>"
        "</ul>"
        "<p style='font-size: 14px; line-height: 1.6; text-align: left; margin: 20px;'>"
        "Система реализует полный набор математических операций — от базовых арифметических действий "
        "до продвинутых алгебраических преобразований."
        "</p>"
        "<p style='font-size: 16px; color: #76D7C4; font-weight: bold; margin-top: 30px;'>"
        "Для начала работы выберите тип данных и операцию в меню выше."
        "</p>"
        "<p style='font-size: 14px; color: #5DADE2; margin-top: 20px;'>"
        "Приятной работы с математическими вычислениями! 🚀"
        "</p>"
        "</div>"
        );
}

/**
 * @brief Обработчик выбора типа данных
 *
 * Вызывается при изменении выбора в комбобоксе типов данных.
 * Обновляет список доступных методов и сбрасывает состояние интерфейса.
 */
void MainWindow::onTypeSelected()
{
    // Получить выбранный тип данных из UI
    m_currentType = m_typeComboBox->currentText().toStdString();

    if(m_currentType == "Greeting") {
        showWelcomeDialog();
        m_methodListWidget->clear();
        m_currentMethod.clear();             ///< Очистить выбранный метод
        m_executeButton->setEnabled(false);  ///< Деактивировать кнопку выполнения
    }
    else {
        m_methodLabel->setVisible(true);
        m_methodListWidget->setVisible(true);
        m_executeButton->setVisible(true);
        m_resultLabel->setVisible(true);
        updateMethodList();
        m_currentMethod.clear();             ///< Очистить выбранный метод
        m_executeButton->setEnabled(false);  ///< Деактивировать кнопку выполнения
        m_resultTextEdit->clear();           ///< Очистить поле результатов
    }
}

/**
 * @brief Обработчик выбора математического метода
 *
 * Вызывается при выборе элемента в списке методов.
 * Активирует кнопку выполнения и сохраняет выбранный метод.
 */
void MainWindow::onMethodSelected()
{
    // Проверка наличия выбранного элемента
    if (m_methodListWidget->selectedItems().isEmpty()) {
        m_executeButton->setEnabled(false);
        return;
    }

    // Извлечение технического имени метода из данных элемента
    QListWidgetItem* selectedItem = m_methodListWidget->currentItem();
    m_currentMethod = selectedItem->data(Qt::UserRole).toString().toStdString();

    // Активация кнопки выполнения
    m_executeButton->setEnabled(true);
}

/**
 * @brief Обработчик нажатия кнопки выполнения
 *
 * Выполняет проверку корректности выбора и инициирует процесс вычислений
 * через диалог ввода параметров.
 */
void MainWindow::onExecuteClicked()
{
    // Валидация выбора типа данных и метода
    if (m_currentType.empty() || m_currentMethod.empty()) {
        displayError("Не выбран тип данных или метод");
        return;
    }

    // Отображение диалога ввода параметров для выбранной операции
    showInputDialog();
}

/**
 * @brief Обновление списка доступных методов
 *
 * Загружает и отображает список математических методов для выбранного типа данных,
 * используя человеко-читаемые названия из контроллера.
 */
void MainWindow::updateMethodList()
{
    // Очистка предыдущего списка методов
    m_methodListWidget->clear();

    // Получение списка методов для текущего типа данных
    auto methods = m_controller.getMethodsForType(m_currentType);

    // Заполнение списка методов с человеко-читаемыми названиями
    for (const std::string& method : methods) {
        QString methodStr = QString::fromStdString(method);
        QString displayName = QString::fromStdString(
            m_controller.getMethodDescription(method)
            );

        // Создание элемента списка с отображаемым именем
        QListWidgetItem* item = new QListWidgetItem(displayName);

        // Сохранение технического имени в пользовательских данных
        item->setData(Qt::UserRole, methodStr);

        // Добавление элемента в список
        m_methodListWidget->addItem(item);
    }
}

/**
 * @brief Отображение диалога ввода параметров
 *
 * Создает и показывает модальный диалог для ввода параметров выбранной
 * математической операции, обрабатывает результаты ввода.
 */
void MainWindow::showInputDialog()
{
    // Определение количества требуемых операндов
    int operandCount = m_controller.getOperandCount(m_currentMethod);
    std::string m_currentRussianType = m_controller.getMethodDescription(m_currentMethod);

    // Создание диалога ввода параметров
    InputDialog dialog(m_currentMethod, m_currentType, m_currentRussianType, operandCount, this);

    // Обработка результата диалога
    if (dialog.exec() == QDialog::Accepted) {
        try {
            // Получение введенных пользователем данных
            std::vector<std::string> inputs = dialog.getInputs();

            // Выполнение математической операции через контроллер
            std::string result = m_controller.executeOperation(
                m_currentType, m_currentMethod, inputs);

            // Отображение результата вычислений
            displayResult(result);

        } catch (const std::exception& e) {
            // Обработка и отображение ошибок выполнения
            displayError(e.what());
        }
    }
}

/**
 * @brief Отображение результата вычислений
 * @param result Строка с результатом для отображения
 */
void MainWindow::displayResult(const std::string& result)
{
    m_resultTextEdit->setPlainText(QString::fromStdString(result));
}

/**
 * @brief Отображение сообщения об ошибке
 * @param error Текст ошибки для отображения
 */
void MainWindow::displayError(const std::string& error)
{
    QMessageBox::critical(this, "Ошибка", QString::fromStdString(error));
}
