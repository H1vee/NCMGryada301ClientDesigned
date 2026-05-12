/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QLabel *TopIcon;
    QLabel *TopLabel;
    QComboBox *PointComboBox;
    QLabel *Loginlabel;
    QLineEdit *LoginEdit;
    QLabel *PasswordLabel;
    QLineEdit *PasswordEdit;
    QLabel *OTPLabel;
    QLineEdit *OTPEdit;
    QCheckBox *ShowOTPCheckBox;
    QCheckBox *ShowPasswordCheckBox;
    QPushButton *CancelButton;
    QPushButton *OKButton;
    QFrame *frame;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(501, 203);
        TopIcon = new QLabel(Login);
        TopIcon->setObjectName("TopIcon");
        TopIcon->setGeometry(QRect(20, 10, 31, 32));
        TopIcon->setAutoFillBackground(false);
        TopIcon->setStyleSheet(QString::fromUtf8(""));
        TopIcon->setTextFormat(Qt::AutoText);
        TopIcon->setPixmap(QPixmap(QString::fromUtf8(":/img/SIm2/UserNetDevice.png")));
        TopIcon->setScaledContents(true);
        TopIcon->setWordWrap(false);
        TopIcon->setOpenExternalLinks(false);
        TopLabel = new QLabel(Login);
        TopLabel->setObjectName("TopLabel");
        TopLabel->setGeometry(QRect(60, 20, 201, 18));
        QFont font;
        font.setPointSize(10);
        TopLabel->setFont(font);
        TopLabel->setStyleSheet(QString::fromUtf8(""));
        PointComboBox = new QComboBox(Login);
        PointComboBox->setObjectName("PointComboBox");
        PointComboBox->setGeometry(QRect(20, 50, 250, 21));
        PointComboBox->setStyleSheet(QString::fromUtf8(""));
        Loginlabel = new QLabel(Login);
        Loginlabel->setObjectName("Loginlabel");
        Loginlabel->setGeometry(QRect(20, 73, 211, 18));
        Loginlabel->setFont(font);
        Loginlabel->setStyleSheet(QString::fromUtf8(""));
        LoginEdit = new QLineEdit(Login);
        LoginEdit->setObjectName("LoginEdit");
        LoginEdit->setGeometry(QRect(20, 90, 250, 21));
        LoginEdit->setStyleSheet(QString::fromUtf8(""));
        PasswordLabel = new QLabel(Login);
        PasswordLabel->setObjectName("PasswordLabel");
        PasswordLabel->setGeometry(QRect(20, 113, 131, 18));
        PasswordLabel->setFont(font);
        PasswordLabel->setStyleSheet(QString::fromUtf8(""));
        PasswordEdit = new QLineEdit(Login);
        PasswordEdit->setObjectName("PasswordEdit");
        PasswordEdit->setGeometry(QRect(20, 130, 250, 21));
        PasswordEdit->setStyleSheet(QString::fromUtf8(""));
        PasswordEdit->setEchoMode(QLineEdit::Password);
        OTPLabel = new QLabel(Login);
        OTPLabel->setObjectName("OTPLabel");
        OTPLabel->setGeometry(QRect(20, 150, 111, 18));
        OTPLabel->setFont(font);
        OTPLabel->setStyleSheet(QString::fromUtf8(""));
        OTPEdit = new QLineEdit(Login);
        OTPEdit->setObjectName("OTPEdit");
        OTPEdit->setGeometry(QRect(20, 170, 149, 21));
        OTPEdit->setStyleSheet(QString::fromUtf8(""));
        ShowOTPCheckBox = new QCheckBox(Login);
        ShowOTPCheckBox->setObjectName("ShowOTPCheckBox");
        ShowOTPCheckBox->setGeometry(QRect(180, 170, 121, 24));
        ShowOTPCheckBox->setFont(font);
        ShowOTPCheckBox->setStyleSheet(QString::fromUtf8(""));
        ShowOTPCheckBox->setChecked(true);
        ShowPasswordCheckBox = new QCheckBox(Login);
        ShowPasswordCheckBox->setObjectName("ShowPasswordCheckBox");
        ShowPasswordCheckBox->setGeometry(QRect(280, 130, 111, 24));
        ShowPasswordCheckBox->setFont(font);
        ShowPasswordCheckBox->setStyleSheet(QString::fromUtf8(""));
        CancelButton = new QPushButton(Login);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(410, 140, 86, 22));
        CancelButton->setFont(font);
        CancelButton->setStyleSheet(QString::fromUtf8(""));
        OKButton = new QPushButton(Login);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(410, 170, 86, 22));
        OKButton->setFont(font);
        OKButton->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(Login);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(388, 50, 20, 141));
        frame->setFrameShape(QFrame::VLine);
        frame->setFrameShadow(QFrame::Plain);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "\320\237\321\226\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\217 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260", nullptr));
        TopIcon->setText(QString());
        TopLabel->setText(QCoreApplication::translate("Login", "\320\237\321\226\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\217 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260", nullptr));
        Loginlabel->setText(QCoreApplication::translate("Login", "\320\241\320\272\320\276\321\200\320\276\321\207\320\265\320\275\320\265 \321\226\320\274'\321\217 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260:", nullptr));
        PasswordLabel->setText(QCoreApplication::translate("Login", "\320\237\320\260\321\200\320\276\320\273\321\214 \320\264\320\276\321\201\321\202\321\203\320\277\321\203:", nullptr));
        OTPLabel->setText(QCoreApplication::translate("Login", "OTP-\320\277\320\260\321\200\320\276\320\273\321\214:", nullptr));
        ShowOTPCheckBox->setText(QCoreApplication::translate("Login", "\320\222\321\226\320\264\320\276\320\261\321\200\320\260\320\266\320\260\321\202\320\270", nullptr));
        ShowPasswordCheckBox->setText(QCoreApplication::translate("Login", "\320\222\321\226\320\264\320\276\320\261\321\200\320\260\320\266\320\260\321\202\320\270", nullptr));
        CancelButton->setText(QCoreApplication::translate("Login", "\320\222\321\226\320\264\320\274\321\226\320\275\320\260", nullptr));
        OKButton->setText(QCoreApplication::translate("Login", "\320\236\320\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
