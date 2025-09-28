#include "clientsecurity.h"
#include "ui_clientsecurity.h"

ClientSecurity::ClientSecurity(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClientSecurity)
{
    ui->setupUi(this);

    SetupWindowLayout();

    originalOKPos = ui->OKButton->pos();
    originalCancelPos =ui->CancelButton->pos();
    originalBottomLinePos = ui->BottomLine->pos();

    SetupCheckBox();
    initializeDialog();
    connect(ui->CancelButton,&QPushButton::clicked,
            this,&ClientSecurity::reject);
    connect(ui->OKButton,&QPushButton::clicked,
            this,&ClientSecurity::OKButtonClick);
    connect(ui->OTPKeyCopyButton,&QPushButton::clicked,
            this,&ClientSecurity::OTPKeyCopyButtonClick);
    connect(ui->OTPKeyRegenerateButton,&QPushButton::clicked,
            this,&ClientSecurity::OTPKeyReGenerateButtonClick);
    connect(ui->DenyOthersPasswordChangeCheckBox,&QCheckBox::toggled,
            this,&ClientSecurity::DenyOthersPasswordChangeCheckBoxClick);
    connect(ui->OTPInUseCheckBox,&QCheckBox::toggled,
            this,&ClientSecurity::OTPInUseCheckBoxClick);
    connect(ui->OTPTimeStepComboBox, &QComboBox::currentIndexChanged,
            this, &ClientSecurity::OTPTimeStepComboBoxChange);
    connect(ui->OTPDigitsComboBox, &QComboBox::currentIndexChanged,
            this, &ClientSecurity::OTPDigitsComboBoxChange);

}


ClientSecurity::~ClientSecurity()
{
    delete ui;
}


void ClientSecurity::SetupCheckBox(){
    ui->OTPDigitsComboBox->clear();
    ui->OTPTimeStepComboBox->clear();

    for(UINT uiTimeStep = G301_CLIENT_OTP_TIME_STEP_MIN;
         uiTimeStep <= G301_CLIENT_OTP_TIME_STEP_MAX;
         uiTimeStep += G301_CLIENT_OTP_TIME_STEP_INC)
    {
        ui->OTPTimeStepComboBox->addItem(QString::number(uiTimeStep));
    }

    int timeStepIndex = ui->OTPTimeStepComboBox->findText(
        QString::number(G301_CLIENT_OTP_TIME_STEP_DEF));
    if (timeStepIndex >= 0)
        ui->OTPTimeStepComboBox->setCurrentIndex(timeStepIndex);


    for(UINT uiDigits = G301_CLIENT_OTP_DIGITS_MIN;
         uiDigits <= G301_CLIENT_OTP_DIGITS_MAX;
         uiDigits++)
    {
        ui->OTPDigitsComboBox->addItem(QString::number(uiDigits));
    }

    int digitsIndex = ui->OTPDigitsComboBox->findText(
        QString::number(G301_CLIENT_OTP_DIGITS_DEF));
    if (digitsIndex >= 0)
        ui->OTPDigitsComboBox->setCurrentIndex(digitsIndex);
}

void ClientSecurity::initializeDialog(){
    ui->OTPInUseCheckBox->setChecked(false);

    int otpWidgetHeight = ui->OTPWidget->height();

    ui->OTPWidget->setVisible(false);
    ui->OTPParamsNoteImage->setVisible(false);
    ui->OTPParamsNoteLabel->setVisible(false);

    QPoint okPos = ui->OKButton->pos();
    QPoint cancelPos = ui->CancelButton->pos();
    QPoint bottomLinePos = ui->BottomLine->pos();


    ui->OKButton->move(okPos.x(), okPos.y() - otpWidgetHeight);
    ui->CancelButton->move(cancelPos.x(), cancelPos.y() - otpWidgetHeight);
    ui->BottomLine->move(bottomLinePos.x(),bottomLinePos.y() - 370);
    resize(width(), height() - otpWidgetHeight);

    int timeStepIndex = ui->OTPTimeStepComboBox->findText(QString::number(G301_CLIENT_OTP_TIME_STEP_DEF));
    if (timeStepIndex != -1) {
        ui->OTPTimeStepComboBox->setCurrentIndex(timeStepIndex);
    }

    int digitsIndex = ui->OTPDigitsComboBox->findText(QString::number(G301_CLIENT_OTP_DIGITS_DEF));
    if (digitsIndex != -1) {
        ui->OTPDigitsComboBox->setCurrentIndex(digitsIndex);
    }

    ui->OTPKeyEdit->clear();
}

