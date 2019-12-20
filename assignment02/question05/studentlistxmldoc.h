#ifndef STUDENTLISTXMLDOC_H
#define STUDENTLISTXMLDOC_H

#include <QDomDocument>

class StudentList;

class StudentListXMLDoc : public QDomDocument
{
public:
    StudentListXMLDoc();
    QDomElement setRootStudentList(const StudentList& list);
private:
    QDomElement createStudentElement(QString number);
    QDomElement createStudentNumberText(QString number, QDomElement parent);
    QDomElement createModuleElement(QString moduleName, int mark, QDomElement parent);
};

#endif // STUDENTLISTXMLDOC_H
