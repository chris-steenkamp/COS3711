#ifndef STUDENTXMLWRITER_H
#define STUDENTXMLWRITER_H

#include <QString>

class StudentList;

class StudentListXMLWriter
{
public:
    StudentListXMLWriter();

    void write(const StudentList &list, QString filename) const;
};

#endif // STUDENTXMLWRITER_H
