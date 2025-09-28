
#ifdef OS_NIX
#include <sys/socket.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif //OS_NIX
#include <QMessageBox>

#include "moduleparamsdialog.h"
#include "ui_moduleparamsdialog.h"
#include "./Settings/NCMsList.h"

ModuleParamsDialog::ModuleParamsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModuleParamsDialog)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);

    connect(ui->OKButton,&QPushButton::clicked,this,&ModuleParamsDialog::OKButtonClick);
    connect(ui->CancelButton,&QPushButton::clicked,this,&ModuleParamsDialog::reject);
    connect(ui->InitialPortsCheckBox,&QCheckBox::clicked,
            this,&ModuleParamsDialog::InitialPortsCheckBoxClick);
}

ModuleParamsDialog::~ModuleParamsDialog()
{
    delete ui;
}


QString ModuleParamsDialog::getModuleName(){
    return ui->NameEdit->text();
}

QString ModuleParamsDialog::getSN(){
    return ui->SNEdit->text();
}

QString ModuleParamsDialog::getAddress(){
    return ui->AddressEdit->text();
}
QStringList ModuleParamsDialog::getInitialPorts(){
    return QStringList({
        ui->InitialPort1Edit->text(),ui->InitialPort2Edit->text(),
        ui->InitialPort3Edit->text(),ui->InitialPort4Edit->text(),
        ui->InitialPort5Edit->text(),ui->InitialPort6Edit->text()
    });
}

void ModuleParamsDialog::SetupStartInfo(QString& ModuleName,QString& SN,
                                        QString& Address,QStringList& InitialPorts){
    const std::array<std::pair<QLabel*, QLineEdit*>,NCM_INITIAL_POINTS>initialPortsWidget={
                                                                                                 {
                                                                                                     {ui->InitialPort1Label, ui->InitialPort1Edit},
                                                                                                     {ui->InitialPort2Label, ui->InitialPort2Edit},
                                                                                                     {ui->InitialPort3Label, ui->InitialPort3Edit},
                                                                                                     {ui->InitialPort4Label, ui->InitialPort4Edit},
                                                                                                     {ui->InitialPort5Label, ui->InitialPort5Edit},
                                                                                                     {ui->InitialPort6Label, ui->InitialPort6Edit}
                                                                                                 }};

    if (InitialPorts.size()==NCM_INITIAL_POINTS) {
        ui->InitialPortsCheckBox->setChecked(true);
        for (size_t i=0 ; i<NCM_INITIAL_POINTS ; ++i) {
            auto& [label,edit]=initialPortsWidget[i];
            edit->setText(InitialPorts.at(i));
            edit->setEnabled(true);
            label->setEnabled(true);
        }
    }else {
        ui->InitialPortsCheckBox->setChecked(false);
        for (const auto& [label,edit] : initialPortsWidget) {
            edit->clear();
            label->setEnabled(false);
            edit->setEnabled(false);
        }
    }
    ui->NameEdit->setText(ModuleName);
    ui->AddressEdit->setText(Address);
    ui->SNEdit->setText(SN);
    return;
}

void ModuleParamsDialog::DenyNameEdit(){
    ui->NameEdit->setEnabled(false);
    return;
}

bool ModuleParamsDialog::CheckInteger(QString& integer,int nMin,int nMax){
    bool isInteger;
    int value=integer.toInt(&isInteger);
    return isInteger && value >= nMin&&value <= nMax;
}

bool ModuleParamsDialog::CheckAddress(QString Address){
    if (Address == "255.255.255.255") return true;
    if (Address == "0.0.0.0") return false;
    if (Address.count('.')!=3) return false;
    const QStringList octets = Address.split('.',Qt::KeepEmptyParts);

    for(const QString& octet:octets){
        if(octet.isEmpty() || octet.length()>3)return false;

        if (octet.length()>1 && octet[0] == '0') return false;

        int value = 0;
        for(const QChar& ch : octet){
            if(!ch.isDigit()) return false;
            value = value * 10 + (ch.unicode()- '0');
            if (value >255) return false;
        }
    }
    return true;
}
bool ModuleParamsDialog::CheckSN(QString SN){
    return CheckInteger(SN, NCM_MIN_SN, NCM_MAX_SN);
}

bool ModuleParamsDialog::CheckPort(QString Port){
    return CheckInteger(Port, 1, 65535);
}



void ModuleParamsDialog::InitialPortsCheckBoxClick(bool checked) {
    const std::array<std::pair<QLabel*, QLineEdit*>,NCM_INITIAL_POINTS>initialPorts={
        {
            {ui->InitialPort1Label, ui->InitialPort1Edit},
            {ui->InitialPort2Label, ui->InitialPort2Edit},
            {ui->InitialPort3Label, ui->InitialPort3Edit},
            {ui->InitialPort4Label, ui->InitialPort4Edit},
            {ui->InitialPort5Label, ui->InitialPort5Edit},
            {ui->InitialPort6Label, ui->InitialPort6Edit}
        }
    };
    for (size_t i = 0; i < NCM_INITIAL_POINTS; ++i) {
        auto& [label,edit]=initialPorts[i];

        label->setEnabled(checked);
        edit->setEnabled(checked);
        if (checked) {
            if (edit->text().isEmpty()) {
                edit->setText(QString::number(NCM_INITIAL_POINT_FIRST_PORT + i));
            }
        }else {
            edit->clear();
        }
    }
}


void ModuleParamsDialog::OKButtonClick()
{
    const QString title = QStringLiteral("Повідомлення оператору");

    if (!InputValidator::validateInput(ui->NameEdit,
                                       this,title,QStringLiteral("Не вказано назву модуля"),
                                       [](const QString& text){return !text.trimmed().isEmpty();},QString())) {
        return;
    }
    if (!InputValidator::validateInput(ui->SNEdit,
                                       this,title,QStringLiteral("Не вказано серійний номер модуля"),
                                       [this](const QString& text){return CheckSN(text);},
                                       QStringLiteral("Серійний номер модуля має невірний формат (%1-%2)")
                                           .arg(NCM_MIN_SN).arg(NCM_MAX_SN))) {
        return;
    }
    if (!InputValidator::validateInput(ui->AddressEdit,
                                       this,title,QStringLiteral("Не вказано IP-адресу модуля"),
                                       [this](const QString& text){return CheckAddress(text);},
                                       QStringLiteral("IP-адреса модуля має невірний формат"))) {
        return;
    }
    if (ui->InitialPortsCheckBox->isChecked()) {
        const std::array<QLineEdit*,NCM_INITIAL_POINTS> initialPortsEdit={
            ui->InitialPort1Edit,ui->InitialPort2Edit,
            ui->InitialPort3Edit,ui->InitialPort4Edit,
            ui->InitialPort5Edit,ui->InitialPort6Edit
        };
        for (size_t i=0 ; i<NCM_INITIAL_POINTS ; ++i) {
            QLineEdit* edit=initialPortsEdit[i];
            const QString portText=edit->text();
            if (portText.isEmpty()) {
                QMessageBox::warning(this,
                                     title,
                                     QStringLiteral("Не вказано TCP-порт початкової точки доступу модуля"));
                edit->setFocus();
                return;
            }

            if (!CheckPort(portText)) {
                QMessageBox::warning(this,
                                     title,
                                     QStringLiteral("TCP-порт початкової точки доступу модуля має "
                                                    "невірний формат (1-65535)"));
                edit->setFocus();
                return;
            }
        }
    }
    accept();
}



















