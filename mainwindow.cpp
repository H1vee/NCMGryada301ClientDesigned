#include <QMessageBox>
#include <QMenu>
#include <QMouseEvent>

#include <QtGlobal>
#include <QGuiApplication>
#include <QStyleHints>
#include <QPalette>
#include <QSettings>
#include <QProcess>
#include "./Settings/NCMsList.h"
#include "tlistitem.h"
#include "moduleparamsdialog.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupButtonsLayout();
    updateTheme();
    qApp->installEventFilter(this);

    pModulesList = new NCMsList(HKEY_LOCAL_MACHINE);
    ui->RegisteredModulesListView->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->AddItemButton, &QPushButton::clicked,
            this, &MainWindow::AddExtendedMenuItemFrameItemLabelClick);
    connect(ui->ChangeItemButton, &QPushButton::clicked,
            this, &MainWindow::ChangeExtendedMenuItemFrameItemLabelClick);
    connect(ui->DeleteItemButton, &QPushButton::clicked,
            this, &MainWindow::DeleteExtendedMenuItemFrameItemLabelClick);
    connect(ui->RegisteredModulesListView,&QListWidget::itemClicked,
            this,&MainWindow::RegisteredModulesListViewSelectItem);
    connect(ui->RegisteredModulesListView,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(ShowContextMenu(QPoint)));
    connect (ui->UpdateItemButton,&QPushButton::clicked,this,&MainWindow::UpdateRegisteredModulesListView);
    connect(ui->ChangeItemPasswordButton,&QPushButton::clicked,
            this,&MainWindow::ChangePasswordExtendedMenuItemFrameItemLabelClick);
    connect(ui->SecurityParametersButton,&QPushButton::clicked,
            this,&MainWindow::ClientSecurityExtendedMenuItemFrameItemLabelClick);

    this->setStyleSheet("MainWindow { background-color: #0B264F; }");
    initializeApplication();


    UpdateRegisteredModulesListView();
}



MainWindow::~MainWindow()
{
    if(pModulesList!=nullptr)
        delete pModulesList;
    delete ui;
}


bool MainWindow::isDarkTheme() const
{
#if defined(Q_OS_WINDOWS)
    QSettings settings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                      QSettings::NativeFormat);
    return settings.value("AppsUseLightTheme", 1).toInt() == 0;

#elif defined(Q_OS_MACOS)
   QProcess process;
   process.start("defaults", QStringList() << "read" << "-g" << "AppleInterfaceStyle");
   if (process.waitForFinished(1000)) {
       QString result = process.readAllStandardOutput().trimmed();
       return result.contains("Dark", Qt::CaseInsensitive);
   }
   return false;
    
#elif defined(Q_OS_LINUX) || defined(Q_OS_UNIX)
    QProcess gsettingsCheck;
    gsettingsCheck.start("gsettings", QStringList() << "get" << "org.gnome.desktop.interface" << "color-scheme");
    if (gsettingsCheck.waitForFinished(1000)) {
        QString colorScheme = gsettingsCheck.readAllStandardOutput().trimmed();
        colorScheme = colorScheme.remove('\'').remove('\"').toLower();
        if (colorScheme.contains("prefer-dark")) {
            return true;
        }
        if (colorScheme.contains("prefer-light") || colorScheme.contains("default")) {
            return false;
        }
    }
#else
    QColor bgColor = QGuiApplication::palette().color(QPalette::Window);
    int brightness = (bgColor.red() * 299 +
                      bgColor.green() * 587 +
                      bgColor.blue() * 114) / 1000;
    return brightness < 128;
#endif
}
void MainWindow::updateTheme()
{
    bool dark = isDarkTheme();
    int fontWeight = 600;
    QString currentStyle = ui->TitleMain->styleSheet();
    ui->TitleMain->setStyleSheet(currentStyle + QString(" font-weight: %1;").arg(fontWeight));
    QString currentStyleIIT = ui->IITLabel1->styleSheet();
    ui->IITLabel1->setStyleSheet(currentStyleIIT + " font-size: 11pt;");
    QString regModLabelCurrentStyle = ui->RegisteredModulesLabel->styleSheet();
#ifdef Q_OS_LINUX
    ui->RegisteredModulesLabel->setStyleSheet(regModLabelCurrentStyle +
    QString(" letter-spacing: -2px; font-weight: %1;").arg(fontWeight));
#else
    ui->RegisteredModulesLabel->setStyleSheet(regModLabelCurrentStyle +
QString(" letter-spacing: -1px; font-weight: %1;").arg(fontWeight));
#endif


    applyListViewStyle(dark);
    applyButtonSectionStyle(dark);
    applyInfoPanelStyle(dark);
    applyLabelsStyle(dark);
    applyButtonsStyle(dark);

    setupListAnimations();
}

void MainWindow::applyListViewStyle(bool darkTheme)
{
    ui->RegisteredModulesListView->setStyleSheet(getListWidgetStyleSheet(darkTheme));
}

void MainWindow::applyButtonSectionStyle(bool darkTheme)
{
    ui->ButtonSection->setStyleSheet(getButtonSectionStyleSheet(darkTheme));
}

void MainWindow::applyInfoPanelStyle(bool darkTheme)
{
    ui->InfoTopPanel->setStyleSheet(getInfoTopPanelStyleSheet(darkTheme));
}

void MainWindow::applyLabelsStyle(bool darkTheme)
{
    QString labelStyle = getInfoLabelsStyleSheet(darkTheme);
    QString currentStyle = ui->InfoTopPanel->styleSheet();
    ui->InfoTopPanel->setStyleSheet(currentStyle + labelStyle);
}

void MainWindow::applyButtonsStyle(bool darkTheme)
{
    const QList<QPushButton*> buttons = {
        ui->UpdateItemButton, ui->AddItemButton, ui->ChangeItemButton,
        ui->ChangeItemPasswordButton, ui->DeleteItemButton, ui->SecurityParametersButton
    };

    QString buttonStyle = getButtonsStyleSheet(darkTheme);
    for (QPushButton* button : buttons) {
        button->setStyleSheet(buttonStyle);
    }
}


