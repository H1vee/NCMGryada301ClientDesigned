#ifndef PROCESSSTATEDIALOG_H
#define PROCESSSTATEDIALOG_H

#include <QProgressDialog>
#include <QApplication>
#include <QString>
class ProcessStateDialog
{
public:
    ProcessStateDialog(QWidget *parent = nullptr);
    ~ProcessStateDialog();

    void show(const QString &message);
    void hide();
    void setTitle(const QString &title);

private:
    QProgressDialog *m_dialog;
    QWidget *m_parent;
};

#endif // PROCESSSTATEDIALOG_H