bool ClientSecurity::loadSecuritySettings(){
    if(uiImageVersion < G301_IMAGE_COMPATIBLE9_VERSION)
        return false;

    m_loading = true;

    if(pClientSecurity->uiFlags &
        G301_CLIENT_SECURITY_FLAG_CANT_CHANGE_PASSWORD)
    {
        ui->CantChangePasswordCheckBox->setChecked(true);
    }
    else
        ui->CantChangePasswordCheckBox->setChecked(false);

    if(pClientSecurity->uiFlags &
        G301_CLIENT_SECURITY_FLAG_MUST_CHANGE_PASSWORD)
    {
        ui->MustChangePasswordCheckBox->setChecked(true);
    }
    else
        ui->MustChangePasswordCheckBox->setChecked(false);

    if(pClientSecurity->uiFlags &
        G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_CHANGE_PASSWORD)
    {
        ui->DenyOthersPasswordChangeCheckBox->setChecked(true);
    }
    else
        ui->DenyOthersPasswordChangeCheckBox->setChecked(false);

    if(pClientSecurity->uiFlags &
        G301_CLIENT_SECURITY_FLAG_MUST_USE_OTP)
    {
        ui->MustUseOTPCheckBox->setChecked(true);
    }
    else
        ui->MustUseOTPCheckBox->setChecked(false);

    if(pClientSecurity->uiFlags &
        G301_CLIENT_SECURITY_FLAG_OTP_IN_USE)
    {
        ui->OTPInUseCheckBox->setChecked(true);

        ui->OTPTimeStepComboBox->setCurrentIndex(ui->OTPTimeStepComboBox->findText(QString::number(pClientSecurity->uiOTPTimeStep)));
        ui->OTPDigitsComboBox->setCurrentIndex(ui->OTPDigitsComboBox->findText(QString::number(pClientSecurity->uiOTPDigits)));

        CHAR	szKey[NC_HOST_CP_OTP_KEY_LENGTH * 2 + 1];

        pICryptoProviderEx->EncodeBase32(pClientSecurity->bOTPKey,
                                         pClientSecurity->uiOTPKeyLength,
                                         szKey);

        ui->OTPKeyEdit->setText(szKey);
    }else{
        ui->OTPInUseCheckBox->setChecked(false);
    }

    m_loading = false;
    return true;
}

bool ClientSecurity::saveSecuritySettings() {
    if(ui->DenyOthersPasswordChangeCheckBox->isChecked()){
        pClientSecurity->uiFlags |=
            G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_CHANGE_PASSWORD;
    }else{
        pClientSecurity->uiFlags &=
            (~G301_CLIENT_SECURITY_FLAG_DENY_OTHERS_CHANGE_PASSWORD);
    }

    if(ui->OTPInUseCheckBox->isChecked()){
        pClientSecurity->uiFlags |=
            G301_CLIENT_SECURITY_FLAG_OTP_IN_USE;

        pClientSecurity->uiOTPTimeStep = ui->OTPTimeStepComboBox->currentText().toUInt();
        pClientSecurity->uiOTPDigits = ui->OTPDigitsComboBox->currentText().toUInt();

        pClientSecurity->uiOTPKeyLength = G301_CLIENT_OTP_KEY_LENGTH;

        QByteArray otpKeyBytes = ui->OTPKeyEdit->text().toLocal8Bit();
        pICryptoProviderEx->DecodeBase32(otpKeyBytes.data(),pClientSecurity->bOTPKey,
                                         pClientSecurity->uiOTPKeyLength);
    }else{
        pClientSecurity->uiFlags &=
            (~G301_CLIENT_SECURITY_FLAG_OTP_IN_USE);

        pClientSecurity->uiOTPTimeStep = 0;
        pClientSecurity->uiOTPDigits = 0;
        pClientSecurity->uiOTPKeyLength = 0;

        ZeroMemory((PVOID) pClientSecurity->bOTPKey,
                   sizeof(pClientSecurity->bOTPKey));
    }
    return true;
}

