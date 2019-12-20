#include "staffmember.h"
#include "staffmemberfilestore.h"
#include "staffmemberreader.h"
#include "staffmemberwriter.h"

#include <QDebug>
#include <QFile>

StaffMemberFileStore::StaffMemberFileStore(QString filename, QObject *parent) :
    QObject (parent),
    m_StaffList(),
    m_SourceDevice(new QFile(filename))
{
    loadList();
}

StaffMemberFileStore::~StaffMemberFileStore()
{
    printList();
    saveList();

    if (m_SourceDevice->isOpen()) {
        m_SourceDevice->close();
    }

    delete m_SourceDevice;
    m_SourceDevice = 0;
}

void StaffMemberFileStore::loadList() {
    if (m_SourceDevice->open(QIODevice::ReadOnly)) {
        StaffMemberReader reader(m_SourceDevice);
        bool read = false;
        do {
            StaffMember* member = new StaffMember();
            if ((read = reader.read(*member))) {
                member->setParent(this);
                m_StaffList.insert(member->toString(), member);
            }
            else {
                //the last created member is not valid so we need to clean it up
                delete member;
            }
        } while (read);

        m_SourceDevice->close();
    }
}

void StaffMemberFileStore::addMember(QString name, QDate birthdate, QString appType) {
    StaffMember *member = new StaffMember(name, birthdate, appType, this);
    QString key = member->toString();
    if (!m_StaffList.contains(key)) {
        m_StaffList.insert(key, member);
    }
}

void StaffMemberFileStore::saveList() {
    if (m_SourceDevice->open(QIODevice::WriteOnly)) {
        StaffMemberWriter writer(m_SourceDevice);
        for (int i = 0; i < m_StaffList.size(); ++i) {
            writer.write(*m_StaffList.values()[i]);
        }

        m_SourceDevice->close();
    }
}

void StaffMemberFileStore::printList() {
    for (int i = 0; i < m_StaffList.size(); ++i) {
        qDebug() << m_StaffList.values()[i]->toString() << '\n';
    }
}
