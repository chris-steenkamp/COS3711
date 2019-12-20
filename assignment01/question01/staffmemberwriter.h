#ifndef STAFFMEMBERWRITER_H
#define STAFFMEMBERWRITER_H

#include <QIODevice>
#include <QTextStream>

class StaffMember;

class StaffMemberWriter
{
public:
    StaffMemberWriter(QIODevice* device);
    bool write(const StaffMember &member);
    StaffMemberWriter& operator<<(const StaffMember&);
private:
    QTextStream m_Stream;
};

#endif // STAFFMEMBERWRITER_H
