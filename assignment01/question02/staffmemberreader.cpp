#include <QMetaProperty>
#include <QStringList>
#include "staffmemberreader.h"
#include "staffmember.h"

StaffMemberReader::StaffMemberReader(QIODevice* device) : m_Stream(device)
{
}

bool StaffMemberReader::read(StaffMember &member) {
    static const QMetaObject meta = StaffMember::staticMetaObject;

    QStringList list = m_Stream.readLine().split("\t");
    if (list.size() == 1 && list[0] == "") {
        return false;
    }

    for (int i = 0; i < list.size(); ++i) {
        //Create a kev/value pair of property name, property value for each record which has been read.
        QStringList kvp = list[i].split('=');
        QByteArray propertyName = kvp[0].toUtf8();
        QMetaProperty prop = meta.property(meta.indexOfProperty(propertyName));
        //If the property data type is the AppointmentType enum then we need to cast from int
        if (QString(prop.typeName()) == "AppointmentType") {
            member.setProperty(propertyName, static_cast<StaffMember::AppointmentType>(kvp[1].toInt()));
        }
        else {
            member.setProperty(propertyName, kvp[1]);
        }
    }

    return true;
}

StaffMemberReader& StaffMemberReader::operator>>(StaffMember &member) {
    read(member);
    return *this;
}
