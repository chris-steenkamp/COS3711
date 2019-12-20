#include "staffmember.h"
#include <QMetaEnum>
#include <QDebug>

StaffMember::StaffMember(QObject *parent) : QObject(parent) {
}

StaffMember::StaffMember(QString name, QDate birthdate, StaffMember::AppointmentType appType, QObject *parent)
    : QObject(parent), m_Birthdate(birthdate), m_Name(name), m_AppointmentType(appType) {
}

QString StaffMember::name() const {
    return m_Name;
}

QDate StaffMember::birthdate()const {
    return m_Birthdate;
}

StaffMember::AppointmentType StaffMember::appointmentType() const {
    return m_AppointmentType;
}

QString StaffMember::appointmentTypeString() const {
    static const QMetaEnum e = staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("AppointmentType"));

    return e.key(m_AppointmentType);
}

QString StaffMember::toString() const {
    return QString("%0 (%2) born on %1").arg(name()).arg(birthdate().toString("yyyy/MM/dd")).arg(appointmentTypeString());
}

void StaffMember::setName(QString name) {
    m_Name = name;
}

void StaffMember::setBirthdate(QDate birthdate) {
    m_Birthdate = birthdate;
}

void StaffMember::setAppointmentType(StaffMember::AppointmentType appType) {
    m_AppointmentType = appType;
}

bool StaffMember::operator==(const StaffMember& other) {
    return m_Name == other.m_Name && m_Birthdate == other.m_Birthdate && m_AppointmentType == other.m_AppointmentType;
}
