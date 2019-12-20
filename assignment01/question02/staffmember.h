#ifndef STAFFMEMBER_H
#define STAFFMEMBER_H

#include <QObject>
#include <QDate>
#include <QString>

class StaffMember : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QDate birthdate READ birthdate WRITE setBirthdate)
    Q_PROPERTY(AppointmentType appointmentType READ appointmentType WRITE setAppointmentType)
    Q_PROPERTY(QString toString READ toString)
    Q_ENUMS(AppointmentType)
public:
    enum AppointmentType { Permanent = 0, PartTime, Contract };
    explicit StaffMember(QObject *parent = 0);
    StaffMember(QString name, QDate birthdate, AppointmentType appType, QObject *parent=0);

    bool operator==(const StaffMember&);
private:
    QDate m_Birthdate;
    QString m_Name;
    AppointmentType m_AppointmentType;

    QString name() const;
    QDate birthdate() const;
    AppointmentType appointmentType() const;
    QString appointmentTypeString() const;
    QString toString() const;

    void setName(QString name);
    void setBirthdate(QDate birthdate);
    void setAppointmentType(AppointmentType appointmentType);
};

//Q_DECLARE_METATYPE(StaffMember::AppointmentType)

#endif // STAFFMEMBER_H
