#include "inputdialog.h"

InputDialog::InputDialog(const std::string&,
                         const std::string&,
                         int,
                         QWidget*)
{
    // Пустая реализация
}

std::vector<std::string> InputDialog::getInputs() const
{
    return std::vector<std::string>(); // Пустой вектор
}

std::string InputDialog::getMethodName() const
{
    return m_methodName;
}
