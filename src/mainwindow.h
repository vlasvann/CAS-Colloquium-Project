#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QListWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "controller.h"

/**
 * Developed by Danil Babin group 4381
 * @class MainWindow
 * @brief Главное окно приложения системы компьютерной алгебры
 *
 * Обеспечивает пользовательский интерфейс для выбора математических операций,
 * ввода параметров и отображения результатов вычислений.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор главного окна
     * @param parent Родительский виджет (по умолчанию nullptr)
     */
    MainWindow(QWidget *parent = nullptr);

private slots:
    // Слоты обработки пользовательских действий
    void onTypeSelected();           ///< Обработчик выбора типа данных
    void onMethodSelected();         ///< Обработчик выбора математического метода
    void onExecuteClicked();         ///< Обработчик нажатия кнопки выполнения операции

    // Слоты обновления интерфейса
    void updateMethodList();         ///< Обновление списка доступных методов для выбранного типа

private:
    // Методы настройки интерфейса
    void setupUI();                  ///< Инициализация и компоновка элементов интерфейса
    void setupConnections();         ///< Настройка сигнально-слотовых соединений

    // Методы бизнес-логики
    void showWelcomeDialog();        ///< Отображение текста с обзором программы
    void showInputDialog();          ///< Отображение диалога ввода параметров операции
    void displayResult(const std::string& result); ///< Отображение результата вычислений
    void displayError(const std::string& error);   ///< Отображение сообщения об ошибке

    // Бизнес-логика приложения
    Controller m_controller;         ///< Контроллер для выполнения математических операций

    // Иерархия виджетов интерфейса
    QWidget* m_centralWidget;        ///< Центральный виджет-контейнер
    QVBoxLayout* m_mainLayout;       ///< Главный вертикальный компоновщик

    // Группа элементов выбора типа данных
    QComboBox* m_typeComboBox;       ///< Комбобокс выбора типа данных (Natural/Integer/Rational/Polynomial)
    QLabel* m_typeLabel;             ///< Метка для комбобокса типа данных

    // Группа элементов выбора метода
    QListWidget* m_methodListWidget; ///< Список доступных математических методов
    QLabel* m_methodLabel;           ///< Метка для списка методов

    // Элементы управления
    QPushButton* m_executeButton;    ///< Кнопка выполнения выбранной операции

    // Группа элементов отображения результатов
    QTextEdit* m_resultTextEdit;     ///< Текстовое поле для вывода результатов вычислений
    QLabel* m_resultLabel;           ///< Метка для поля результатов

    // Текущее состояние приложения
    std::string m_currentType;       ///< Выбранный тип данных (копия для избежания зависимостей от UI)
    std::string m_currentMethod;     ///< Выбранный математический метод (копия для избежания зависимостей от UI)
};

#endif // MAINWINDOW_H
