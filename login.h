#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>



#include "inputvalidator.h"
#include "Gryada301.h"
#include "./Settings/NCMsList.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QString getLogin() const;
    QString getPassword() const;
    QString getOTP() const;
    int getPoint() const;

private slots:
    void OKButtonClick();
    void ShowOTPCheckBoxClick();
    void ShowPasswordCheckBoxClick();

private:
    Ui::Login *ui;

    void setupLogin();

    QString m_login;
    QString m_password;
    QString m_otp;
    int m_point;
};

#endif // LOGIN_H
