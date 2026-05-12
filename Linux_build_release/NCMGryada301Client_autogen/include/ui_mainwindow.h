/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget_3;
    QLabel *TopImage;
    QLabel *TitleMain;
    QLabel *IITLabel1;
    QLabel *BottomTitle;
    QLabel *IITLabel2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QLabel *RegisteredModulesLabel;
    QListWidget *RegisteredModulesListView;
    QWidget *ButtonSection;
    QGroupBox *groupBox;
    QPushButton *AddItemButton;
    QPushButton *DeleteItemButton;
    QPushButton *ChangeItemButton;
    QPushButton *UpdateItemButton;
    QPushButton *ChangeItemPasswordButton;
    QPushButton *SecurityParametersButton;
    QFrame *ModulesLabel;
    QLabel *ButtonsTitle;
    QWidget *InfoTopPanel;
    QLabel *ImageLabel;
    QLabel *InfoLabel;
    QLabel *ModuleNameTitleLabel;
    QLabel *SNTitleLabel;
    QLabel *AddressTitleLabel;
    QLabel *InitialPortsTitleLabel;
    QLabel *InitialPortsLabel;
    QLabel *AddressLabel;
    QLabel *SNLabel;
    QLabel *ModuleNameLabel;
    QWidget *widget_5;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(650, 680);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(650, 680));
        MainWindow->setMaximumSize(QSize(650, 680));
        QFont font;
        font.setBold(false);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/SIm2/NetDevice.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_3 = new QWidget(centralwidget);
        widget_3->setObjectName("widget_3");
        widget_3->setMaximumSize(QSize(16777215, 80));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: #0B264F;"));
        TopImage = new QLabel(widget_3);
        TopImage->setObjectName("TopImage");
        TopImage->setGeometry(QRect(16, 16, 48, 48));
        TopImage->setPixmap(QPixmap(QString::fromUtf8(":/img/SIm2/NetDevice2.ico")));
        TitleMain = new QLabel(widget_3);
        TitleMain->setObjectName("TitleMain");
        TitleMain->setGeometry(QRect(70, 20, 531, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        QBrush brush1(QColor(255, 0, 0, 0));
        brush1.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::BrushStyle::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        QBrush brush3(QColor(255, 255, 255, 128));
        brush3.setStyle(Qt::BrushStyle::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::BrushStyle::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush4);
#endif
        TitleMain->setPalette(palette);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe UI")});
        font1.setPointSize(18);
        TitleMain->setFont(font1);
        TitleMain->setStyleSheet(QString::fromUtf8("color : white;\n"
"background: rgba(255, 0, 0, 0);"));
        IITLabel1 = new QLabel(widget_3);
        IITLabel1->setObjectName("IITLabel1");
        IITLabel1->setGeometry(QRect(70, 10, 51, 20));
        QFont font2;
        font2.setPointSize(8);
        IITLabel1->setFont(font2);
        IITLabel1->setStyleSheet(QString::fromUtf8("color : white;\n"
"background: rgba(255, 0, 0, 0);"));
        BottomTitle = new QLabel(widget_3);
        BottomTitle->setObjectName("BottomTitle");
        BottomTitle->setGeometry(QRect(70, 50, 201, 16));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe UI")});
        font3.setBold(true);
        BottomTitle->setFont(font3);
        BottomTitle->setStyleSheet(QString::fromUtf8("color : white;\n"
"background: rgba(255, 0, 0, 0);"));
        IITLabel2 = new QLabel(widget_3);
        IITLabel2->setObjectName("IITLabel2");
        IITLabel2->setGeometry(QRect(587, 1, 61, 20));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Segoe UI")});
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setItalic(true);
        font4.setStrikeOut(false);
        font4.setKerning(true);
        IITLabel2->setFont(font4);
        IITLabel2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        IITLabel2->setStyleSheet(QString::fromUtf8("color : white;\n"
"background: rgba(255, 0, 0, 0);\n"
"background-position:  top right;"));
        IITLabel2->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTop|Qt::AlignmentFlag::AlignTrailing);

        verticalLayout->addWidget(widget_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0, y1:0, x2:0, y2:1,\n"
"        stop:0 rgba(11, 38, 79, 255),   \n"
"        stop:1 rgba(18, 65, 120, 255)\n"
");\n"
"\n"
"\n"
""));
        RegisteredModulesLabel = new QLabel(widget);
        RegisteredModulesLabel->setObjectName("RegisteredModulesLabel");
        RegisteredModulesLabel->setGeometry(QRect(20, 15, 391, 31));
        QPalette palette1;
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush1);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::BrushStyle::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush1);
        QBrush brush6(QColor(255, 255, 255, 128));
        brush6.setStyle(Qt::BrushStyle::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush6);
