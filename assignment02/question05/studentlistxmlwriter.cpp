#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QHash>
#include <QString>
#include <QTextStream>

#include "student.h"
#include "studentlist.h"
#include "studentlistxmldoc.h"
#include "studentlistxmlwriter.h"

typedef QHash<QString, int> ModuleContainer;

StudentListXMLWriter::StudentListXMLWriter()
{

}

void StudentListXMLWriter::write(const StudentList &list, QString filename) const
{
    StudentListXMLDoc doc;
    doc.setRootStudentList(list);

    QFile outputFile(filename);
    QTextStream s(&outputFile);
    outputFile.open(QFile::WriteOnly);
    doc.save(s, 0);
    outputFile.close();
}
