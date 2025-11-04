#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <vector>
#include <string>
#include <QString>

/**
 * Developed by Danil Babin group 4381
 * @class InputDialog
 * @brief Диалоговое окно для ввода параметров математических операций
 *
 * Предоставляет интерфейс для ввода операндов в зависимости от выбранного
 * типа данных и математической операции.
 */
class InputDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор диалога ввода параметров
     * @param methodName Техническое имя математического метода
     * @param dataType Тип данных (Natural/Integer/Rational/Polynomial)
     * @param operandCount Количество требуемых операндов
     * @param parent Родительский виджет
     */
    InputDialog(const std::string& methodName,
                const std::string& dataType,
                const std::string& russianType,
                int operandCount,
                QWidget* parent = nullptr);

    /**
     * @brief Получить введенные пользователем данные
     * @return Вектор строк с введенными значениями операндов
     */
    std::vector<std::string> getInputs() const;

    /**
     * @brief Получить выбранный метод
     * @return Техническое имя математического метода
     */
    std::string getMethodName() const { return m_methodName; }

private slots:
    void onOkClicked();    ///< Обработчик подтверждения ввода
    void onCancelClicked(); ///< Обработчик отмены ввода

private:
    // Методы настройки интерфейса
    void setupUI();        ///< Инициализация и компоновка элементов интерфейса
    void setupConnections(); ///< Настройка сигнально-слотовых соединений
    void applyStyle();     ///< Применение стилей к элементам интерфейса

    // Методы валидации и вспомогательные
    bool validateInputs(); ///< Проверка корректности введенных данных
    QString getOperandLabel(int index) const;     ///< Генерация текста метки операнда
    QString getOperandPlaceholder(int index) const; ///< Генерация подсказки для поля ввода

    // Данные контекста операции
    std::string m_methodName;   ///< Техническое имя математического метода
    std::string m_dataType;     ///< Тип обрабатываемых данных
    std::string m_russianType;  ///< Тип обрабатываемых данных на русском языке
    int m_operandCount;         ///< Количество требуемых операндов

    // Иерархия виджетов интерфейса
    QVBoxLayout* m_mainLayout;  ///< Главный вертикальный компоновщик
    QLabel* m_descriptionLabel; ///< Метка с описанием операции
    std::vector<QLabel*> m_inputLabels;     ///< Вектор меток для полей ввода
    std::vector<QLineEdit*> m_inputFields;  ///< Вектор полей для ввода данных

    // Элементы управления
    QHBoxLayout* m_buttonLayout; ///< Горизонтальный компоновщик для кнопок
    QPushButton* m_okButton;     ///< Кнопка подтверждения ввода
    QPushButton* m_cancelButton; ///< Кнопка отмены ввода

    // Данные состояния
    std::vector<std::string> m_inputs; ///< Буфер для хранения введенных данных
};

#endif // INPUTDIALOG_H
