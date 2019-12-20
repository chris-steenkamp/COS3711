#include <QStringList>
#include "staffmemberreader.h"
#include "staffmember.h"

StaffMemberReader::StaffMemberReader(QIODevice* device) : m_Stream(device)
{
}

bool StaffMemberReader::read(StaffMember &member) {
    QStringList list;
    list = m_Stream.readLine().split("\t");
    if (list.size() == 1 && list[0].isEmpty()) {
        return false;
    }

    while (list.size() < 3)
    {
        list << "";
    }

    member.setName(list[0]);
    member.setBirthdate(QDate::fromString(list[1], "yyyy/MM/dd"));
    member.setAppointmentType(list[2]);

    return true;
}

StaffMemberReader& StaffMemberReader::operator>>(StaffMember &member) {
    read(member);
    return *this;
}