QString MainWindow::getListWidgetStyleSheet(bool darkTheme) const
{
    const QString darkStyle = R"(
        QListWidget {
            background-color: #0f172a;
            border: 1px solid #475569;
            border-radius: 8px;
            outline: none;
            padding: 4px;
            color: #e2e8f0;
            font-weight: 600;
            font-size: 15px;
        }
        QListWidget::item {
            background: rgba(30, 41, 59, 0.7);
            border: 1px solid transparent;
            border-radius: 6px;
            margin: 2px;
            padding: 8px 12px 8px 8px;
            font-size: 13px;
            font-weight: 600;
            spacing: 6px;
            color: #cbd5e1;
        }
        QListWidget::item:hover {
            background: rgba(30, 41, 59, 0.9);
            border: 1px solid rgba(59, 130, 246, 0.3);
            font-weight: 700;
        }
        QListWidget::item:selected {
            background-color: #0B264F;
            color: white;
            border: 1px solid #3b82f6;
            border-radius: 6px;
            padding: 8px 12px 8px 8px;
            font-weight: 700;
        }
    )";

    const QString lightStyle = R"(
        QListWidget {
            background-color: #e2e9f0;
            border: 1px solid #cbd5e1;
            border-radius: 8px;
            outline: none;
            padding: 4px;
            font-weight: 600;
            font-size: 15px;
        }
        QListWidget::item {
            background-color: #ffffff;
            border: 1px solid transparent;
            border-radius: 6px;
            margin: 2px;
            padding: 8px 12px 8px 8px;
            font-size: 13px;
            font-weight: 600;
            spacing: 6px;
            color: #374151;
        }
        QListWidget::item:selected {
            background-color: #f5f7fa;
            color: #2c3e50;
            border: 1px solid #4a5568;
            border-radius: 6px;
            padding: 8px 12px 8px 8px;
            font-weight: 700;
        }
        QListWidget::item:selected:!hover {
            background-color: #f5f7fa;
            color: #2c3e50;
            border: 1px solid #4a5568;
            font-weight: 700;
        }
    )";

    return darkTheme ? darkStyle : lightStyle;
}

QString MainWindow::getButtonSectionStyleSheet(bool darkTheme) const
{
    const QString baseColor = darkTheme ? "#0f172a" : "#e2e9f0";

    return QString(R"(
        #ButtonSection {
            background-color: %1;
            border-bottom: 3px solid rgba(18, 65, 120, 255);
            border-top-left-radius: 8px;
            outline: none;
        }
        #groupBox {
            background-color: %1;
            border: 2px solid rgb(14,39,78);
            border-top-left-radius: 0px;
            border-top-right-radius: 0px;
            border-bottom-left-radius: 8px;
            border-bottom-right-radius: 8px;
        }
        #ModulesLabel {
            border-radius: 5px;
            background: qlineargradient(
                spread:pad,
                x1:0, y1:0, x2:1, y2:0,
                stop:0 rgba(11, 38, 79, 255),
                stop:1 rgba(18, 65, 120, 255)
            );
            color: #ffffff;
            font-weight: 700;
            font-size: 14px;
            padding-left: 12px;
            padding-top: 6px;
            padding-bottom: 6px;
        }
        #ButtonsTitle {
            font-weight: 700;
            font-size: 14px;
        }
    )").arg(baseColor);
}

QString MainWindow::getButtonsStyleSheet(bool darkTheme) const
{
    struct ButtonColors {
        QString textColor;
        QString hoverBg;
        QString pressedBg;
        int fontSize;
    };

#ifdef Q_OS_LINUX
    const QString letterSpacing = "letter-spacing: -1px;";
#else
    const QString letterSpacing = "";
#endif

    const ButtonColors colors = darkTheme
        ? ButtonColors{"#e2e8f0", "rgba(59, 130, 246, 0.2)", "rgba(59, 130, 246, 0.4)", 14}
    : ButtonColors{"#34495e", "rgba(150, 160, 180, 0.4)", "rgba(100, 110, 130, 0.6)", 14};

    return QString(R"(
       #UpdateItemButton, #AddItemButton, #ChangeItemButton,
       #ChangeItemPasswordButton, #DeleteItemButton, #SecurityParametersButton  {
           background-color: transparent;
           color: %1;
           border: none;
           border-radius: 4px;
           padding: 8px 12px;
           text-align: left;
           font-size: %4px;
           font-weight: 700;
           %7
           min-height: 18px;
           margin-left: 5px;
       }
       #UpdateItemButton:hover, #AddItemButton:hover, #ChangeItemButton:hover,
       #ChangeItemPasswordButton:hover, #DeleteItemButton:hover, #SecurityParametersButton:hover{
           background-color: %2;
           color: %5;
           font-weight: 800;
       }
        #UpdateItemButton:pressed, #AddItemButton:pressed, #ChangeItemButton:pressed,
       #ChangeItemPasswordButton:pressed, #DeleteItemButton:pressed, #SecurityParametersButton:pressed{
           background-color: %3;
           color: %6;
           font-weight: 800;
       }
   )")
    .arg(colors.textColor)
    .arg(colors.hoverBg)
    .arg(colors.pressedBg)
    .arg(colors.fontSize)
    .arg(darkTheme ? "#ffffff" : "#2c3e50")
    .arg(darkTheme ? "#ffffff" : "#1a1a1a")
    .arg(letterSpacing);
}

QString MainWindow::getInfoTopPanelStyleSheet(bool darkTheme) const
{
    const QString bgColor = darkTheme ? "#0f172a" : "#e2e9f0";
    const QString borderColor = darkTheme ? "#475569" : "#e9ecef";
    const QString textColor = darkTheme ? "#e2e8f0" : "rgb(14, 39, 78)";

    return QString(R"(
        #InfoTopPanel {
            background-color: %1;
            border-bottom: 1px solid %2;
            outline: none;
        }
        #InfoLabel {
            color: %3;
            border-top: none;
            font-weight: 700;
            font-size: 14px;
        }
        #ImageLabel {
            background-color: %1;
        }
    )").arg(bgColor, borderColor, textColor);
}