void ClientSecurity::SetupWindowLayout()
{
#ifdef Q_OS_LINUX
    QRect mustUseOTPRect = ui->MustUseOTPCheckBox->geometry();
    ui->MustUseOTPCheckBox->setGeometry(mustUseOTPRect.x() + 13, mustUseOTPRect.y(), mustUseOTPRect.width()+15, mustUseOTPRect.height());

    QRect otpInUseRect = ui->OTPInUseCheckBox->geometry();
    ui->OTPInUseCheckBox->setGeometry(otpInUseRect.x() + 13, otpInUseRect.y(), otpInUseRect.width()+15, otpInUseRect.height());

    QRect mustChangePasswordRect = ui->MustChangePasswordCheckBox->geometry();
    ui->MustChangePasswordCheckBox->setGeometry(mustChangePasswordRect.x(), mustChangePasswordRect.y(), mustChangePasswordRect.width() + 50, mustChangePasswordRect.height());

    QRect cantChangePasswordRect = ui->CantChangePasswordCheckBox->geometry();
    ui->CantChangePasswordCheckBox->setGeometry(cantChangePasswordRect.x(), cantChangePasswordRect.y(), cantChangePasswordRect.width() + 50, cantChangePasswordRect.height());

    QRect qrCodeLabelRect = ui->OTPQRCodeLabel->geometry();
    ui->OTPQRCodeLabel->setGeometry(qrCodeLabelRect.x(), qrCodeLabelRect.y() + 12, qrCodeLabelRect.width() + 25, qrCodeLabelRect.height());

    QRect otpInfoLabelRect = ui->OTPInfoLabel->geometry();
    ui->OTPInfoLabel->setGeometry(otpInfoLabelRect.x(), otpInfoLabelRect.y(), otpInfoLabelRect.width() + 40, otpInfoLabelRect.height());

    QRect otpKeyLabelRect = ui->OTPKeyLabel->geometry();
    ui->OTPKeyLabel->setGeometry(otpKeyLabelRect.x(), otpKeyLabelRect.y(), otpKeyLabelRect.width() + 20, otpKeyLabelRect.height());

    QRect OTPTimeStepLabelRect = ui->OTPTimeStepLabel->geometry();
    ui->OTPTimeStepLabel->setGeometry(OTPTimeStepLabelRect.x(), OTPTimeStepLabelRect.y(), OTPTimeStepLabelRect.width()+ 7, OTPTimeStepLabelRect.height());

    QRect OTPDigitsLabelRect = ui->OTPDigitsLabel->geometry();
    ui->OTPDigitsLabel->setGeometry(OTPDigitsLabelRect.x(), OTPDigitsLabelRect.y(), OTPDigitsLabelRect.width()+ 7, OTPDigitsLabelRect.height());

    QRect timeStepComboRect = ui->OTPTimeStepComboBox->geometry();
    ui->OTPTimeStepComboBox->setGeometry(timeStepComboRect.x() + 16, timeStepComboRect.y(), timeStepComboRect.width() - 10, timeStepComboRect.height());

    QRect digitsComboRect = ui->OTPDigitsComboBox->geometry();
    ui->OTPDigitsComboBox->setGeometry(digitsComboRect.x() + 16, digitsComboRect.y(), digitsComboRect.width() - 10, digitsComboRect.height());


    QRect keyRegenerateButtonRect = ui->OTPKeyRegenerateButton->geometry();
    ui->OTPKeyRegenerateButton->setGeometry(keyRegenerateButtonRect.x() - 5, keyRegenerateButtonRect.y(), keyRegenerateButtonRect.width() + 15, keyRegenerateButtonRect.height());

    QRect keyCopyButtonRect = ui->OTPKeyCopyButton->geometry();
    ui->OTPKeyCopyButton->setGeometry(keyCopyButtonRect.x() - 5, keyCopyButtonRect.y(), keyCopyButtonRect.width() + 15, keyCopyButtonRect.height());


    QRect paramsNoteImageRect = ui->OTPParamsNoteImage->geometry();
    ui->OTPParamsNoteImage->setGeometry(paramsNoteImageRect.x(), paramsNoteImageRect.y() - 10, paramsNoteImageRect.width(), paramsNoteImageRect.height());


    QRect paramsNoteLabelRect = ui->OTPParamsNoteLabel->geometry();
    ui->OTPParamsNoteLabel->setGeometry(paramsNoteLabelRect.x(), paramsNoteLabelRect.y() - 10, paramsNoteLabelRect.width(), paramsNoteLabelRect.height() + 17);
    QFont noteFont = ui->OTPParamsNoteLabel->font();
    noteFont.setStretch(95);
    ui->OTPParamsNoteLabel->setFont(noteFont);
    ui->OTPParamsNoteLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->OTPParamsNoteLabel->setWordWrap(true);
    QRect frameRect = ui->frame->geometry();
    ui->frame->setGeometry(frameRect.x()+12, frameRect.y(), frameRect.width()-3, frameRect.height());


    QRect otpParametersLabelRect = ui->OTPParametersLabel->geometry();
    ui->OTPParametersLabel->setGeometry(otpParametersLabelRect.x(), otpParametersLabelRect.y(), otpParametersLabelRect.width() + 15, otpParametersLabelRect.height());
#elif defined(Q_OS_MACOS)

    QRect frameRect = ui->frame->geometry();
    ui->frame->setGeometry(frameRect.x()-24, frameRect.y(), frameRect.width()+21, frameRect.height());

    QRect otpInfoLabelRect = ui->OTPInfoLabel->geometry();
    ui->OTPInfoLabel->setGeometry(otpInfoLabelRect.x(), otpInfoLabelRect.y(), otpInfoLabelRect.width(), otpInfoLabelRect.height());

    QRect otpKeyLabelRect = ui->OTPKeyLabel->geometry();
    ui->OTPKeyLabel->setGeometry(otpKeyLabelRect.x(), otpKeyLabelRect.y(), otpKeyLabelRect.width() + 20, otpKeyLabelRect.height());

    QRect OTPTimeStepLabelRect = ui->OTPTimeStepLabel->geometry();
    ui->OTPTimeStepLabel->setGeometry(OTPTimeStepLabelRect.x(), OTPTimeStepLabelRect.y(), OTPTimeStepLabelRect.width()+ 7, OTPTimeStepLabelRect.height());

    QRect OTPDigitsLabelRect = ui->OTPDigitsLabel->geometry();
    ui->OTPDigitsLabel->setGeometry(OTPDigitsLabelRect.x()-7, OTPDigitsLabelRect.y(), OTPDigitsLabelRect.width()+ 7, OTPDigitsLabelRect.height());

    QRect qrCodeLabelRect = ui->OTPQRCodeLabel->geometry();
    ui->OTPQRCodeLabel->setGeometry(qrCodeLabelRect.x(), qrCodeLabelRect.y() + 12, qrCodeLabelRect.width() + 25, qrCodeLabelRect.height());

    QList<QLabel*> labels = {
        ui->OTPInfoLabel,
        ui->OTPKeyLabel,
        ui->OTPDigitsLabel,
        ui->OTPTimeStepLabel
    };

    QRect keyRegenerateButtonRect = ui->OTPKeyRegenerateButton->geometry();
    ui->OTPKeyRegenerateButton->setGeometry(keyRegenerateButtonRect.x(), keyRegenerateButtonRect.y()-2, keyRegenerateButtonRect.width()+1, keyRegenerateButtonRect.height()+6);

    QRect keyCopyButtonRect = ui->OTPKeyCopyButton->geometry();
    ui->OTPKeyCopyButton->setGeometry(keyCopyButtonRect.x(), keyCopyButtonRect.y()-2, keyCopyButtonRect.width()+1, keyCopyButtonRect.height()+6);

    QFont buttonFont = ui->OTPKeyCopyButton->font();
    buttonFont.setPointSize(10);
    ui->OTPKeyCopyButton->setFont(buttonFont);
    ui->OTPKeyRegenerateButton->setFont(buttonFont);


    QRect digitsComboRect = ui->OTPDigitsComboBox->geometry();
    ui->OTPDigitsComboBox->setGeometry(digitsComboRect.x() -13, digitsComboRect.y(), digitsComboRect.width(), digitsComboRect.height());


    QFont OTPNoteLabelFont = ui->OTPParamsNoteLabel->font();
    OTPNoteLabelFont.setPointSize(12);
    ui->OTPParamsNoteLabel->setFont(OTPNoteLabelFont);

    QRect paramsNoteImageRect = ui->OTPParamsNoteImage->geometry();
    ui->OTPParamsNoteImage->setGeometry(paramsNoteImageRect.x(), paramsNoteImageRect.y() - 6, paramsNoteImageRect.width(), paramsNoteImageRect.height());

    QRect paramsNoteLabelRect = ui->OTPParamsNoteLabel->geometry();
    ui->OTPParamsNoteLabel->setGeometry(paramsNoteLabelRect.x(), paramsNoteLabelRect.y() - 6, paramsNoteLabelRect.width(), paramsNoteLabelRect.height() + 17);


    for (QLabel* label : labels) {
        QFont labelFont = label->font();
        labelFont.setPointSize(10);
        label->setFont(labelFont);
    }
#else
    QRect qrCodeLabelRect = ui->OTPQRCodeLabel->geometry();
    ui->OTPQRCodeLabel->setGeometry(qrCodeLabelRect.x(), qrCodeLabelRect.y() + 12, qrCodeLabelRect.width(), qrCodeLabelRect.height());
#endif
}


