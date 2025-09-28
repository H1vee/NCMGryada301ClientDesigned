#ifndef CLIENTSECURITY_H
#define CLIENTSECURITY_H

#include <QDialog>
#include <QMessageBox>
#include <QScreen>
#include <QTimer>
#include <QClipboard>
#include <QGuiApplication>

#include "QRCode.h"
#include "Gryada301.h"
#include "NCHostCP.h"

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else // OS_NIX
#include <windows.h>
#endif // OS_NIX
namespace Ui {
class ClientSecurity;
}

class ClientSecurity : public QDialog
{
    Q_OBJECT

public:
    explicit ClientSecurity(QWidget *parent = nullptr);

    void setModuleName(const QString& ModuleName);
    void setQRCodeInterface(IQRCode* pIQRCode);
    void setCryptoProvider(PNC_HOST_CP_INTERFACE_EX pICryptoProviderEx);
    void setClientSecurity(PG301_CLIENT_SECURITY pClientSecurity);
    void setImageVersion(UINT uiImageVersion);

    int exec() override;

    ~ClientSecurity();

    //PNC_HOST_CP_INTERFACE_EX pICryptoProviderEx = nullptr;

private slots:
    void OKButtonClick();
    void OTPInUseCheckBoxClick();
    void DenyOthersPasswordChangeCheckBoxClick();
    void OTPTimeStepComboBoxChange(int);
    void OTPDigitsComboBoxChange(int);
    void OTPKeyCopyButtonClick();
    void OTPKeyReGenerateButtonClick();


private:
    Ui::ClientSecurity *ui;
    bool GenerateOTPParamsQRCode();
    bool GenerateOTPParams();
    void initializeDialog();
    void SetupCheckBox();
    bool loadSecuritySettings();
    bool saveSecuritySettings();
    void SetupWindowLayout();

    QPoint originalOKPos;
    QPoint originalCancelPos;
    QPoint originalBottomLinePos;

    bool blChanged = false;
    bool m_loading = false;

    QString ModuleName;
    UINT uiImageVersion;

    IQRCode 	*pIQRCode;
    PNC_HOST_CP_INTERFACE_EX
        pICryptoProviderEx;
    PG301_CLIENT_SECURITY pClientSecurity;
};

#endif // CLIENTSECURITY_H