QString MainWindow::getInfoLabelsStyleSheet(bool darkTheme) const
{
    const QString bgColor = darkTheme ? "#0f172a" : "#e2e9f0";
    const QString textColor = darkTheme ? "#e2e8f0" : "rgb(14, 39, 78)";
#ifdef Q_OS_WIN
    const int LABEL_X_OFFSET = -9;
#elif defined(Q_OS_LINUX)
    const int LABEL_X_OFFSET = +8;
#elif defined(Q_OS_MACOS)
    const int LABEL_X_OFFSET = 0;
#endif

    const QPoint ModuleNameLabelPos = ui->ModuleNameLabel->pos();
    const QSize ModuleNameLabelSize = ui->ModuleNameLabel->size();
    const QPoint SNLabelPos = ui->SNLabel->pos();
    const QSize SNLabelSize = ui->SNLabel->size();
    const QPoint AddressLabelPos = ui->AddressLabel->pos();
    const QSize AddressLabelSize = ui->AddressLabel->size();
    const QPoint InitialPortsLabelPos = ui->InitialPortsLabel->pos();
    const QSize InitialPortsLabelSize = ui->InitialPortsLabel->size();
    ui->InitialPortsLabel->setGeometry(
        InitialPortsLabelPos.x() + LABEL_X_OFFSET, InitialPortsLabelPos.y()+1,
        InitialPortsLabelSize.width(), InitialPortsLabelSize.height());
    ui->AddressLabel->setGeometry(
    AddressLabelPos.x() + LABEL_X_OFFSET, AddressLabelPos.y(),
    AddressLabelSize.width(), AddressLabelSize.height());
    ui->ModuleNameLabel->setGeometry(
        ModuleNameLabelPos.x() + LABEL_X_OFFSET, ModuleNameLabelPos.y()+1,
        ModuleNameLabelSize.width(), ModuleNameLabelSize.height());
    ui->SNLabel->setGeometry(
        SNLabelPos.x() + LABEL_X_OFFSET, SNLabelPos.y(),
        SNLabelSize.width(), SNLabelSize.height());


    return QString(R"(
    #InfoLabel {
        background-color: %1;
        border-top: none;
        color: %2;
        font-weight: 700;
        font-size: 13px;
    }
    #AddressLabel, #AddressTitleLabel,
    #InitialPortsLabel, #InitialPortsTitleLabel,
    #ModuleNameLabel, #ModuleNameTitleLabel,
    #SNLabel, #SNTitleLabel {
        background-color: %1;
        border-top: none;
        color: %2;
        font-weight: 400;
        font-size: 12px;
    }
)").arg(bgColor, textColor);
}

void MainWindow::setupListAnimations()
{
    connect(ui->RegisteredModulesListView, &QListWidget::itemEntered,
            this, &MainWindow::onItemEntered);
    ui->RegisteredModulesListView->setIconSize(QSize(18, 18));
}

void MainWindow::onItemEntered(QListWidgetItem *item)
{
    if (!item || item == currentSelectedItem) return;
    animateItemHover(item);
}

void MainWindow::animateItemHover(QListWidgetItem *item)
{
    const QString currentStyle = ui->RegisteredModulesListView->styleSheet();
    const bool dark = isDarkTheme();

    const QString hoverStyle = currentStyle + (dark
        ? R"(QListWidget::item:hover:!selected {
               background-color: rgba(59, 130, 246, 0.15);
               border: 1px solid rgba(59, 130, 246, 0.3);
               border-radius: 6px;
               padding: 8px 12px 8px 8px;
           })"
        : R"(QListWidget::item:hover:!selected {
               background-color: #f3f4f6;
               border: 1px solid #6b7280;
               border-radius: 6px;
               padding: 8px 12px 8px 8px;
           })");

    ui->RegisteredModulesListView->setStyleSheet(hoverStyle);
}

void MainWindow::checkSingleModule(TListItem* item)
{
    if (!item || item->skipConnect()) return;

    if (ConnectModule(item)) {
        updateModuleConnectionStatus(item, true);
    } else {
        item->setSkipConnect(true);
    }
}

void MainWindow::updateModuleConnectionStatus(TListItem* item, bool connected)
{
    if (!item) return;

    if (connected) {
        const QIcon connectedIcon(":/img/SIm2/NetDeviceCheck.ico");
        item->setIcon(connectedIcon);
        item->setData(Qt::UserRole, "connected");

        QTimer::singleShot(100, [item]() {
            if (!item) return;

            QFont originalFont = item->font();
            QFont boldFont = originalFont;
            boldFont.setBold(true);
            item->setFont(boldFont);

            QTimer::singleShot(300, [item, originalFont]() {
                if (item) {
                    item->setFont(originalFont);
                }
            });
        });
    }
}

void MainWindow::setupButtonsLayout()
{
    ButtonLayoutConfig config;
    config.leftOffset = -10;
    config.buttonSpacing = 30;
    config.buttonWidth = 13;

    configureButtonGeometry(config);
    configureButtonVisibility();
}

