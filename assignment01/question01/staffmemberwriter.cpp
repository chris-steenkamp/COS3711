#include <QStringList>
#include "staffmemberwriter.h"
#include "staffmember.h"

StaffMemberWriter::StaffMemberWriter(QIODevice *device) : m_Stream(device)
{
}

bool StaffMemberWriter::write(const StaffMember &member) {
    QStringList list;
    list << member.name() << member.birthdate().toString("yyyy/MM/dd") << member.appointmentType();
    m_Stream << list.join('\t') << '\n';
    return !(m_Stream.status() == QTextStream::WriteFailed);
}

StaffMemberWriter& StaffMemberWriter::operator<<(const StaffMember &member) {
    write(member);
    return *this;
}
