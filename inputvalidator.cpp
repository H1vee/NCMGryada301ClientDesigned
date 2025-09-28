#include "inputvalidator.h"

#include <QMessageBox>

void InputValidator::showWarning(QWidget *parent, const QString &title, const QString &message, QLineEdit *widget) {
    QMessageBox msgBox;
    msgBox.warning(parent, title, message);
    widget->setFocus();
}


bool InputValidator::validateInput(QLineEdit *widget, QWidget *parent, const QString &title, const QString &emptyMessage, const std::function<bool(const QString &)> &checkFunction, const QString &invalidMessage) {
    if (widget->text().isEmpty()) {
        showWarning(parent, title, emptyMessage, widget);
        return false;
    }
    if (!checkFunction(widget->text())) {
        showWarning(parent, title, invalidMessage, widget);
        return false;
    }
    return true;
}