void ClientSecurity::OKButtonClick(){
    if(ui->OTPInUseCheckBox->isChecked() && ui->OTPTimeStepComboBox->currentIndex()==-1){
        QMessageBox::warning(
            this,
            QStringLiteral("Повідомлення оператору"),
            QStringLiteral("Не вказано часовий інтервал формування OTP-пароля"));

        ui->OTPTimeStepComboBox->setFocus();

        return;
    }
    if(ui->OTPInUseCheckBox->isChecked() && ui->OTPDigitsComboBox->currentIndex()==-1){
        QMessageBox::warning(
            this,
            QStringLiteral("Повідомлення оператору"),
            QStringLiteral("Не вказано довжину OTP-пароля"));

        ui->OTPDigitsComboBox->setFocus();

        return;
    }

    if(ui->OTPInUseCheckBox->isChecked() && ui->OTPKeyEdit->text().isEmpty()){
        QMessageBox::warning(
            this,
            QStringLiteral("Повідомлення оператору"),
            QStringLiteral("Ключ формування OTP-пароля не згенеровано"));

        ui->OTPInUseCheckBox->setFocus();

        return;
    }

    if (ui->OTPParamsNoteLabel->isVisible()) {
        QString message = ui->OTPParamsNoteLabel->text() +
                          ".\nВстановити нові параметри безпеки користувача у модулі?";

        QMessageBox msgBox(this);

        msgBox.setWindowTitle(QStringLiteral("Повідомлення оператору"));
        msgBox.setText(message);
        msgBox.setIcon(QMessageBox::Warning);

        QPushButton *yesButton = msgBox.addButton(QStringLiteral("Так"), QMessageBox::YesRole);
        QPushButton *noButton = msgBox.addButton(QStringLiteral("Ні"), QMessageBox::NoRole);

        msgBox.setDefaultButton(noButton);
        msgBox.exec();

        if (msgBox.clickedButton() != yesButton) {
            return;
        }
    }

    accept();
}

