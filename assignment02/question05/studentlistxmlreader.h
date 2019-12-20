#ifndef STUDENTXMLREADER_H
#define STUDENTXMLREADER_H

#include <QString>

class StudentList;

class StudentListXMLReader
{
public:
    StudentListXMLReader();

    StudentList& read(StudentList &studentList, QString filename);
};

#endif // STUDENTXMLREADER_H