#endif
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush1);
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush1);
        QBrush brush7(QColor(255, 255, 255, 128));
        brush7.setStyle(Qt::BrushStyle::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush7);
#endif
        RegisteredModulesLabel->setPalette(palette1);
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Segoe UI")});
        font5.setPointSize(19);
        RegisteredModulesLabel->setFont(font5);
        RegisteredModulesLabel->setStyleSheet(QString::fromUtf8("color : white;\n"
"background: rgba(255, 0, 0, 0);"));
        RegisteredModulesListView = new QListWidget(widget);
        RegisteredModulesListView->setObjectName("RegisteredModulesListView");
        RegisteredModulesListView->setGeometry(QRect(20, 50, 371, 361));
        RegisteredModulesListView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);
        RegisteredModulesListView->setStyleSheet(QString::fromUtf8(""));
        RegisteredModulesListView->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(widget);

        ButtonSection = new QWidget(centralwidget);
        ButtonSection->setObjectName("ButtonSection");
        ButtonSection->setMaximumSize(QSize(240, 16777215));
        ButtonSection->setStyleSheet(QString::fromUtf8(""));
        groupBox = new QGroupBox(ButtonSection);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 40, 191, 121));
        groupBox->setStyleSheet(QString::fromUtf8(""));
        AddItemButton = new QPushButton(groupBox);
        AddItemButton->setObjectName("AddItemButton");
        AddItemButton->setEnabled(true);
        AddItemButton->setGeometry(QRect(4, 35, 182, 28));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Sans Serif")});
        AddItemButton->setFont(font6);
        AddItemButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	text-align:left;\n"
"	border: none;\n"
"	color: black;\n"
"}\n"
"\n"
"QPushButton::hover { \n"
"	text-decoration: underline; \n"
"}\n"
"\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/SIm2/buttonIcon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        AddItemButton->setIcon(icon1);
        AddItemButton->setFlat(true);
        DeleteItemButton = new QPushButton(groupBox);
        DeleteItemButton->setObjectName("DeleteItemButton");
        DeleteItemButton->setEnabled(true);
        DeleteItemButton->setGeometry(QRect(4, 65, 182, 28));
        DeleteItemButton->setFont(font6);
        DeleteItemButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	text-align:left;\n"
"	border: none;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton::hover { \n"
"	text-decoration: underline; \n"
"}\n"
"\n"
""));
        DeleteItemButton->setIcon(icon1);
        DeleteItemButton->setFlat(true);
        ChangeItemButton = new QPushButton(groupBox);
        ChangeItemButton->setObjectName("ChangeItemButton");
        ChangeItemButton->setGeometry(QRect(4, 85, 182, 28));
        ChangeItemButton->setFont(font6);
        ChangeItemButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	text-align:left;\n"
"	border: none;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton::hover { \n"
"	text-decoration: underline; \n"
"}\n"
""));
        ChangeItemButton->setIcon(icon1);
        ChangeItemButton->setFlat(true);
        UpdateItemButton = new QPushButton(groupBox);
        UpdateItemButton->setObjectName("UpdateItemButton");
        UpdateItemButton->setGeometry(QRect(4, 6, 182, 28));
        UpdateItemButton->setFont(font6);
        UpdateItemButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	text-align:left;\n"
"	border: none;\n"
"}\n"
"\n"
"QPushButton::hover { \n"
"	text-decoration: underline; \n"
"}\n"
"QPushButton {\n"
"    color: black;\n"
"}\n"
""));
        UpdateItemButton->setIcon(icon1);
        ChangeItemPasswordButton = new QPushButton(groupBox);
        ChangeItemPasswordButton->setObjectName("ChangeItemPasswordButton");
        ChangeItemPasswordButton->setGeometry(QRect(4, 90, 182, 28));
        ChangeItemPasswordButton->setFont(font6);
        ChangeItemPasswordButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	text-align:left;\n"
"	border: none;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton::hover { \n"
"	text-decoration: underline; \n"
"}\n"
""));
        ChangeItemPasswordButton->setIcon(icon1);
        ChangeItemPasswordButton->setFlat(true);
        SecurityParametersButton = new QPushButton(groupBox);
        SecurityParametersButton->setObjectName("SecurityParametersButton");
        SecurityParametersButton->setGeometry(QRect(4, 80, 181, 28));
        SecurityParametersButton->setFont(font6);
        SecurityParametersButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	text-align:left;\n"
