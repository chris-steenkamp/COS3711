#include "staffmember.h"
#include <QMetaEnum>
#include <QDebug>

StaffMember::StaffMember(QObject *parent) : QObject(parent) {
}

StaffMember::~StaffMember() {
    qDebug() << "Deleting " << toString() << '\n';
}

StaffMember::StaffMember(QString name, QDate birthdate, QString appType, QObject *parent)
    : QObject(parent), m_Birthdate(birthdate), m_Name(name) {
    setAppointmentType(appType);
}

QString StaffMember::name() const {
    return m_Name;
}

QDate StaffMember::birthdate()const {
    return m_Birthdate;
}

QString StaffMember::appointmentType() const {
    static const QMetaEnum e = staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("AppointmentType"));

    return e.key(m_AppointmentType);
}

QString StaffMember::toString() const {
    return QString("%0 (%2) born on %1").arg(name()).arg(birthdate().toString("yyyy/MM/dd")).arg(appointmentType());
}

void StaffMember::setName(QString name) {
    m_Name = name;
}

void StaffMember::setBirthdate(QDate birthdate) {
    m_Birthdate = birthdate;
}

void StaffMember::setAppointmentType(QString appType) {
    static const QMetaEnum e = staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("AppointmentType"));
    for (int i = 0; i < e.keyCount(); ++i) {
        if (QString(e.key(i)).toUpper() == appType.toUpper()) {
            m_AppointmentType = static_cast<AppointmentType>(e.keyToValue(e.key(i)));
           return;
        }
    }

    qDebug() << QString("Unable to convert %0 to AppointmentType enum.").arg(appType);
}

bool StaffMember::operator==(const StaffMember& other) {
    return m_Name == other.m_Name && m_Birthdate == other.m_Birthdate && m_AppointmentType == other.m_AppointmentType;
}
