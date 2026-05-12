/********************************************************************************
** Form generated from reading UI file 'changepassword.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGEPASSWORD_H
#define UI_CHANGEPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ChangePassword
{
public:
    QLabel *HeaderImage;
    QLabel *TopLabel;
    QLabel *label_3;
    QLineEdit *PasswordEdit;
    QLabel *label_4;
    QLineEdit *PasswordRepeatEdit;
    QCheckBox *ShowPasswordCheckBox;
    QPushButton *CancelButton;
    QPushButton *OKButton;
    QFrame *frame;

    void setupUi(QDialog *ChangePassword)
    {
        if (ChangePassword->objectName().isEmpty())
            ChangePassword->setObjectName("ChangePassword");
        ChangePassword->resize(542, 132);
        ChangePassword->setStyleSheet(QString::fromUtf8(""));
        HeaderImage = new QLabel(ChangePassword);
        HeaderImage->setObjectName("HeaderImage");
        HeaderImage->setGeometry(QRect(20, 10, 31, 32));
        HeaderImage->setStyleSheet(QString::fromUtf8(""));
        HeaderImage->setPixmap(QPixmap(QString::fromUtf8(":/img/SIm2/UserLock.png")));
        HeaderImage->setScaledContents(true);
        TopLabel = new QLabel(ChangePassword);
        TopLabel->setObjectName("TopLabel");
        TopLabel->setGeometry(QRect(60, 20, 271, 16));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sans Serif")});
        font.setPointSize(10);
        TopLabel->setFont(font);
        label_3 = new QLabel(ChangePassword);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 45, 201, 18));
        QFont font1;
        font1.setPointSize(10);
        label_3->setFont(font1);
        PasswordEdit = new QLineEdit(ChangePassword);
        PasswordEdit->setObjectName("PasswordEdit");
        PasswordEdit->setGeometry(QRect(20, 65, 285, 16));
        label_4 = new QLabel(ChangePassword);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 85, 201, 18));
        label_4->setFont(font1);
        PasswordRepeatEdit = new QLineEdit(ChangePassword);
        PasswordRepeatEdit->setObjectName("PasswordRepeatEdit");
        PasswordRepeatEdit->setGeometry(QRect(20, 105, 285, 16));
        PasswordRepeatEdit->setEchoMode(QLineEdit::EchoMode::Password);
        ShowPasswordCheckBox = new QCheckBox(ChangePassword);
        ShowPasswordCheckBox->setObjectName("ShowPasswordCheckBox");
        ShowPasswordCheckBox->setGeometry(QRect(315, 58, 111, 31));
        ShowPasswordCheckBox->setFont(font1);
        CancelButton = new QPushButton(ChangePassword);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(440, 66, 86, 22));
        CancelButton->setFont(font1);
        OKButton = new QPushButton(ChangePassword);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(440, 98, 86, 22));
        OKButton->setFont(font1);
        frame = new QFrame(ChangePassword);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(420, 50, 20, 70));
        frame->setFrameShape(QFrame::Shape::VLine);
        frame->setFrameShadow(QFrame::Shadow::Plain);

        retranslateUi(ChangePassword);

        QMetaObject::connectSlotsByName(ChangePassword);
    } // setupUi

    void retranslateUi(QDialog *ChangePassword)
    {
        ChangePassword->setWindowTitle(QCoreApplication::translate("ChangePassword", "\320\227\320\274\321\226\320\275\320\260 \320\277\320\260\321\200\320\276\320\273\321\217 \320\264\320\276\321\201\321\202\321\203\320\277\321\203 ", nullptr));
        HeaderImage->setText(QString());
        TopLabel->setText(QCoreApplication::translate("ChangePassword", "\320\227\320\274\321\226\320\275\320\260 \320\277\320\260\321\200\320\276\320\273\321\217 \320\264\320\276\321\201\321\202\321\203\320\277\321\203 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("ChangePassword", "\320\235\320\276\320\262\320\270\320\271 \320\277\320\260\321\200\320\276\320\273\321\214 \320\264\320\276\321\201\321\202\321\203\320\277\321\203:", nullptr));
        label_4->setText(QCoreApplication::translate("ChangePassword", "\320\237\320\276\320\262\321\202\320\276\321\200 \320\277\320\260\321\200\320\276\320\273\321\217:", nullptr));
        PasswordRepeatEdit->setText(QString());
        ShowPasswordCheckBox->setText(QCoreApplication::translate("ChangePassword", "\320\222\321\226\320\264\320\276\320\261\321\200\320\260\320\266\320\260\321\202\320\270", nullptr));
        CancelButton->setText(QCoreApplication::translate("ChangePassword", "\320\222\321\226\320\264\320\274\321\226\320\275\320\260", nullptr));
        OKButton->setText(QCoreApplication::translate("ChangePassword", "\320\236\320\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChangePassword: public Ui_ChangePassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGEPASSWORD_H