void ClientSecurity::OTPInUseCheckBoxClick(){
    if (!m_loading) {
        blChanged = true;
    }

    if (!ui->OTPInUseCheckBox->isChecked()) {
        if (ui->OTPWidget->isVisible()) {
            ui->OTPWidget->setVisible(false);
            initializeDialog();
            move(QGuiApplication::primaryScreen()->geometry().center() - rect().center());
        }

        int timeStepIndex = ui->OTPTimeStepComboBox->findText(QString::number(G301_CLIENT_OTP_TIME_STEP_DEF));
        if (timeStepIndex != -1) {
            ui->OTPTimeStepComboBox->setCurrentIndex(timeStepIndex);
        }

        int digitsIndex = ui->OTPDigitsComboBox->findText(QString::number(G301_CLIENT_OTP_DIGITS_DEF));
        if (digitsIndex != -1) {
            ui->OTPDigitsComboBox->setCurrentIndex(digitsIndex);
        }

        ui->OTPKeyEdit->clear();
        ui->OTPParamsNoteImage->setVisible(false);
        ui->OTPParamsNoteLabel->setVisible(false);
    }
    else {

        if (isVisible()) {
            if (!GenerateOTPParams())
                return;
        }

        if (!ui->OTPWidget->isVisible()) {
            int otpWidgetHeight = ui->OTPWidget->height();

            ui->OKButton->move(originalOKPos);
            ui->CancelButton->move(originalCancelPos);
            ui->BottomLine->move(originalBottomLinePos);

            ui->OTPWidget->setVisible(true);

            ui->OTPQRCodeLabel->setVisible(true);
            ui->OTPParamsNoteImage->setVisible(true);
            ui->OTPParamsNoteLabel->setVisible(true);

            resize(width(), height() + otpWidgetHeight);
            move(QGuiApplication::primaryScreen()->geometry().center() - rect().center());
        }

       GenerateOTPParamsQRCode();
    }
}

