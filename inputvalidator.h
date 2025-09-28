#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <functional>
#include <QLineEdit>
#include <QWidget>

class InputValidator {
public:
    static void showWarning(QWidget* parent,const QString& title, const QString& message,QLineEdit* widget);
    static bool validateInput(QLineEdit* widget, QWidget* parent, const QString& title,
                              const QString& emptyMessage,
                              const std::function<bool(const QString&)>& checkFunction,
                              const QString& invalidMessage);
};
#endif //INPUTVALIDATOR_H
