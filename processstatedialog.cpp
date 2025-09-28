#include "processstatedialog.h"
ProcessStateDialog::ProcessStateDialog(QWidget *parent)
    : m_parent(parent)
    , m_dialog(nullptr)
{
}

ProcessStateDialog::~ProcessStateDialog()
{
    if (m_dialog) {
        delete m_dialog;
    }
}

void ProcessStateDialog::show(const QString &message)
{
    if (!m_dialog) {
        m_dialog = new QProgressDialog(m_parent);
        m_dialog->setWindowTitle("Ініціалізація програми");
        m_dialog->setWindowModality(Qt::WindowModal);
        m_dialog->setMinimumDuration(0);
        m_dialog->setCancelButton(nullptr);
        m_dialog->setRange(0, 0); // Indeterminate progress
    }

    m_dialog->setLabelText(message);
    m_dialog->show();
    QApplication::processEvents();
}

void ProcessStateDialog::hide()
{
    if (m_dialog) {
        m_dialog->hide();
    }
}

void ProcessStateDialog::setTitle(const QString &title)
{
    if (m_dialog) {
        m_dialog->setWindowTitle(title);
    }
}