void MainWindow::configureButtonGeometry(const ButtonLayoutConfig& config)
{
    const QPoint addButtonPos = ui->AddItemButton->pos();
    const QSize addButtonSize = ui->AddItemButton->size();
    const QPoint updateButtonPos = ui->UpdateItemButton->pos();
    const QSize updateButtonSize = ui->UpdateItemButton->size();
    const QPoint deleteButtonPos = ui->DeleteItemButton->pos();
    const QSize deleteButtonSize = ui->DeleteItemButton->size();

    ui->AddItemButton->setGeometry(
        addButtonPos.x() + config.leftOffset, addButtonPos.y(),
        addButtonSize.width() + config.buttonWidth, addButtonSize.height());

    ui->UpdateItemButton->setGeometry(
        updateButtonPos.x() + config.leftOffset, updateButtonPos.y(),
        updateButtonSize.width() + config.buttonWidth, updateButtonSize.height());

    ui->DeleteItemButton->setGeometry(
        deleteButtonPos.x() + config.leftOffset, deleteButtonPos.y(),
        deleteButtonSize.width() + config.buttonWidth, deleteButtonSize.height());


    ui->ChangeItemButton->setGeometry(
        addButtonPos.x() + config.leftOffset, addButtonPos.y(),
        addButtonSize.width() + config.buttonWidth, addButtonSize.height());


    const int baseY = ui->DeleteItemButton->pos().y() + ui->DeleteItemButton->size().height();

    ui->ChangeItemPasswordButton->setGeometry(
        addButtonPos.x() + config.leftOffset, baseY,
        addButtonSize.width() + config.buttonWidth, addButtonSize.height());

    ui->SecurityParametersButton->setGeometry(
        addButtonPos.x() + config.leftOffset, baseY + config.buttonSpacing,
        addButtonSize.width() + config.buttonWidth, addButtonSize.height());

#ifdef Q_OS_WIN
    ui->groupBox->resize(230, ui->groupBox->height());
    const QPoint spbPos = ui->SecurityParametersButton->pos();
    const QSize spbSize = ui->SecurityParametersButton->size();
    ui->SecurityParametersButton->setGeometry(spbPos.x(), spbPos.y(), 220, spbSize.height());
#endif
}

void MainWindow::configureButtonVisibility()
{
    const QList<QPushButton*> visibleButtons = {
        ui->AddItemButton, ui->UpdateItemButton, ui->DeleteItemButton
    };

    const QList<QPushButton*> hiddenButtons = {
        ui->ChangeItemButton, ui->ChangeItemPasswordButton, ui->SecurityParametersButton
    };

    for (QPushButton* button : visibleButtons) {
        button->show();
    }

    for (QPushButton* button : hiddenButtons) {
        button->hide();
    }
}

void MainWindow::setupButtonSection()
{
    applyButtonSectionStyle(isDarkTheme());
}

void MainWindow::setupInfoTopPanelStyle()
{
    const bool dark = isDarkTheme();
    applyInfoPanelStyle(dark);
    applyLabelsStyle(dark);
}
bool MainWindow::initializeApplication()
{
    ProcessStateDialog processState(this);
#ifdef OS_MAC
    UCSPHasherInitPaths();
#endif
         processState.show("Перевірка цілісності програми");
           if (!UCSPHasherCheckFiles(TRUE)) {
       #ifndef _DEBUG
               processState.hide();
               QMessageBox::critical(nullptr,"Повідомлення оператору",
                                               "Виникла помилка при перевірці цілісності програми.\n"
                                               "Цілісність пошкоджено або не може бути перевірено.\n"
                                               "Необхідна переінсталяція програми");
               QCoreApplication::exit(-1);
               return false;
       #else
               setWindowTitle(windowTitle() + "(цілісність пошкоджено)");
       #endif
           }

       processState.hide();
    processState.show("Завантаження та ініціалізація бібліотек");
    if (!Gryada301::Load()) {
        processState.hide();
        QMessageBox::critical(nullptr, "Повідомлення оператору",
                              "Виникла помилка при завантаженні "
                              "бібліотеки взаємодії з криптомодулем");
        QCoreApplication::exit(-1);
        return false;
    }

    processState.show("Завантаження модуля QR-коду");
    if (!QRCodeLoad()) {
        Gryada301::Unload();
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Виникла помилка при завантаженні "
                              "бібліотеки роботи з QR-кодами");
        QCoreApplication::exit(-1);
        return false;
    }

    if (!QRCodeGetInterface(&pIQRCode)) {
        QRCodeUnload();
        Gryada301::Unload();
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Виникла помилка при ініціалізації "
                              "бібліотеки роботи з QR-кодами");
        QCoreApplication::exit(-1);
        return false;
    }

    processState.show("Завантаження криптопровайдера");
    pCryptoProvider = new NCHostCP();
    if (!pCryptoProvider->Load()) {
        delete pCryptoProvider;
        pCryptoProvider = nullptr;

        QRCodeUnload();
        Gryada301::Unload();
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Виникла помилка при завантаженні "
                              "криптографічної бібліотеки вузла");
        QCoreApplication::exit(-1);
        return false;
    }

    pICryptoProvider = pCryptoProvider->GetInterface();
    pICryptoProviderEx = pCryptoProvider->GetInterfaceEx();
    if (!pICryptoProvider || !pICryptoProviderEx) {
        if (pICryptoProviderEx) pCryptoProvider->FreeInterfaceEx(pICryptoProviderEx);
        if (pICryptoProvider)    pCryptoProvider->FreeInterface(pICryptoProvider);

        pCryptoProvider->Unload();
        delete pCryptoProvider;
        pCryptoProvider = nullptr;

        QRCodeUnload();
        Gryada301::Unload();
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Виникла помилка при ініціалізації "
                              "криптографічної бібліотеки вузла");
        QCoreApplication::exit(-1);
        return false;
    }

    DWORD dwError = pICryptoProvider->Initialize(nullptr, TRUE);
    if (dwError != NC_HOST_CP_ERROR_NONE) {
        pCryptoProvider->FreeInterface(pICryptoProvider);
        pCryptoProvider->FreeInterfaceEx(pICryptoProviderEx);
        pCryptoProvider->Unload();
        delete pCryptoProvider;
        pCryptoProvider = nullptr;

        QRCodeUnload();
        Gryada301::Unload();
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Виникла помилка при ініціалізації "
                              "криптографічної бібліотеки вузла");
        QCoreApplication::exit(-1);
        return false;
    }

    processState.hide();

    pModulesList = new NCMsList(HKEY_LOCAL_MACHINE);
    pModule = nullptr;
    ModulePassword.clear();

    return true;
}

