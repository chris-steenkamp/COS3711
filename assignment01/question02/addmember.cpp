#include "addmember.h"
#include "staffmember.h"

#include <QComboBox>
#include <QDateEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QMetaEnum>
#include <QPushButton>
#include <QVBoxLayout>

AddMember::AddMember(QWidget *parent) :
    QWidget(parent),
    m_NameLineEdit(new QLineEdit(this)),
    m_BirthdateDateEdit(new QDateEdit(this)),
    m_AppointmentTypeComboBox(new QComboBox(this))
{
    setWindowTitle("Add Staff Member");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(tr("&Name"), m_NameLineEdit);
    formLayout->addRow(tr("&Birthdate"), m_BirthdateDateEdit);
    formLayout->addRow(tr("A&ppointment Type"), m_AppointmentTypeComboBox);

    QMetaObject meta = StaffMember::staticMetaObject;
    QMetaEnum e = meta.enumerator(meta.indexOfEnumerator("AppointmentType"));

    for (int i = 0; i < e.keyCount(); ++i) {
        QVariant var(e.keysToValue(e.key(i)));
        m_AppointmentTypeComboBox->addItem(e.key(i), var);
    }

    mainLayout->addLayout(formLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *m_BtnAdd(new QPushButton(tr("&Add"),this));
    QPushButton *m_BtnClose(new QPushButton(tr("&Close"), this));
    buttonLayout->addWidget(m_BtnAdd);
    buttonLayout->addWidget(m_BtnClose);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(m_BtnAdd, SIGNAL(clicked(bool)), this, SLOT(handleAddClicked()));
    connect(m_BtnClose, SIGNAL(clicked(bool)), this, SLOT(handleCloseClicked()));
}

void AddMember::handleAddClicked()
{
    if (m_NameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Invalid Name", "Please enter the name of the staff member.", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    StaffMember::AppointmentType appType = static_cast<StaffMember::AppointmentType>(m_AppointmentTypeComboBox->currentData().value<int>());

    emit memberCreated(m_NameLineEdit->text(),
                       m_BirthdateDateEdit->date(),
                       appType);

    m_NameLineEdit->clear();
    m_NameLineEdit->setFocus();
}

void AddMember::handleCloseClicked()
{
    close();
}
