/********************************************************************************
** Form generated from reading UI file 'clientsecurity.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTSECURITY_H
#define UI_CLIENTSECURITY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientSecurity
{
public:
    QLabel *HeaderLabel;
    QLabel *HeaderImage;
    QPushButton *OKButton;
    QCheckBox *CantChangePasswordCheckBox;
    QCheckBox *MustChangePasswordCheckBox;
    QCheckBox *MustUseOTPCheckBox;
    QCheckBox *DenyOthersPasswordChangeCheckBox;
    QCheckBox *OTPInUseCheckBox;
    QPushButton *CancelButton;
    QWidget *OTPWidget;
    QLabel *OTPParametersLabel;
    QLabel *OTPQRCodeImage;
    QLabel *OTPQRCodeLabel;
    QLabel *OTPParamsNoteLabel;
    QPushButton *OTPKeyRegenerateButton;
    QLabel *OTPTimeStepLabel;
    QComboBox *OTPDigitsComboBox;
    QLabel *OTPKeyLabel;
    QLabel *OTPDigitsLabel;
    QPushButton *OTPKeyCopyButton;
    QLabel *OTPParamsNoteImage;
    QLabel *OTPInfoLabel;
    QLineEdit *OTPKeyEdit;
    QComboBox *OTPTimeStepComboBox;
    QFrame *frame;
    QFrame *BottomLine;

    void setupUi(QDialog *ClientSecurity)
    {
        if (ClientSecurity->objectName().isEmpty())
            ClientSecurity->setObjectName("ClientSecurity");
        ClientSecurity->resize(451, 556);
        ClientSecurity->setStyleSheet(QString::fromUtf8(""));
        HeaderLabel = new QLabel(ClientSecurity);
        HeaderLabel->setObjectName("HeaderLabel");
        HeaderLabel->setGeometry(QRect(60, 20, 241, 16));
        QFont font;
        font.setFamilies({QString::fromUtf8("Sans Serif")});
        font.setPointSize(10);
        HeaderLabel->setFont(font);
        HeaderLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        HeaderImage = new QLabel(ClientSecurity);
        HeaderImage->setObjectName("HeaderImage");
        HeaderImage->setGeometry(QRect(20, 10, 31, 32));
        HeaderImage->setStyleSheet(QString::fromUtf8(""));
        HeaderImage->setPixmap(QPixmap(QString::fromUtf8(":/img/SIm2/UserLock.png")));
        HeaderImage->setScaledContents(true);
        OKButton = new QPushButton(ClientSecurity);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(261, 520, 86, 21));
        QFont font1;
        font1.setPointSize(10);
        OKButton->setFont(font1);
        OKButton->setStyleSheet(QString::fromUtf8("color: black;"));
        CantChangePasswordCheckBox = new QCheckBox(ClientSecurity);
        CantChangePasswordCheckBox->setObjectName("CantChangePasswordCheckBox");
        CantChangePasswordCheckBox->setEnabled(false);
        CantChangePasswordCheckBox->setGeometry(QRect(20, 50, 171, 17));
        CantChangePasswordCheckBox->setFont(font1);
        CantChangePasswordCheckBox->setMouseTracking(true);
        CantChangePasswordCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox:disabled { color: gray; }"));
        MustChangePasswordCheckBox = new QCheckBox(ClientSecurity);
        MustChangePasswordCheckBox->setObjectName("MustChangePasswordCheckBox");
        MustChangePasswordCheckBox->setEnabled(false);
        MustChangePasswordCheckBox->setGeometry(QRect(20, 80, 181, 17));
        MustChangePasswordCheckBox->setFont(font1);
        MustChangePasswordCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox:disabled { color: gray; }"));
        MustUseOTPCheckBox = new QCheckBox(ClientSecurity);
        MustUseOTPCheckBox->setObjectName("MustUseOTPCheckBox");
        MustUseOTPCheckBox->setEnabled(false);
        MustUseOTPCheckBox->setGeometry(QRect(211, 50, 181, 17));
        QFont font2;
        font2.setPointSize(10);
        font2.setStrikeOut(false);
        MustUseOTPCheckBox->setFont(font2);
        MustUseOTPCheckBox->setMouseTracking(true);
        MustUseOTPCheckBox->setStyleSheet(QString::fromUtf8("QCheckBox:disabled { color: gray; }"));
        MustUseOTPCheckBox->setCheckable(true);
        MustUseOTPCheckBox->setChecked(false);
        MustUseOTPCheckBox->setTristate(false);
        DenyOthersPasswordChangeCheckBox = new QCheckBox(ClientSecurity);
        DenyOthersPasswordChangeCheckBox->setObjectName("DenyOthersPasswordChangeCheckBox");
        DenyOthersPasswordChangeCheckBox->setEnabled(true);
        DenyOthersPasswordChangeCheckBox->setGeometry(QRect(20, 110, 321, 17));
        DenyOthersPasswordChangeCheckBox->setFont(font1);
        DenyOthersPasswordChangeCheckBox->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPInUseCheckBox = new QCheckBox(ClientSecurity);
        OTPInUseCheckBox->setObjectName("OTPInUseCheckBox");
        OTPInUseCheckBox->setEnabled(true);
        OTPInUseCheckBox->setGeometry(QRect(211, 80, 181, 17));
        OTPInUseCheckBox->setFont(font1);
        OTPInUseCheckBox->setStyleSheet(QString::fromUtf8("color: black;"));
        CancelButton = new QPushButton(ClientSecurity);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(351, 520, 86, 21));
        CancelButton->setFont(font1);
        CancelButton->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPWidget = new QWidget(ClientSecurity);
        OTPWidget->setObjectName("OTPWidget");
        OTPWidget->setGeometry(QRect(1, 140, 451, 371));
        OTPParametersLabel = new QLabel(OTPWidget);
        OTPParametersLabel->setObjectName("OTPParametersLabel");
        OTPParametersLabel->setGeometry(QRect(20, 0, 151, 18));
        OTPParametersLabel->setFont(font1);
        OTPParametersLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPQRCodeImage = new QLabel(OTPWidget);
        OTPQRCodeImage->setObjectName("OTPQRCodeImage");
        OTPQRCodeImage->setGeometry(QRect(20, 150, 222, 210));
        OTPQRCodeImage->setStyleSheet(QString::fromUtf8(""));
        OTPQRCodeLabel = new QLabel(OTPWidget);
        OTPQRCodeLabel->setObjectName("OTPQRCodeLabel");
        OTPQRCodeLabel->setGeometry(QRect(20, 120, 151, 18));
        OTPQRCodeLabel->setFont(font1);
        OTPQRCodeLabel->setStyleSheet(QString::fromUtf8("color:black;"));
        OTPParamsNoteLabel = new QLabel(OTPWidget);
        OTPParamsNoteLabel->setObjectName("OTPParamsNoteLabel");
        OTPParamsNoteLabel->setGeometry(QRect(260, 190, 191, 171));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setKerning(true);
        OTPParamsNoteLabel->setFont(font3);
        OTPParamsNoteLabel->setAutoFillBackground(false);
        OTPParamsNoteLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPParamsNoteLabel->setTextFormat(Qt::TextFormat::AutoText);
        OTPParamsNoteLabel->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        OTPParamsNoteLabel->setWordWrap(true);
        OTPKeyRegenerateButton = new QPushButton(OTPWidget);
        OTPKeyRegenerateButton->setObjectName("OTPKeyRegenerateButton");
        OTPKeyRegenerateButton->setGeometry(QRect(345, 120, 93, 22));
        QFont font4;
        font4.setPointSize(8);
        OTPKeyRegenerateButton->setFont(font4);
        OTPKeyRegenerateButton->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPTimeStepLabel = new QLabel(OTPWidget);
        OTPTimeStepLabel->setObjectName("OTPTimeStepLabel");
        OTPTimeStepLabel->setGeometry(QRect(20, 25, 111, 13));
        OTPTimeStepLabel->setFont(font4);
        OTPTimeStepLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPDigitsComboBox = new QComboBox(OTPWidget);
        OTPDigitsComboBox->setObjectName("OTPDigitsComboBox");
        OTPDigitsComboBox->setGeometry(QRect(352, 20, 79, 21));
        OTPDigitsComboBox->setFont(font4);
        OTPDigitsComboBox->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPKeyLabel = new QLabel(OTPWidget);
        OTPKeyLabel->setObjectName("OTPKeyLabel");
        OTPKeyLabel->setGeometry(QRect(20, 70, 131, 18));
        QFont font5;
        font5.setPointSize(9);
        OTPKeyLabel->setFont(font5);
        OTPKeyLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPDigitsLabel = new QLabel(OTPWidget);
        OTPDigitsLabel->setObjectName("OTPDigitsLabel");
        OTPDigitsLabel->setGeometry(QRect(220, 25, 131, 13));
        OTPDigitsLabel->setFont(font4);
        OTPDigitsLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPKeyCopyButton = new QPushButton(OTPWidget);
        OTPKeyCopyButton->setObjectName("OTPKeyCopyButton");
        OTPKeyCopyButton->setGeometry(QRect(345, 90, 93, 22));
        OTPKeyCopyButton->setFont(font4);
        OTPKeyCopyButton->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPParamsNoteImage = new QLabel(OTPWidget);
        OTPParamsNoteImage->setObjectName("OTPParamsNoteImage");
        OTPParamsNoteImage->setGeometry(QRect(260, 155, 31, 32));
        OTPParamsNoteImage->setStyleSheet(QString::fromUtf8(""));
        OTPParamsNoteImage->setPixmap(QPixmap(QString::fromUtf8(":/img/SIm2/UserWarning.png")));
        OTPParamsNoteImage->setScaledContents(true);
        OTPParamsNoteImage->setWordWrap(false);
        OTPInfoLabel = new QLabel(OTPWidget);
        OTPInfoLabel->setObjectName("OTPInfoLabel");
        OTPInfoLabel->setGeometry(QRect(20, 50, 351, 18));
        OTPInfoLabel->setFont(font5);
        OTPInfoLabel->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPKeyEdit = new QLineEdit(OTPWidget);
        OTPKeyEdit->setObjectName("OTPKeyEdit");
        OTPKeyEdit->setEnabled(true);
        OTPKeyEdit->setGeometry(QRect(20, 90, 318, 21));
        OTPKeyEdit->setStyleSheet(QString::fromUtf8("color: black;"));
        OTPKeyEdit->setEchoMode(QLineEdit::EchoMode::Password);
        OTPKeyEdit->setReadOnly(true);
        OTPTimeStepComboBox = new QComboBox(OTPWidget);
        OTPTimeStepComboBox->setObjectName("OTPTimeStepComboBox");
        OTPTimeStepComboBox->setGeometry(QRect(130, 20, 79, 21));
        OTPTimeStepComboBox->setFont(font4);
        OTPTimeStepComboBox->setStyleSheet(QString::fromUtf8("color: black;"));
        frame = new QFrame(OTPWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(170, 3, 261, 16));
        frame->setFrameShape(QFrame::Shape::HLine);
        frame->setFrameShadow(QFrame::Shadow::Plain);
        BottomLine = new QFrame(ClientSecurity);
        BottomLine->setObjectName("BottomLine");
        BottomLine->setGeometry(QRect(20, 500, 415, 16));
        BottomLine->setFrameShape(QFrame::Shape::HLine);
        BottomLine->setFrameShadow(QFrame::Shadow::Plain);

        retranslateUi(ClientSecurity);

        QMetaObject::connectSlotsByName(ClientSecurity);
    } // setupUi

    void retranslateUi(QDialog *ClientSecurity)
    {
        ClientSecurity->setWindowTitle(QCoreApplication::translate("ClientSecurity", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 \320\261\320\265\320\267\320\277\320\265\320\272\320\270 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260", nullptr));
        HeaderLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 \320\261\320\265\320\267\320\277\320\265\320\272\320\270 \320\272\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207\320\260", nullptr));
        HeaderImage->setText(QString());
        OKButton->setText(QCoreApplication::translate("ClientSecurity", "\320\236\320\232", nullptr));
        CantChangePasswordCheckBox->setText(QCoreApplication::translate("ClientSecurity", "\320\227\320\260\320\261\320\276\321\200\320\276\320\275\320\260 \320\267\320\274\321\226\320\275\320\270 \320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        MustChangePasswordCheckBox->setText(QCoreApplication::translate("ClientSecurity", "\320\235\320\265\320\276\320\261\321\205\321\226\320\264\320\275\320\276 \320\267\320\274\321\226\320\275\320\270\321\202\320\270 \320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        MustUseOTPCheckBox->setText(QCoreApplication::translate("ClientSecurity", "\320\236\320\261\320\276\320\262'\321\217\320\267\320\272\320\276\320\262\320\270\320\271 OTP-\320\277\320\260\321\200\320\276\320\273\321\214", nullptr));
        DenyOthersPasswordChangeCheckBox->setText(QCoreApplication::translate("ClientSecurity", "\320\227\320\260\320\261\320\276\321\200\320\276\320\275\320\260 \320\260\320\264\320\274\321\226\320\275\321\226\321\201\321\202\321\200\320\260\321\202\320\270\320\262\320\275\320\276\321\227 \320\267\320\274\321\226\320\275\320\270 \320\277\320\260\321\200\320\276\320\273\321\226\320\262", nullptr));
        OTPInUseCheckBox->setText(QCoreApplication::translate("ClientSecurity", "OTP-\320\277\320\260\321\200\320\276\320\273\321\214 \320\262\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\276", nullptr));
        CancelButton->setText(QCoreApplication::translate("ClientSecurity", "\320\222\321\226\320\264\320\274\321\226\320\275\320\260", nullptr));
        OTPParametersLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 OTP-\320\277\320\260\321\200\320\276\320\273\321\217", nullptr));
        OTPQRCodeImage->setText(QString());
        OTPQRCodeLabel->setText(QCoreApplication::translate("ClientSecurity", "QR-\320\272\320\276\320\264 \320\267 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\260\320\274\320\270:", nullptr));
        OTPParamsNoteLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\235\320\265\320\276\320\261\321\205\321\226\320\264\320\275\320\276 \321\201\320\272\320\276\320\277\321\226\321\216\320\262\320\260\321\202\320\270 \321\202\320\260 \320\267\320\261\320\265\321\200\320\265\320\263\321\202\320\270 \320\267\320\263\320\265\320\275\320\265\321\200\320\276\320\262\320\260\320\275\320\270\320\271 \320\272\320\273\321\216\321\207 \321\204\320\276\321\200\320\274\321\203\320\262\320\260\320\275\320\275\321\217 OTP-\320\277\320\260\321\200\320\276\320\273\321\217 \320\260\320\261\320\276 \320\262\321\226\320\264\321\201\320\272\320\260\320\275\321\203\320\262\320\260\321\202\320\270 QR-\320\272\320\276\320\264 \320\267 \320\277\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\260\320\274\320\270 \321\203 \320\274\320\276\320\261\321\226\320\273\321\214\320\275\320\276\320\274\321\203 \320\264\320\276\320\264\320\260\321\202\320\272\321\203 (\320\263\320\265\320\275\320\265\321\200\320\260\321\202\320\276\321\200\321\226 OTP-\320\277\320\260\321\200\320\276\320\273\321"
                        "\226\320\262). \320\237\321\226\321\201\320\273\321\217 \320\262\321\201\321\202\320\260\320\275\320\276\320\262\320\273\320\265\320\275\320\275\321\217 \320\262\320\270\320\272\320\276\321\200\320\270\321\201\321\202\320\260\320\275\320\275\321\217 OTP-\320\277\320\260\321\200\320\276\320\273\321\217 \320\264\320\276\321\201\321\202\321\203\320\277 \320\264\320\276 \320\272\321\200\320\270\320\277\321\202\320\276\320\274\320\276\320\264\321\203\320\273\321\217 \320\261\320\265\320\267 OTP-\320\277\320\260\321\200\320\276\320\273\321\217 \320\261\321\203\320\264\320\265 \320\275\320\265\320\274\320\276\320\266\320\273\320\270\320\262\320\270\320\271", nullptr));
        OTPKeyRegenerateButton->setText(QCoreApplication::translate("ClientSecurity", "\320\237\320\265\321\200\320\265\320\263\320\265\320\275\320\265\321\200\321\203\320\262\320\260\321\202\320\270", nullptr));
        OTPTimeStepLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\247\320\260\321\201\320\276\320\262\320\270\320\271 \321\226\320\275\321\202\320\265\321\200\320\262\320\260\320\273, \321\201:", nullptr));
        OTPKeyLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\232\320\273\321\216\321\207 (Base32-\321\201\321\202\321\200\320\276\320\272\320\260):", nullptr));
        OTPDigitsLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\224\320\276\320\262\320\266\320\270\320\275\320\260 \320\277\320\260\321\200\320\276\320\273\321\217, \321\206\320\270\321\204\321\200:", nullptr));
        OTPKeyCopyButton->setText(QCoreApplication::translate("ClientSecurity", "\320\241\320\272\320\276\320\277\321\226\321\216\320\262\320\260\321\202\320\270", nullptr));
        OTPParamsNoteImage->setText(QString());
        OTPInfoLabel->setText(QCoreApplication::translate("ClientSecurity", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\263\320\265\321\210\321\203\320\262\320\260\320\275\320\275\321\217 - HMAC-SHA-1, \320\264\320\276\320\262\320\266\320\270\320\275\320\260 \320\272\320\273\321\216\321\207\320\260 - 20 \320\261\320\260\320\271\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientSecurity: public Ui_ClientSecurity {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTSECURITY_H