#ifndef OS_NIX
QString ConvertAnsiToQString(const QByteArray& ansiName) {
    PWSTR pwszName = nullptr;
    if (StringToWString(ansiName.constData(), &pwszName, 1251) && pwszName != nullptr) {
        QString result = QString::fromWCharArray(pwszName);
        delete[] pwszName;
        return result;
    }
    return QString::fromLocal8Bit(ansiName);
}
bool ConvertQStringToAnsi(const QString& str, PSTR* outAnsi)
{
    if (!outAnsi)
        return false;

    *outAnsi = nullptr;

    const wchar_t* pwsz = reinterpret_cast<const wchar_t*>(str.utf16());

    BOOL res = WStringToString(pwsz, 0, outAnsi, 1251);

    if (res == FALSE || *outAnsi == nullptr) {
        *outAnsi = nullptr;
        return false;
    }

    return true;
}
#endif // !OS_NIX

void MainWindow::AddModuleToListView(const QString& ModuleName,
                                     const QString& SN,const QString& Address,
                                     const QStringList& InitialPorts)
{

    TListItem* Item = new TListItem();
    QIcon icon;

    icon.addPixmap(QPixmap(":/img/SIm2/NetDevice.ico"),QIcon::Normal);
    icon.addPixmap(QPixmap(":/img/SIm2/NetDevice.ico"),QIcon::Selected);
    Item->setText(ModuleName);
    Item->setIcon(icon);
    Item->setSN(SN);
    Item->setAddress(Address);
    Item->setInitialPorts(InitialPorts);

    constexpr int itemHeight = 40;
    Item->setSizeHint(QSize(Item->sizeHint().width(), itemHeight));

    ui->RegisteredModulesListView->addItem(Item);
}

bool MainWindow::IsModuleInListView(const QString& ModuleName)const
{
    return !ui->RegisteredModulesListView->findItems(ModuleName,Qt::MatchFixedString).isEmpty();
}

bool MainWindow::IsModuleSNInUse(const QString& SN) const {
    const int itemCount = ui->RegisteredModulesListView->count();
    for (int i = 0;i< itemCount; ++i) {
        auto* item = static_cast<TListItem*>(ui->RegisteredModulesListView->item(i));
        if (item && item->getSN() == SN) {
            return true;
        }
    }
    return false;
}

void MainWindow::UpdateRegisteredModulesListView(){
    ui->RegisteredModulesListView->clear();
    StringList* rawList = nullptr;
    if (!pModulesList->EnumModules(&rawList)) {
        DefaultSelectionUpdate();
        return;
    }
    auto pList = std::unique_ptr<StringList>(rawList);
    const int itemsCount = pList->GetItemsCount();
    std::array<CHAR,NCM_SN_LENGTH+1>szSN{};
    std::array<CHAR,NCM_ADDRESS_MAX_LENGTH+1>szAddress{};
    std::array<CHAR,NCM_PORT_MAX_LENGTH+1>szInitialPort{};
    for (int i = 0;i < itemsCount; ++i) {
        const auto& currentItem= pList->GetItem(i);
#ifndef OS_NIX
        QString moduleName = ConvertAnsiToQString(currentItem);
#endif
        if (!pModulesList->GetModule(currentItem, szSN.data(),
                                    szAddress.data(), nullptr)) {
            continue;
        }
        QStringList initialPorts;
        for (INT iPoint = 1; iPoint <= NCM_INITIAL_POINTS ; ++iPoint) {
            if (!pModulesList->GetModuleInitialPort(currentItem, iPoint,
                                                   szInitialPort.data()) ||
                szInitialPort[0] == '\0'){
                break;
            }
            initialPorts.append(QString::fromLocal8Bit(szInitialPort.data()));
        }
        AddModuleToListView(
#ifndef OS_NIX
            moduleName,
#else
            QString::fromLocal8Bit(currentItem),
#endif
            szSN.data(),
            szAddress.data(),
            initialPorts
        );
    }
    if (!Gryada301::LocateModules() &&
        ui->RegisteredModulesListView->count() != 0) {
        QMessageBox::warning(this, "Повідомлення оператору",
                            "Не знайдено жодного зареєстрованого криптомодуля"
                            "через бібліотеку взаємодії з криптомодулем");
        }
    DefaultSelectionUpdate();
}

void MainWindow::DefaultSelectionUpdate(){
    ui->ChangeItemButton->hide();
    ui->DeleteItemButton->hide();
    ui->ChangeItemPasswordButton->hide();
    ui->SecurityParametersButton->hide();
    ui->AddItemButton->show();

    const bool hasModules = ui->RegisteredModulesListView->count() > 0;
    ui->ImageLabel->setPixmap(QPixmap(hasModules?":/img/SIm2/SelectInsertImage.ico"
                                                 :":/img/SIm2/InfoImage.ico"));
    ui->InfoLabel->show();
    ui->InfoLabel->setText(hasModules?QStringLiteral("Оберіть модуль зі списку")
                                      :QStringLiteral("Не зареєстровано жодного модуля"));

    ui->groupBox->setFixedHeight(121);
    const std::array<QWidget*,8>LabelsToHide={
        ui->ModuleNameTitleLabel, ui->ModuleNameLabel,
        ui->SNTitleLabel, ui->SNLabel,
        ui->AddressTitleLabel, ui->AddressLabel,
        ui->InitialPortsTitleLabel, ui->InitialPortsLabel
    };

    for (auto* label : LabelsToHide) {
        label->hide();
    }
}

