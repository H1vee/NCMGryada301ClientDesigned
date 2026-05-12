/********************************************************************************
** Form generated from reading UI file 'moduleparamsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULEPARAMSDIALOG_H
#define UI_MODULEPARAMSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ModuleParamsDialog
{
public:
    QLabel *HeaderImage;
    QLabel *HeaderLabel;
    QLineEdit *NameEdit;
    QLabel *NameEditLabel;
    QLabel *SNEditLabel;
    QLabel *AddressLabel;
    QLabel *InitialPort1Label;
    QLabel *InitialPort2Label;
    QLabel *InitialPort3Label;
    QLabel *InitialPort4Label;
    QLabel *InitialPort5Label;
    QLabel *InitialPort6Label;
    QLineEdit *InitialPort1Edit;
    QLineEdit *InitialPort2Edit;
    QLineEdit *InitialPort3Edit;
    QLineEdit *InitialPort4Edit;
    QLineEdit *InitialPort5Edit;
    QLineEdit *InitialPort6Edit;
    QPushButton *OKButton;
    QPushButton *CancelButton;
    QLineEdit *SNEdit;
    QLineEdit *AddressEdit;
    QCheckBox *InitialPortsCheckBox;
    QFrame *SplitLine;
    QFrame *line;

    void setupUi(QDialog *ModuleParamsDialog)
    {
        if (ModuleParamsDialog->objectName().isEmpty())
            ModuleParamsDialog->setObjectName("ModuleParamsDialog");
        ModuleParamsDialog->resize(326, 537);
        ModuleParamsDialog->setMinimumSize(QSize(326, 537));
        ModuleParamsDialog->setMaximumSize(QSize(326, 537));
        QFont font;
        font.setFamilies({QString::fromUtf8("Tahoma")});
        font.setPointSize(8);
        font.setKerning(false);
        font.setStyleStrategy(QFont::PreferAntialias);
        ModuleParamsDialog->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/SIm2/NetDevice.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ModuleParamsDialog->setWindowIcon(icon);
        HeaderImage = new QLabel(ModuleParamsDialog);
        HeaderImage->setObjectName("HeaderImage");
        HeaderImage->setGeometry(QRect(10, 20, 40, 40));
        HeaderImage->setPixmap(QPixmap(QString::fromUtf8(":/img/SIm2/NetDevice.ico")));
        HeaderImage->setScaledContents(true);
        HeaderLabel = new QLabel(ModuleParamsDialog);
        HeaderLabel->setObjectName("HeaderLabel");
        HeaderLabel->setGeometry(QRect(60, 30, 171, 21));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Tahoma")});
        font1.setPointSize(9);
        font1.setKerning(false);
        font1.setStyleStrategy(QFont::PreferAntialias);
        HeaderLabel->setFont(font1);
        NameEdit = new QLineEdit(ModuleParamsDialog);
        NameEdit->setObjectName("NameEdit");
        NameEdit->setGeometry(QRect(16, 97, 291, 25));
        NameEdit->setFont(font1);
        NameEdit->setMaxLength(255);
        NameEditLabel = new QLabel(ModuleParamsDialog);
        NameEditLabel->setObjectName("NameEditLabel");
        NameEditLabel->setGeometry(QRect(16, 80, 111, 16));
        NameEditLabel->setFont(font1);
        SNEditLabel = new QLabel(ModuleParamsDialog);
        SNEditLabel->setObjectName("SNEditLabel");
        SNEditLabel->setGeometry(QRect(16, 143, 111, 16));
        SNEditLabel->setFont(font1);
        AddressLabel = new QLabel(ModuleParamsDialog);
        AddressLabel->setObjectName("AddressLabel");
        AddressLabel->setGeometry(QRect(16, 181, 81, 16));
        AddressLabel->setFont(font1);
        InitialPort1Label = new QLabel(ModuleParamsDialog);
        InitialPort1Label->setObjectName("InitialPort1Label");
        InitialPort1Label->setEnabled(false);
        InitialPort1Label->setGeometry(QRect(30, 250, 131, 16));
        InitialPort1Label->setFont(font1);
        InitialPort2Label = new QLabel(ModuleParamsDialog);
        InitialPort2Label->setObjectName("InitialPort2Label");
        InitialPort2Label->setEnabled(false);
        InitialPort2Label->setGeometry(QRect(30, 284, 131, 16));
        InitialPort2Label->setFont(font1);
        InitialPort3Label = new QLabel(ModuleParamsDialog);
        InitialPort3Label->setObjectName("InitialPort3Label");
        InitialPort3Label->setEnabled(false);
        InitialPort3Label->setGeometry(QRect(30, 324, 131, 16));
        InitialPort3Label->setFont(font1);
        InitialPort4Label = new QLabel(ModuleParamsDialog);
        InitialPort4Label->setObjectName("InitialPort4Label");
        InitialPort4Label->setEnabled(false);
        InitialPort4Label->setGeometry(QRect(30, 366, 131, 16));
        InitialPort4Label->setFont(font1);
        InitialPort5Label = new QLabel(ModuleParamsDialog);
        InitialPort5Label->setObjectName("InitialPort5Label");
        InitialPort5Label->setEnabled(false);
        InitialPort5Label->setGeometry(QRect(30, 405, 131, 16));
        InitialPort5Label->setFont(font1);
        InitialPort6Label = new QLabel(ModuleParamsDialog);
        InitialPort6Label->setObjectName("InitialPort6Label");
        InitialPort6Label->setEnabled(false);
        InitialPort6Label->setGeometry(QRect(30, 446, 131, 16));
        InitialPort6Label->setFont(font1);
        InitialPort1Edit = new QLineEdit(ModuleParamsDialog);
        InitialPort1Edit->setObjectName("InitialPort1Edit");
        InitialPort1Edit->setEnabled(false);
        InitialPort1Edit->setGeometry(QRect(160, 244, 90, 25));
        InitialPort1Edit->setFont(font1);
        InitialPort2Edit = new QLineEdit(ModuleParamsDialog);
        InitialPort2Edit->setObjectName("InitialPort2Edit");
        InitialPort2Edit->setEnabled(false);
        InitialPort2Edit->setGeometry(QRect(160, 280, 90, 25));
        InitialPort2Edit->setFont(font1);
        InitialPort3Edit = new QLineEdit(ModuleParamsDialog);
        InitialPort3Edit->setObjectName("InitialPort3Edit");
        InitialPort3Edit->setEnabled(false);
        InitialPort3Edit->setGeometry(QRect(160, 320, 90, 25));
        InitialPort3Edit->setFont(font1);
        InitialPort4Edit = new QLineEdit(ModuleParamsDialog);
        InitialPort4Edit->setObjectName("InitialPort4Edit");
        InitialPort4Edit->setEnabled(false);
        InitialPort4Edit->setGeometry(QRect(160, 360, 90, 25));
        InitialPort4Edit->setFont(font1);
        InitialPort5Edit = new QLineEdit(ModuleParamsDialog);
        InitialPort5Edit->setObjectName("InitialPort5Edit");
        InitialPort5Edit->setEnabled(false);
        InitialPort5Edit->setGeometry(QRect(160, 400, 90, 25));
        InitialPort5Edit->setFont(font1);
        InitialPort6Edit = new QLineEdit(ModuleParamsDialog);
        InitialPort6Edit->setObjectName("InitialPort6Edit");
        InitialPort6Edit->setEnabled(false);
        InitialPort6Edit->setGeometry(QRect(160, 440, 90, 25));
        InitialPort6Edit->setFont(font1);
        OKButton = new QPushButton(ModuleParamsDialog);
        OKButton->setObjectName("OKButton");
        OKButton->setGeometry(QRect(110, 500, 93, 28));
        CancelButton = new QPushButton(ModuleParamsDialog);
        CancelButton->setObjectName("CancelButton");
        CancelButton->setGeometry(QRect(220, 500, 93, 28));
        SNEdit = new QLineEdit(ModuleParamsDialog);
        SNEdit->setObjectName("SNEdit");
        SNEdit->setGeometry(QRect(150, 140, 61, 25));
        SNEdit->setFont(font1);
        SNEdit->setMaxLength(3);
        AddressEdit = new QLineEdit(ModuleParamsDialog);
        AddressEdit->setObjectName("AddressEdit");
        AddressEdit->setGeometry(QRect(150, 180, 161, 25));
        AddressEdit->setFont(font1);
        AddressEdit->setMaxLength(255);
        InitialPortsCheckBox = new QCheckBox(ModuleParamsDialog);
        InitialPortsCheckBox->setObjectName("InitialPortsCheckBox");
        InitialPortsCheckBox->setGeometry(QRect(16, 221, 201, 17));
        InitialPortsCheckBox->setFont(font1);
        SplitLine = new QFrame(ModuleParamsDialog);
        SplitLine->setObjectName("SplitLine");
        SplitLine->setGeometry(QRect(220, 220, 91, 20));
        SplitLine->setFrameShape(QFrame::Shape::HLine);
        SplitLine->setFrameShadow(QFrame::Shadow::Sunken);
        line = new QFrame(ModuleParamsDialog);
        line->setObjectName("line");
        line->setGeometry(QRect(10, 480, 301, 16));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        retranslateUi(ModuleParamsDialog);

        QMetaObject::connectSlotsByName(ModuleParamsDialog);
    } // setupUi

    void retranslateUi(QDialog *ModuleParamsDialog)
    {
        ModuleParamsDialog->setWindowTitle(QCoreApplication::translate("ModuleParamsDialog", "\320\234\320\276\320\264\321\203\320\273\321\214", nullptr));
        HeaderImage->setText(QString());
        HeaderLabel->setText(QCoreApplication::translate("ModuleParamsDialog", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 \320\274\320\276\320\264\321\203\320\273\321\217", nullptr));
        NameEditLabel->setText(QCoreApplication::translate("ModuleParamsDialog", "\320\235\320\260\320\267\320\262\320\260 \320\234\320\276\320\264\321\203\320\273\321\217:", nullptr));
        SNEditLabel->setText(QCoreApplication::translate("ModuleParamsDialog", "\320\241\320\265\321\200\321\226\320\271\320\275\320\270\320\271 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        AddressLabel->setText(QCoreApplication::translate("ModuleParamsDialog", "IP-\320\260\320\264\321\200\320\265\321\201\320\260:", nullptr));
        InitialPort1Label->setText(QCoreApplication::translate("ModuleParamsDialog", "TCP-\320\277\320\276\321\200\321\202 \321\202\320\276\321\207\320\272\320\270 1:", nullptr));
        InitialPort2Label->setText(QCoreApplication::translate("ModuleParamsDialog", "TCP-\320\277\320\276\321\200\321\202 \321\202\320\276\321\207\320\272\320\270 2:", nullptr));
        InitialPort3Label->setText(QCoreApplication::translate("ModuleParamsDialog", "TCP-\320\277\320\276\321\200\321\202 \321\202\320\276\321\207\320\272\320\270 3:", nullptr));
        InitialPort4Label->setText(QCoreApplication::translate("ModuleParamsDialog", "TCP-\320\277\320\276\321\200\321\202 \321\202\320\276\321\207\320\272\320\270 4:", nullptr));
        InitialPort5Label->setText(QCoreApplication::translate("ModuleParamsDialog", "TCP-\320\277\320\276\321\200\321\202 \321\202\320\276\321\207\320\272\320\270 5:", nullptr));
        InitialPort6Label->setText(QCoreApplication::translate("ModuleParamsDialog", "TCP-\320\277\320\276\321\200\321\202 \321\202\320\276\321\207\320\272\320\270 6:", nullptr));
        OKButton->setText(QCoreApplication::translate("ModuleParamsDialog", "\320\236\320\232", nullptr));
        CancelButton->setText(QCoreApplication::translate("ModuleParamsDialog", "\320\222\321\226\320\264\320\274\321\226\320\275\320\260", nullptr));
        InitialPortsCheckBox->setText(QCoreApplication::translate("ModuleParamsDialog", "\320\237\320\276\321\207\320\260\321\202\320\272\320\276\320\262\321\226 \321\202\320\276\321\207\320\272\320\270 \320\264\320\276\321\201\321\202\321\203\320\277\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ModuleParamsDialog: public Ui_ModuleParamsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULEPARAMSDIALOG_H
