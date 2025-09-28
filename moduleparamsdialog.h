#ifndef MODULEPARAMSDIALOG_H
#define MODULEPARAMSDIALOG_H

#include <QDialog>
#include <QString>
#include <QStringLiteral>
#include <QStringList>
#include <utility>
#include "inputvalidator.h"

namespace Ui {
class ModuleParamsDialog;
}

class ModuleParamsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModuleParamsDialog(QWidget *parent = nullptr);
    ~ModuleParamsDialog();

    QString getModuleName();
    QString getSN();
    QString getAddress();
    QStringList getInitialPorts();
    void SetupStartInfo(QString& ModuleName,QString& SN,
                        QString& Address,QStringList& InitialPorts);
    void DenyNameEdit();

private slots:
    void InitialPortsCheckBoxClick(bool checked);

    void OKButtonClick();

private:
    Ui::ModuleParamsDialog *ui;


    bool CheckInteger(QString& integer,int nMin,int nMax);
    bool CheckAddress(QString Address);
    bool CheckSN(QString SN);
    bool CheckPort(QString Port);
};

#endif // MODULEPARAMSDIALOG_H