void MainWindow::RegisteredModulesListViewSelectItem(QListWidgetItem *item)
{
    auto* moduleItem = static_cast<TListItem*>(item);

    ui->groupBox->setFixedHeight(159);
    ui->AddItemButton->hide();
    ui->ChangeItemButton->show();
    ui->DeleteItemButton->show();
    ui->ChangeItemPasswordButton->show();
    ui->SecurityParametersButton->show();

    ui->ImageLabel->setPixmap(QPixmap(":/img/SIm2/SelectInsertImage.ico"));
    ui->ImageLabel->show();
    ui->InfoLabel->setText("Інформація про модуль:");

    auto showLabel = [](QLabel* titleLabel, QLabel* valueLabel, const QString& text) {
        titleLabel->show();
        valueLabel->show();
        valueLabel->setText(text);
    };

    showLabel(ui->ModuleNameTitleLabel, ui->ModuleNameLabel,moduleItem->text());
    showLabel(ui->SNTitleLabel, ui->SNLabel,moduleItem->getSN());
    showLabel(ui->AddressTitleLabel, ui->AddressLabel,moduleItem->getAddress());

    const QStringList& initialPorts = moduleItem->getInitialPorts();
    QString initialPortsText = initialPorts.isEmpty()
                                   ? "Не визначені"
                                   :initialPorts.join(", ");
    showLabel(ui->InitialPortsTitleLabel, ui->InitialPortsLabel,initialPortsText);
}

void MainWindow::AddExtendedMenuItemFrameItemLabelClick()
{
    const QString defaultBroadcastAddress = "255.255.255.255";
    QMessageBox messageBox;
    std::unique_ptr<ModuleParamsDialog> dialog = std::make_unique<ModuleParamsDialog>();

    while (true) {
        if (dialog->exec() == QDialog::Accepted) {
            QString ModuleName   = dialog->getModuleName();
            QString SN           = dialog->getSN();
            QString Address      = dialog->getAddress();
            QStringList InitialPorts = dialog->getInitialPorts();

            if (IsModuleInListView(ModuleName)) {
                messageBox.information(this, "Повідомлення оператору",
                                       "Модуль із вказаною назвою вже зареєстрований");
                continue;
            }
            if (IsModuleSNInUse(SN)) {
                messageBox.information(this, "Повідомлення оператору",
                                       "Вказаний серійний номер вже має інший "
                                       "зареєстрований модуль");
                continue;
            }

#ifndef OS_NIX // Windows - ConvertQStringToAnsi для CP1251
            
            PSTR moduleNameAnsi = nullptr;
            if (!ConvertQStringToAnsi(ModuleName, &moduleNameAnsi)) {
                messageBox.critical(this, "Помилка", "Не вдалося конвертувати ім'я модуля у CP1251");
                return;
            }
#else // Unix (Linux/macOS)

            QByteArray moduleNameBA = ModuleName.toLocal8Bit();
            moduleNameBA.append('\0');
            PSTR moduleNameAnsi = (PSTR)moduleNameBA.data();
#endif

            if (!pModulesList->AddModule(moduleNameAnsi)) {
                messageBox.critical(this, "Повідомлення оператору",
                                    "Виникла помилка при додаванні модуля у системний реєстр");
#ifndef OS_NIX
                delete[] moduleNameAnsi;
#endif
                return;
            }

            QByteArray snBA = SN.toLocal8Bit();
            snBA.append('\0');
            QByteArray addressBA = Address.toLocal8Bit();
            addressBA.append('\0');
            QByteArray broadcastBA = defaultBroadcastAddress.toLocal8Bit();
            broadcastBA.append('\0');

            if (!pModulesList->SetModule(moduleNameAnsi,
                                        (PSTR)snBA.data(),
                                        (PSTR)addressBA.data(),
                                        (PSTR)broadcastBA.data())) {
                pModulesList->DeleteModule(moduleNameAnsi);
#ifndef OS_NIX
                delete[] moduleNameAnsi;
#endif
                messageBox.critical(this, "Повідомлення оператору",
                                    "Виникла помилка при встановленні параметрів модуля у системному реєстрі");
                return;
                                        }

            for (INT iPoint = 1; iPoint <= NCM_INITIAL_POINTS; ++iPoint) {
                QString port = (iPoint <= InitialPorts.size()) ? InitialPorts.at(iPoint-1) : "";
                QByteArray portBA = port.toLocal8Bit();
                portBA.append('\0');

                if (!pModulesList->SetModuleInitialPort(moduleNameAnsi,
                                                        iPoint,
                                                        (PSTR)portBA.data())) {
                    pModulesList->DeleteModule(moduleNameAnsi);
#ifndef OS_NIX
                    delete[] moduleNameAnsi;
#endif
                    messageBox.critical(this, "Повідомлення оператору",
                                        "Виникла помилка при встановленні TCP-порта початкової точки доступу модуля у системному реєстрі");
                    return;
                                                        }
            }

#ifndef OS_NIX
            delete[] moduleNameAnsi;
#endif
            break;
        } else {
            return;
        }
    }

    UpdateRegisteredModulesListView();
}



