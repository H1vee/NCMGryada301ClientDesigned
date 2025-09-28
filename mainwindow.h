#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QString>
#include <QPropertyAnimation>
#include <QPoint>
#include <QStringList>

#ifdef OS_NIX
#include "./OSIntermediate/OSIntermediate.h"
#else // OS_NIX
#include <windows.h>
#include "StringCoder.h"
#endif // OS_NIX

#include "./Settings/NCMsList.h"
#include "changepassword.h"
#include "clientsecurity.h"
#include "tlistitem.h"
#include "Gryada301.h"
#include "login.h"
#include "processstatedialog.h"
#include "UCSPHasher.h"
#include "QRCode.h"
#include "NCHostCP.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void RegisteredModulesListViewSelectItem(QListWidgetItem *item);

    void AddExtendedMenuItemFrameItemLabelClick();

    void ChangeExtendedMenuItemFrameItemLabelClick();

    void DeleteExtendedMenuItemFrameItemLabelClick();

    void ChangePasswordExtendedMenuItemFrameItemLabelClick();

    void ClientSecurityExtendedMenuItemFrameItemLabelClick();

    void ShowContextMenu(const QPoint&);

    void onItemEntered(QListWidgetItem *item);
    void animateItemHover(QListWidgetItem *item);
    void checkSingleModule(TListItem* item);


private:
    void AddModuleToListView(const QString& ModuleName,
                             const QString& SN,const QString& Address,
                             const QStringList& InitialPorts);
    bool IsModuleInListView(const QString& ModuleName) const;
    bool IsModuleSNInUse(const QString& SN) const;
    void UpdateRegisteredModulesListView();
    void DefaultSelectionUpdate();
    bool ConnectModule(TListItem *Item);
    void DisconnectModule();
    bool initializeApplication();
    void setupButtonsLayout();
    void setupListAnimations();
    void setupButtonSection();
    void setupInfoTopPanelStyle();
    void updateTheme();
    bool isDarkTheme() const;

    struct ButtonLayoutConfig {
        int leftOffset;
        int buttonSpacing;
        int buttonWidth;
    };

    void applyListViewStyle(bool darkTheme);
    void applyButtonSectionStyle(bool darkTheme);
    void applyInfoPanelStyle(bool darkTheme);
    void applyLabelsStyle(bool darkTheme);
    void applyButtonsStyle(bool darkTheme);

    void updateModuleConnectionStatus(TListItem* item, bool connected);

    void configureButtonGeometry(const ButtonLayoutConfig& config);
    void configureButtonVisibility();
    //void RegisteredModulesListViewSelectItem(
    //        TObject *Sender, TListItem *Item, bool Selected);


    QString getListWidgetStyleSheet(bool darkTheme) const;
    QString getButtonSectionStyleSheet(bool darkTheme) const;
    QString getInfoTopPanelStyleSheet(bool darkTheme) const;
    QString getInfoLabelsStyleSheet(bool darkTheme) const ;
    QString getButtonsStyleSheet(bool darkTheme) const;


    Ui::MainWindow *ui;
    NCMsList 	*pModulesList;
    IQRCode		*pIQRCode;
    NCHostCP	*pCryptoProvider;
    PNC_HOST_CP_INTERFACE
        pICryptoProvider;
    PNC_HOST_CP_INTERFACE_EX
        pICryptoProviderEx;
    Gryada301	*pModule;
    TListItem   *pConnectedModuleItem;
    QListWidgetItem *currentSelectedItem;
    QString ModulePassword;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
};
#endif // MAINWINDOW_H
