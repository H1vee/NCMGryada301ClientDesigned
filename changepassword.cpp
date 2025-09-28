#include "changepassword.h"
#include "ui_changepassword.h"

ChangePassword::ChangePassword(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChangePassword)

{
    ui->setupUi(this);
    ui->PasswordEdit->setEchoMode(QLineEdit::Password);

    connect(ui->OKButton,&QPushButton::clicked,this,&ChangePassword::OKButtonClick);
    connect(ui->CancelButton,&QPushButton::clicked,this,&ChangePassword::reject);
    connect(ui->ShowPasswordCheckBox,&QCheckBox::toggled,this,&ChangePassword::ShowPasswordCheckBoxClick);
    connect(ui->PasswordEdit, &QLineEdit::textChanged,
            this, &ChangePassword::PasswordEditChange);
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::OKButtonClick(){
    const QString title = QStringLiteral("Повідомлення оператору");
    if(!InputValidator::validateInput(ui->PasswordEdit
                                       ,this,title
                                       ,QStringLiteral("Не введений новий пароль доступу до криптомодуля")
                                       ,[](const QString& text){return !text.trimmed().isEmpty();},QString())){
        return;
    }
    if(ui->PasswordRepeatEdit->text().isEmpty()){
        if(!ui->ShowPasswordCheckBox->isChecked()){
            QMessageBox::warning(this,
                                 title,
                                 QStringLiteral("Не введений повтор нового пароля доступу "
                                                "до криптомодуля"));
            ui->PasswordRepeatEdit->setFocus();
            return;
        }
    }
    if(ui->PasswordRepeatEdit->text()!=ui->PasswordEdit->text()){
        QMessageBox::warning(this,
                             title,
                             QStringLiteral("Ведений новий пароль доступу "
                                            "до криптомодуля "
                                            "та його повтор не співпадають"));
        ui->PasswordRepeatEdit->setFocus();
        return;
    }



    if(ui->PasswordEdit->text()== m_currentPassword){
        QMessageBox::warning(this,
                             title,
                             QStringLiteral( "Новий пароль доступу до криптомодуля "
                                            "співпадає із поточним"));
        ui->PasswordEdit->setFocus();
        return;
    }
    m_resultPassword = ui->PasswordEdit->text();
    accept();
}

void ChangePassword::ShowPasswordCheckBoxClick(){
    bool show = ui->ShowPasswordCheckBox->isChecked();

    ui->PasswordEdit->setEchoMode(show ? QLineEdit::Normal : QLineEdit::Password);
    ui->PasswordRepeatEdit->setEchoMode(show ? QLineEdit::Normal : QLineEdit::Password);
    ui->PasswordRepeatEdit->setStyleSheet(show ? "QLineEdit:disabled { color: gray; }" : "");
    ui->PasswordRepeatEdit->setEnabled(!show);

    PasswordEditChange();
}

void ChangePassword::PasswordEditChange(){
    if(ui->ShowPasswordCheckBox->isChecked() &&
        !ui->PasswordRepeatEdit->isEnabled()) {
        ui->PasswordRepeatEdit->setText(ui->PasswordEdit->text());
    }
}

QString ChangePassword::getPassword() const {
    return m_resultPassword;
}

void ChangePassword::setPassword(const QString &password) {
    m_currentPassword = password;
}