void MainWindow::ChangeExtendedMenuItemFrameItemLabelClick()
{
    const QString defaultBroadcastAddress = "255.255.255.255";
    if(ui->RegisteredModulesListView->selectedItems().count()!=1)
        return;
    QMessageBox messageBox(this);
    std::unique_ptr<ModuleParamsDialog> dialog = std::make_unique<ModuleParamsDialog>();
    TListItem *item = static_cast<TListItem*>(ui->RegisteredModulesListView->selectedItems().at(0));
    QString ModuleName   = item->text();
    QString SN           = item->getSN();
    QString Address      = item->getAddress();
    QStringList InitialPorts = item->getInitialPorts();

    dialog->SetupStartInfo(ModuleName,SN,Address, InitialPorts);
    dialog->DenyNameEdit();

    while (true) {
        if (dialog->exec() == QDialog::Accepted) {
            QString newSN = dialog->getSN();
            if (newSN != SN && IsModuleSNInUse(newSN)) {
                messageBox.information(this,
                                       "Повідомлення оператору",
                                       "Вказаний серійний номер вже має інший зареєстрований модуль");
                continue;
            }
            SN = newSN;
            Address  = dialog->getAddress();
            InitialPorts = dialog->getInitialPorts();

#ifndef OS_NIX
            PSTR moduleNameAnsi = nullptr;
            if (!ConvertQStringToAnsi(ModuleName, &moduleNameAnsi)) {
                return;
            }
#else
            QByteArray nameBA = ModuleName.toLocal8Bit();
#endif

            QByteArray snBA = SN.toLocal8Bit();
            QByteArray addressBA = Address.toLocal8Bit();
            QByteArray broadcastBA = defaultBroadcastAddress.toLocal8Bit();

            if (!pModulesList->SetModule(
#ifndef OS_NIX
                    moduleNameAnsi,
#else
                    (PSTR)nameBA.data(),
#endif
                    (PSTR)snBA.data(),
                    (PSTR)addressBA.data(),
                    (PSTR)broadcastBA.data())) {
                messageBox.critical(this, "Повідомлення оператору",
                                     "Виникла помилка при встановленні параметрів модуля у системному реєстрі");
#ifndef OS_NIX
                delete[] moduleNameAnsi;
#endif
                return;
            }
            for (INT iPoint = 1; iPoint <= NCM_INITIAL_POINTS; ++iPoint) {
                QString port = InitialPorts.value(iPoint-1,"");
                QByteArray portBA = port.toLocal8Bit();
                if (!pModulesList->SetModuleInitialPort(
#ifndef OS_NIX
                        moduleNameAnsi,
#else
                        (PSTR)nameBA.data(),
#endif
                        iPoint,
                        (PSTR)portBA.data())) {

                    QByteArray deleteNameBA = ModuleName.toLocal8Bit();
                    pModulesList->DeleteModule((PSTR)deleteNameBA.data());
                    messageBox.critical(this, "Повідомлення оператору",
                                         "Виникла помилка при встановленні TCP-порта початкової точки доступу модуля у системному реєстрі");
#ifndef OS_NIX
                    delete[] moduleNameAnsi;
#endif
                    return;
                }
            }
#ifndef OS_NIX
            delete[] moduleNameAnsi;
#endif
            break;
        } else {
            return;
        }
    }
    UpdateRegisteredModulesListView();
}


void MainWindow::DeleteExtendedMenuItemFrameItemLabelClick()
{
    if(ui->RegisteredModulesListView->selectedItems().count()!=1) {
        return;
    }
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Повідомлення оператору");
    msgBox.setText("Видалити модуль?");
    msgBox.setIcon(QMessageBox::Question);
    QPushButton *yesButton = msgBox.addButton("Так",QMessageBox::YesRole);
    QPushButton *noButton = msgBox.addButton("Ні",QMessageBox::NoRole);
    msgBox.setDefaultButton(yesButton);

    int result = msgBox.exec();

    QMessageBox::StandardButton userResponse;
    if (msgBox.clickedButton() == yesButton) {
        userResponse = QMessageBox::Yes;
    } else {
        userResponse = QMessageBox::No;
    }

    if (userResponse == QMessageBox::Yes) {
        QString moduleName = ui->RegisteredModulesListView->selectedItems().at(0)->text();
        
#ifndef OS_NIX
        PSTR moduleNameAnsi = nullptr;
        if (!ConvertQStringToAnsi(moduleName, &moduleNameAnsi)) {
            return;
        }
        
        if (!pModulesList->DeleteModule(moduleNameAnsi)) {
            QMessageBox::critical(this,
                                  "Повідомлення оператору",
                                  "Виникла помилка при видаленні модуля з системного реєстру");
            delete[] moduleNameAnsi;
            return;
        }
        
        delete[] moduleNameAnsi;
#else
        QByteArray nameBA = moduleName.toLocal8Bit();
        if (!pModulesList->DeleteModule((PSTR)(nameBA.data()))) {
            QMessageBox::critical(this,
                                  "Повідомлення оператору",
                                  "Виникла помилка при видаленні модуля з системного реєстру");
            return;
        }
#endif
    }
    UpdateRegisteredModulesListView();
}

void MainWindow::ChangePasswordExtendedMenuItemFrameItemLabelClick(){
    TListItem* item = dynamic_cast<TListItem*>(ui->RegisteredModulesListView->currentItem());
    if (!item)
        return;

    if (!ConnectModule(item))
        return;
    ChangePassword dialog(this);
    dialog.setPassword(ModulePassword);

    if (dialog.exec() != QDialog::Accepted)
        return;

    QString newPassword = dialog.getPassword();
    std::string passwordStr = newPassword.toStdString();
    char* pszPassword = passwordStr.data();
    DWORD dwError = pModule->ChangePassword(pszPassword);

    if (dwError != G301_SUCCESS) {
        QMessageBox::critical(this,
                              QStringLiteral("Повідомлення оператору"),
                              QStringLiteral("Не вдалося змінити пароль користувача в модулі"));

        DisconnectModule();
        return;
    }

    QMessageBox::information(this,
                             QStringLiteral("Повідомлення оператору"),
                             QStringLiteral("Пароль користувача в модулі змінено успішно"));

    DisconnectModule();

    ConnectModule(item);

   UpdateRegisteredModulesListView();
}

