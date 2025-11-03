#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <vector>
#include <string>

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    InputDialog(const std::string& methodName,
                const std::string& dataType,
                int operandCount,
                QWidget* parent = nullptr);

    std::vector<std::string> getInputs() const;
    std::string getMethodName() const;

private:
    std::string m_methodName;
};

#endif // INPUTDIALOG_H