"	border: none;\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton::hover { \n"
"	text-decoration: underline; \n"
"}\n"
""));
        SecurityParametersButton->setIcon(icon1);
        SecurityParametersButton->setFlat(true);
        ModulesLabel = new QFrame(ButtonSection);
        ModulesLabel->setObjectName("ModulesLabel");
        ModulesLabel->setGeometry(QRect(20, 20, 191, 25));
        ModulesLabel->setFrameShape(QFrame::Shape::StyledPanel);
        ModulesLabel->setFrameShadow(QFrame::Shadow::Raised);
        ButtonsTitle = new QLabel(ModulesLabel);
        ButtonsTitle->setObjectName("ButtonsTitle");
        ButtonsTitle->setGeometry(QRect(8, 5, 71, 16));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Arial")});
        font7.setPointSize(9);
        font7.setBold(false);
        ButtonsTitle->setFont(font7);
        ButtonsTitle->setStyleSheet(QString::fromUtf8("color:white;\n"
"background: none;"));

        horizontalLayout->addWidget(ButtonSection);


        verticalLayout->addLayout(horizontalLayout);

        InfoTopPanel = new QWidget(centralwidget);
        InfoTopPanel->setObjectName("InfoTopPanel");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(InfoTopPanel->sizePolicy().hasHeightForWidth());
        InfoTopPanel->setSizePolicy(sizePolicy1);
        InfoTopPanel->setMaximumSize(QSize(16777215, 148));
        InfoTopPanel->setStyleSheet(QString::fromUtf8(""));
        ImageLabel = new QLabel(InfoTopPanel);
        ImageLabel->setObjectName("ImageLabel");
        ImageLabel->setGeometry(QRect(8, 10, 16, 16));
        ImageLabel->setStyleSheet(QString::fromUtf8("border-top : none;"));
        ImageLabel->setScaledContents(true);
        InfoLabel = new QLabel(InfoTopPanel);
        InfoLabel->setObjectName("InfoLabel");
        InfoLabel->setGeometry(QRect(30, 8, 351, 16));
        QFont font8;
        font8.setPointSize(9);
        font8.setBold(true);
        InfoLabel->setFont(font8);
        InfoLabel->setStyleSheet(QString::fromUtf8(""));
        ModuleNameTitleLabel = new QLabel(InfoTopPanel);
        ModuleNameTitleLabel->setObjectName("ModuleNameTitleLabel");
        ModuleNameTitleLabel->setGeometry(QRect(30, 35, 141, 16));
        QPalette palette2;
        QBrush brush8(QColor(0, 0, 0, 255));
        brush8.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::WindowText, brush8);
        QBrush brush9(QColor(11, 38, 79, 255));
        brush9.setStyle(Qt::BrushStyle::SolidPattern);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush9);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Text, brush8);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::ButtonText, brush8);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Base, brush9);
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Window, brush9);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::BrushStyle::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::WindowText, brush8);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush9);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Text, brush8);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::ButtonText, brush8);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Base, brush9);
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Window, brush9);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::WindowText, brush8);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush9);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Text, brush8);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::ButtonText, brush8);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Base, brush9);
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Window, brush9);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::PlaceholderText, brush10);
#endif
        ModuleNameTitleLabel->setPalette(palette2);
        QFont font9;
        font9.setPointSize(9);
        ModuleNameTitleLabel->setFont(font9);
        ModuleNameTitleLabel->setStyleSheet(QString::fromUtf8(""));
        SNTitleLabel = new QLabel(InfoTopPanel);
        SNTitleLabel->setObjectName("SNTitleLabel");
        SNTitleLabel->setGeometry(QRect(30, 60, 131, 16));
        SNTitleLabel->setFont(font9);
        SNTitleLabel->setStyleSheet(QString::fromUtf8(""));
        AddressTitleLabel = new QLabel(InfoTopPanel);
        AddressTitleLabel->setObjectName("AddressTitleLabel");
        AddressTitleLabel->setGeometry(QRect(30, 85, 131, 16));
        AddressTitleLabel->setFont(font9);
        AddressTitleLabel->setStyleSheet(QString::fromUtf8(""));
        InitialPortsTitleLabel = new QLabel(InfoTopPanel);
        InitialPortsTitleLabel->setObjectName("InitialPortsTitleLabel");
        InitialPortsTitleLabel->setGeometry(QRect(30, 110, 151, 16));
        InitialPortsTitleLabel->setFont(font9);
        InitialPortsTitleLabel->setStyleSheet(QString::fromUtf8(""));
        InitialPortsLabel = new QLabel(InfoTopPanel);
        InitialPortsLabel->setObjectName("InitialPortsLabel");
        InitialPortsLabel->setGeometry(QRect(165, 108, 411, 20));
        InitialPortsLabel->setFont(font9);
        InitialPortsLabel->setStyleSheet(QString::fromUtf8(""));
        AddressLabel = new QLabel(InfoTopPanel);
        AddressLabel->setObjectName("AddressLabel");
        AddressLabel->setGeometry(QRect(165, 83, 441, 20));
        AddressLabel->setFont(font9);
        AddressLabel->setStyleSheet(QString::fromUtf8(""));
        SNLabel = new QLabel(InfoTopPanel);
        SNLabel->setObjectName("SNLabel");
        SNLabel->setGeometry(QRect(165, 58, 421, 20));
        SNLabel->setFont(font9);
        SNLabel->setStyleSheet(QString::fromUtf8(""));
        ModuleNameLabel = new QLabel(InfoTopPanel);
        ModuleNameLabel->setObjectName("ModuleNameLabel");
        ModuleNameLabel->setGeometry(QRect(165, 33, 431, 20));
        ModuleNameLabel->setFont(font9);
        ModuleNameLabel->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(InfoTopPanel);

        widget_5 = new QWidget(centralwidget);
        widget_5->setObjectName("widget_5");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy2);
        widget_5->setMaximumSize(QSize(16777215, 20));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgba(18, 65, 120, 255);"));

        verticalLayout->addWidget(widget_5);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\206\320\206\320\242 \320\234\320\265\321\200\320\265\320\266\320\275\320\270\320\271 \320\272\321\200\320\270\320\277\321\202\320\276\320\274\320\276\320\264\321\203\320\273\321\214  \"\320\223\321\200\321\217\320\264\320\260-301\". \320\232\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207", nullptr));
        TopImage->setText(QString());
        TitleMain->setText(QCoreApplication::translate("MainWindow", "\320\234\320\265\321\200\320\265\320\266\320\275\320\270\320\271 \320\272\321\200\320\270\320\277\321\202\320\276\320\274\320\276\320\264\321\203\320\273\321\214 \"\320\223\321\200\321\217\320\264\320\260-301\"", nullptr));
        IITLabel1->setText(QCoreApplication::translate("MainWindow", "\320\206\320\206\320\242", nullptr));
        BottomTitle->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\321\200\320\270\321\201\321\202\321\203\320\262\320\260\321\207", nullptr));
        IITLabel2->setText(QCoreApplication::translate("MainWindow", "\320\206\320\206\320\242", nullptr));
        RegisteredModulesLabel->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\321\200\320\265\321\224\321\201\321\202\321\200\320\276\320\262\320\260\320\275\321\226 \320\272\321\200\320\270\320\277\321\202\320\276\320\274\320\276\320\264\321\203\320\273\321\226", nullptr));
        groupBox->setTitle(QString());
        AddItemButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\264\320\260\321\202\320\270...", nullptr));
        DeleteItemButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\270\320\264\320\260\320\273\320\270\321\202\320\270", nullptr));
        ChangeItemButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\274\321\226\320\275\320\270\321\202\320\270", nullptr));
        UpdateItemButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\275\320\276\320\262\320\270\321\202\320\270", nullptr));
        ChangeItemPasswordButton->setText(QCoreApplication::translate("MainWindow", "\320\227\320\274\321\226\320\275\320\270\321\202\320\270 \320\277\320\260\321\200\320\276\320\273\321\214...", nullptr));
        SecurityParametersButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\320\270 \320\261\320\265\320\277\320\265\320\272\320\270...", nullptr));
        ButtonsTitle->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\264\321\203\320\273\321\226", nullptr));
        ImageLabel->setText(QString());
        InfoLabel->setText(QString());
        ModuleNameTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260 \320\272\321\200\320\270\320\277\321\202\320\276\320\274\320\276\320\264\321\203\320\273\321\217:", nullptr));
        SNTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\241\320\265\321\200\321\226\320\271\320\275\320\270\320\271 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        AddressTitleLabel->setText(QCoreApplication::translate("MainWindow", "IP-\320\260\320\264\321\200\320\265\321\201\320\260:", nullptr));
        InitialPortsTitleLabel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\207\320\260\321\202\320\272\320\276\320\262\321\226 TCP-\320\277\320\276\321\200\321\202\320\270:", nullptr));
        InitialPortsLabel->setText(QString());
        AddressLabel->setText(QString());
        SNLabel->setText(QString());
        ModuleNameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
