#ifndef STAFFMEMBER_H
#define STAFFMEMBER_H

#include <QObject>
#include <QDate>
#include <QString>

class StaffMember : public QObject
{
    Q_OBJECT
public:
    explicit StaffMember(QObject *parent = 0);
    StaffMember(QString name, QDate birthdate, QString appType, QObject *parent=0);
    ~StaffMember();
    enum AppointmentType { Permanent, PartTime, Contract };
    Q_ENUMS(AppointmentType)

    QString name() const;
    QDate birthdate() const;
    QString appointmentType() const;
    QString toString() const;

    void setName(QString name);
    void setBirthdate(QDate birthdate);
    void setAppointmentType(QString appointmentType);

    bool operator==(const StaffMember&);
private:
    QDate m_Birthdate;
    QString m_Name;
    AppointmentType m_AppointmentType;
};

#endif // STAFFMEMBER_H