void MainWindow::ClientSecurityExtendedMenuItemFrameItemLabelClick(){
    QListWidgetItem* selectedItem = ui->RegisteredModulesListView->currentItem();
    if (!selectedItem)
        return;

    auto* moduleItem = static_cast<TListItem*>(selectedItem);

    if(!ConnectModule(moduleItem)){
        return;
    }
    ProcessStateDialog processState(this);
    processState.show("Отримання параметрів з криптомодуля");

    CHAR		szImageVersion[G301_IMAGE_VERSION_LENGTH + 1];
    UINT		uiImageVersion;
    DWORD		dwError;

    dwError = pModule->GetInfo(nullptr, nullptr,
                               szImageVersion, nullptr, nullptr);
    if(dwError == G301_SUCCESS)
    {
        if(!pModule->StringToImageVersion(szImageVersion,
                                           &uiImageVersion))
        {
            uiImageVersion = 0;
        }
    }
    else
        uiImageVersion = 0;

    if(uiImageVersion < G301_IMAGE_COMPATIBLE9_VERSION){
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Модуль не підтримує встановлення параметрів безпеки користувача");
        return;
    }

    G301_CLIENT_SECURITY ClientSec = {};

    dwError = pModule->GetClientSecurity(&ClientSec);
    if(dwError != G301_SUCCESS){
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                              "Виникла помилка при отриманні параметрів безпеки користувача з криптомодуля");
        DisconnectModule();
        return;
    }

    processState.hide();

    ClientSecurity dialog(this);
    dialog.setModuleName(selectedItem->text());
    dialog.setClientSecurity(&ClientSec);
    dialog.setImageVersion(uiImageVersion);
    dialog.setCryptoProvider(pICryptoProviderEx);
    dialog.setQRCodeInterface(pIQRCode);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    processState.show("Зміна параметрів безпеки користувача у криптомодулі");

    dwError = pModule->SetClientSecurity(&ClientSec);

    if(dwError != G301_SUCCESS)
    {
        processState.hide();
        QMessageBox::critical(this, "Повідомлення оператору",
                                      "Виникла помилка при змінні параметрів безпеки користувача у криптомодулі");
        DisconnectModule();
        return;
    }
    processState.hide();

    QMessageBox::information(this,
                             "Повідомлення оператору",
                             "Параметри безпеки користувача у криптомодулі змінено");

    DisconnectModule();
    ConnectModule(moduleItem);
    UpdateRegisteredModulesListView();
}

bool MainWindow::ConnectModule(TListItem *Item){
    if(pModule != nullptr && pConnectedModuleItem == Item)
        return true;

    if(pModule != nullptr && pConnectedModuleItem != Item) {
        DisconnectModule();
    }

    ProcessStateDialog processState(this);
    int    nPoint;
    QString Login, Password, OTP;

    ::Login loginDialog(this);
    if(loginDialog.exec() == QDialog::Accepted) {
        Login= loginDialog.getLogin();
        Password = loginDialog.getPassword();
        OTP = loginDialog.getOTP();
        nPoint = loginDialog.getPoint();
    }else{
        return false;
    }

    QMessageBox messageBox;

    pModule = new Gryada301();
    if (!pModule) {
        return false;
    }

    if (!pModule->Load()) {
        delete pModule;
        pModule = nullptr;
        return false;
    }

    ModulePassword = Password;

    if(!pModule->ConnectModule((DWORD) ((ui->RegisteredModulesListView->row(Item) * NCM_INITIAL_POINTS) +
                                         nPoint))){
        processState.hide();
        QMessageBox::critical(this,
                           "Повідомлення оператору",
                           "Виникла помилка при підключенні до криптомодуля");
        delete pModule;
        pModule = nullptr;
        ModulePassword = "";
        return false;
    }

    BOOL    blReTried = FALSE;
    DWORD  dwError;

    QString CompletePassword = G301_LOGIN_PASSWORD_DELIMITER +
                               Login +
                               G301_LOGIN_PASSWORD_DELIMITER +
                               Password +
                               OTP;
    while(true){
        QByteArray passwordBytes = CompletePassword.toUtf8();
        dwError = pModule->LogOn(passwordBytes.data());

        if(dwError == G301_SUCCESS){
            break;
        }
        if(dwError == G301_ALREADY_LOGGED && !blReTried){
            while (pModule->LogOff()==G301_SUCCESS){

            }
            blReTried = TRUE;
            continue;
        }

        pModule->DisconnectModule();

        if(dwError == G301_ERROR_WRONG_PASSWORD){
            QMessageBox::critical(this,
                                  "Повідомлення оператору",
                                  "Невірне скорочене ім'я користувача чи пароль доступу до криптомодуля");
        }else{
            QMessageBox::critical(this,
                                  "Повідомлення оператору",
                                  "Виникла помилка при автентифікації у модулі");
        }
        delete pModule;
        pModule = nullptr;
        ModulePassword = "";

        return false;
    }

    if (!pModule->F.ConnectModule) {
        return false;
    }
    processState.hide();
    QIcon icon(":/img/SIm2/NetDeviceCheck.ico");
    Item->setIcon(icon);
    pConnectedModuleItem = Item;
    return true;
}

void MainWindow::DisconnectModule(){
    if(pModule == nullptr)
        return;

    pModule->LogOff();
    pModule->DisconnectModule();

    delete pModule;
    pModule = nullptr;
    ModulePassword = "";

    for(int i = 0; i< ui->RegisteredModulesListView->count(); i++){
        QListWidgetItem *item = ui->RegisteredModulesListView->item(i);
        if(item!=nullptr){
            QIcon icon (":/img/SIm2/NetDevice.ico");
            item->setIcon(icon);
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (obj == ui->RegisteredModulesListView->viewport() && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QModelIndex clickedIndex = ui->RegisteredModulesListView->indexAt(mouseEvent->pos());
        bool isSelected = ui->RegisteredModulesListView->selectionModel()->isSelected(clickedIndex);

        if (!isSelected && mouseEvent->button() == Qt::LeftButton) {
            ui->RegisteredModulesListView->clearSelection();
            ui->RegisteredModulesListView->selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
            DefaultSelectionUpdate();
        }
    }
    return QObject::eventFilter(obj, event);
}


void MainWindow::ShowContextMenu(const QPoint& pos){
    QModelIndex item = ui->RegisteredModulesListView->indexAt(pos);
    QMenu contextMenu(this);
    contextMenu.addAction("Додати..", [this](){AddExtendedMenuItemFrameItemLabelClick();});

    if (ui->RegisteredModulesListView->selectionModel()->isSelected(item)) {
        contextMenu.addAction("Змінити",[this](){ChangeExtendedMenuItemFrameItemLabelClick();});
        contextMenu.addSeparator();
        contextMenu.addAction("Видалити",[this](){DeleteExtendedMenuItemFrameItemLabelClick();});
    }
    contextMenu.exec(ui->RegisteredModulesListView->mapToGlobal(pos));
}

