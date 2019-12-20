#ifndef STAFFMEMBERREADER_H
#define STAFFMEMBERREADER_H

#include <QIODevice>
#include <QTextStream>

class StaffMember;

class StaffMemberReader
{
public:
    StaffMemberReader(QIODevice* device);
    bool read(StaffMember &member);
    StaffMemberReader& operator>>(StaffMember&);
private:
    QTextStream m_Stream;
};

#endif // STAFFMEMBERREADER_H
