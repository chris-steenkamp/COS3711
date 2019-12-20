#include <QMetaProperty>
#include <QStringList>
#include <QVariant>
#include "staffmemberwriter.h"
#include "staffmember.h"

StaffMemberWriter::StaffMemberWriter(QIODevice *device) : m_Stream(device)
{
}

bool StaffMemberWriter::write(const StaffMember &member) {
    QStringList list;
    for (int i = 0; i < StaffMember::staticMetaObject.propertyCount(); ++i) {
        QMetaProperty prop = StaffMember::staticMetaObject.property(i);
        //We do not want to save read-only properties because there is no
        //way to restore them from external data.
        if (prop.isWritable()) {
            QVariant var = prop.read(&member);
            if (var.isValid()) {
                //Store each property as a key-value pair to make it easier to
                //dynamically assign the values again when reading from file
                list << QString("%0=%1").arg(prop.name()).arg(var.toString());
            }
        }
    }

    m_Stream << list.join('\t') << '\n';
    return !(m_Stream.status() == QTextStream::WriteFailed);
}

StaffMemberWriter& StaffMemberWriter::operator<<(const StaffMember &member) {
    write(member);
    return *this;
}
