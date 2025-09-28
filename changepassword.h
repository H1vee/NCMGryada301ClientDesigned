#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QMessageBox>
#include "inputvalidator.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = nullptr);
    ~ChangePassword();

    QString getPassword() const;
    void    setPassword(const QString &password);

private slots:
    void OKButtonClick();
    void ShowPasswordCheckBoxClick();
    void PasswordEditChange();

private:
    Ui::ChangePassword *ui;


    QString m_currentPassword;
    QString m_resultPassword;
};

#endif // CHANGEPASSWORD_H
