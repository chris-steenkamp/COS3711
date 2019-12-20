#include "staffmember.h"
#include "staffmemberfilestore.h"
#include "staffmemberreader.h"
#include "staffmemberwriter.h"

#include <QDebug>
#include <QFile>

StaffMemberFileStore::StaffMemberFileStore(QString filename, QObject *parent) :
    QObject (parent),
    m_staffList(),
    m_sourceDevice(new QFile(filename))
{
    loadList();
}

StaffMemberFileStore::~StaffMemberFileStore()
{
    printList();

    saveList();

    qDeleteAll(m_staffList);
    m_staffList.clear();

    if (m_sourceDevice->isOpen()) {
        m_sourceDevice->close();
    }

    delete m_sourceDevice;
    m_sourceDevice = 0;
}

void StaffMemberFileStore::loadList() {
    if (m_sourceDevice->open(QIODevice::ReadOnly)) {
        StaffMemberReader reader(m_sourceDevice);
        bool read = false;
        do {
            StaffMember* member = new StaffMember();
            if ((read = reader.read(*member))) {
                m_staffList.insert(member->property("toString").value<QString>(), member);
            }
        } while (read);

        m_sourceDevice->close();
    }
}

void StaffMemberFileStore::addMember(QString name, QDate birthdate, StaffMember::AppointmentType appType) {
    StaffMember *member = new StaffMember(name, birthdate, appType, this);
    member->setObjectName(member->property("toString").toString());;
    if (!m_staffList.contains(member->objectName())) {
        m_staffList.insert(member->objectName(), member);
    }
}

void StaffMemberFileStore::saveList() {
    if (m_sourceDevice->open(QIODevice::WriteOnly)) {
        StaffMemberWriter writer(m_sourceDevice);
        for (int i = 0; i < m_staffList.size(); ++i) {
            writer.write(*m_staffList.values()[i]);
        }

        m_sourceDevice->close();
    }
}

void StaffMemberFileStore::printList() {
    for (int i = 0; i < m_staffList.size(); ++i) {
        qDebug() << m_staffList.values()[i]->property("toString").value<QString>() << '\n';
    }
}
