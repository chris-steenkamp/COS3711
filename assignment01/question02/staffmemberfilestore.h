#ifndef STAFFMEMBERFILESTORE_H
#define STAFFMEMBERFILESTORE_H

#include <QDate>
#include <QHash>
#include <QObject>
#include <QString>

#include "staffmember.h"
class QIODevice;

class StaffMemberFileStore: public QObject
{
    Q_OBJECT
public:
    StaffMemberFileStore(QString filename, QObject* parent = 0);
    ~StaffMemberFileStore();
public slots:
    void addMember(QString name, QDate birthdate, StaffMember::AppointmentType appointmentType);
private:
    QHash<QString, StaffMember*> m_staffList;
    QIODevice *m_sourceDevice;

    void loadList();
    void saveList();
    void printList();
};

#endif // STAFFMEMBERFILESTORE_H