void ClientSecurity::DenyOthersPasswordChangeCheckBoxClick(){
    if (!m_loading) {
        blChanged = true;
    }
}

void ClientSecurity::OTPTimeStepComboBoxChange(int){
    if (!m_loading && ui->OTPInUseCheckBox->isChecked()) {
        blChanged = true;
    }

    if(ui->OTPInUseCheckBox->isChecked()){
        if (!GenerateOTPParams())
                     return;
    }
}

void ClientSecurity::OTPKeyCopyButtonClick(){
    const QString keyText = ui->OTPKeyEdit->text();

    if(!keyText.isEmpty()){
        QGuiApplication::clipboard()->setText(keyText);
    }
}
void ClientSecurity::OTPKeyReGenerateButtonClick(){
    if(!GenerateOTPParams())
        return;
}

void ClientSecurity::OTPDigitsComboBoxChange(int){
    if (!m_loading && ui->OTPInUseCheckBox->isChecked()) {
        blChanged = true;
    }

    if (ui->OTPInUseCheckBox->isChecked()) {
    if (!GenerateOTPParamsQRCode())
        return;
    }
}

bool ClientSecurity::GenerateOTPParamsQRCode(){
    QString codeText = QString("otpauth://totp/МКМ Гряда-301:%1?secret=%2&algorithm=SHA1&digits=%3&period=%4&lock=false&image=https://iit.com.ua/download/productfiles/NetDeviceKey.png")
                           .arg(ModuleName)
                           .arg(ui->OTPKeyEdit->text())
                           .arg(ui->OTPDigitsComboBox->itemText(ui->OTPDigitsComboBox->currentIndex()))
                           .arg(ui->OTPTimeStepComboBox->itemText(ui->OTPTimeStepComboBox->currentIndex()));

    QByteArray encodedCodeText = QUrl::toPercentEncoding(codeText,":/?&=.");
    QString finalCodeText = QString::fromUtf8(encodedCodeText);

    CHAR	szTempFolder[MAX_PATH * 4 + 1];

    GetTempPathA(MAX_PATH * 4, szTempFolder);
    QString tempFolder = QString::fromLocal8Bit(szTempFolder);
    if (tempFolder == "\\tmp\\") {
        strcpy(szTempFolder, "/tmp/");
    }
    CHAR	szCodeImageFile[MAX_PATH * 4 + 1];


    GetTempFileNameA(szTempFolder, "NCMGryada301ClientOTPQRCode",
                    0, szCodeImageFile);
    QString codeImageFile = QString::fromLocal8Bit(szCodeImageFile).replace('\\', '/') + ".png";
    QByteArray codeImageFileBytes = codeImageFile.toLocal8Bit();

    DeleteFileA(codeImageFileBytes.constData());

    if (!pIQRCode->Generate(encodedCodeText.data(),
                            256, 2, QR_CODE_DEF_ECC_LEVEL,
                            codeImageFileBytes.data())) {
        DeleteFileA(codeImageFileBytes.constData());
        QMessageBox::critical(this,
                              "Повідомлення оператору",
                              "Виникла помилка при генерації QR-коду параметрів OTP-паролю");
        ui->OTPKeyEdit->clear();
        return false;
    }

    QPixmap qrPixmap(codeImageFile);
    if (qrPixmap.isNull()) {
        DeleteFileA(codeImageFileBytes.constData());
        QMessageBox::critical(this,
                              "Повідомлення оператору",
                              "Помилка завантаження згенерованого QR-коду");
        ui->OTPKeyEdit->clear();
        return false;
    }

    ui->OTPQRCodeImage->setPixmap(qrPixmap);
    ui->OTPQRCodeImage->setScaledContents(true);

    DeleteFileA(codeImageFileBytes.constData());

    return true;
}
bool ClientSecurity::GenerateOTPParams(){
    BYTE	bKey[G301_CLIENT_OTP_KEY_LENGTH];

    if(pICryptoProviderEx->GenerateRNSequence(bKey,
                                               G301_CLIENT_OTP_KEY_LENGTH) != NC_HOST_CP_ERROR_NONE)
    {
        QMessageBox::critical(this,
                              "Повідомлення оператору",
                              "Виникла помилка при генерації "
                              "ключа формування OTP-пароля ");
        return false;
    }

    CHAR	szKey[NC_HOST_CP_OTP_KEY_LENGTH * 2 + 1];

    if(pICryptoProviderEx->EncodeBase32(bKey,
                                         G301_CLIENT_OTP_KEY_LENGTH,
                                         szKey) != NC_HOST_CP_ERROR_NONE)
    {
        QMessageBox::critical(this,
                              "Повідомлення оператору",
                              "Виникла помилка при перевторенні "
                              "ключа формування OTP-пароля у Base32-строку");
        return false;
    }
    ui->OTPKeyEdit->setText(szKey);

    if(!GenerateOTPParamsQRCode())
        return false;

    ui->OTPParamsNoteImage->setVisible(true);
    ui->OTPParamsNoteLabel->setVisible(true);

    return true;
}

void ClientSecurity::setModuleName(const QString& ModuleName){
    this->ModuleName = ModuleName;
}
void ClientSecurity::setQRCodeInterface(IQRCode* pIQRCode){
    this->pIQRCode = pIQRCode;
}
void ClientSecurity::setCryptoProvider(PNC_HOST_CP_INTERFACE_EX pICryptoProviderEx){
    this->pICryptoProviderEx = pICryptoProviderEx;
}
void ClientSecurity::setClientSecurity(PG301_CLIENT_SECURITY pClientSecurity){
    this->pClientSecurity = pClientSecurity;
}
void ClientSecurity::setImageVersion(UINT uiImageVersion){
    this->uiImageVersion = uiImageVersion;
}

int ClientSecurity::exec() {
    if (pClientSecurity && uiImageVersion >= G301_IMAGE_COMPATIBLE9_VERSION) {
        loadSecuritySettings();
    }
    int result = QDialog::exec();
    if (result == QDialog::Accepted && blChanged) {
        saveSecuritySettings();
    }
    return result;
}
