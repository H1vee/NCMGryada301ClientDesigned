#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    setupLogin();
    connect(ui->OKButton,&QPushButton::clicked,this,&Login::OKButtonClick);
    connect(ui->ShowOTPCheckBox,&QCheckBox::toggled,this,&Login::ShowOTPCheckBoxClick);
    connect(ui->ShowPasswordCheckBox,&QCheckBox::toggled,this,&Login::ShowPasswordCheckBoxClick);
    connect(ui->CancelButton,&QPushButton::clicked,this,&Login::reject);
}

Login::~Login()
{
    delete ui;
}

void Login::OKButtonClick(){

    const QString title = QStringLiteral("Повідомлення оператору");
    if(!InputValidator::validateInput(ui->LoginEdit,
                                       this,title,QStringLiteral("Не введене скорочене ім'я користувача криптомодуля"),
                                       [](const QString& text){return !text.trimmed().isEmpty();},QString())){
        return;
    }
    if(!InputValidator::validateInput(ui->PasswordEdit,
                                       this,title,QStringLiteral("Не введений пароль доступу користувача до криптомодуля"),
                                       [](const QString& text){return !text.trimmed().isEmpty();},QString())){
        return;
    }
    if(!ui->OTPEdit->text().isEmpty()){
        if(ui->OTPEdit->text().length() < G301_CLIENT_OTP_DIGITS_MIN){
            QMessageBox::warning(this,
                                 title,
                                 QStringLiteral("OTP-пароль занадто короткий (має бути від %1 до %2 цифр)")
                                     .arg(G301_CLIENT_OTP_DIGITS_MIN)
                                     .arg(G301_CLIENT_OTP_DIGITS_MAX));
            ui->OTPEdit->setFocus();
            return;
        }
    }

    QString CompletePassword = QString(G301_LOGIN_PASSWORD_DELIMITER) +
                               ui->LoginEdit->text() +
                               G301_LOGIN_PASSWORD_DELIMITER +
                               ui->PasswordEdit->text() +
                               ui->OTPEdit->text();

    if(CompletePassword.length() > G301_MAX_PASSWORD_LENGTH){
        QMessageBox::warning(this,
                             title,
                             QStringLiteral("Підсумковий пароль доступу користувача "
                                     "до криптомодуля занадто довгий "
                                     "(має бути не більше %1 символів разом із роздільниками, "
                                     "скороченим ім'ям та OTP-паролем)")
                                 .arg(G301_MAX_PASSWORD_LENGTH));
        ui->LoginEdit->setFocus();
        return;
    }

    m_login = ui->LoginEdit->text();
    m_password = ui->PasswordEdit->text();
    m_otp = ui->OTPEdit->text();
    m_point = ui->PointComboBox->currentIndex();

    accept();
}

void Login::ShowOTPCheckBoxClick(){
    ui->OTPEdit->setEchoMode(ui->ShowOTPCheckBox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);
}
void Login::ShowPasswordCheckBoxClick(){
    ui->PasswordEdit->setEchoMode(ui->ShowPasswordCheckBox->isChecked() ? QLineEdit::Normal : QLineEdit::Password);
}

void Login::setupLogin(){
    ui->PointComboBox->clear();
    for(INT nPoint = 0; nPoint < NCM_INITIAL_POINTS; nPoint++) {
        QString text = QString("Точка доступа %1 (%2)")
                           .arg(nPoint + 1)
                           .arg(NCM_INITIAL_POINT_FIRST_PORT + nPoint);
        ui->PointComboBox->addItem(text);
    }
    ui->PointComboBox->setCurrentIndex(0);

    ui->OTPEdit->setMaxLength(G301_CLIENT_OTP_DIGITS_MAX);
}

QString Login::getLogin() const{
    return m_login;
}
QString Login::getPassword() const{
    return m_password;
}
QString Login::getOTP() const{
    return m_otp;
}
int Login::getPoint() const{
    return m_point;
}
