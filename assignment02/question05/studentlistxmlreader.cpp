#include <QDomDocument>
#include <QFile>
#include <QHash>
#include <QString>
#include <QTextStream>

#include "student.h"
#include "studentlist.h"
#include "studentlistxmldoc.h"
#include "studentlistxmlreader.h"

typedef QHash<QString, int> ModuleContainer;

StudentListXMLReader::StudentListXMLReader()
{

}

QDomElement visit(QDomElement current)
{
    QString name = current.tagName();
    QString value = current.text();
    if (name == "student")
    {
        Student s(value);
    }

    return current;
}

QDomNode walkTree(QDomNode current)
{
    QDomNodeList children = current.childNodes();

    for (int i = children.count() - 1; i >=0; --i)
    {
        walkTree(children.item(i));
    }

    if (current.nodeType() == QDomNode::ElementNode)
    {
        QDomElement e = current.toElement();
        return visit(e);
    }

    return current;
}

StudentList& StudentListXMLReader::read(StudentList &studentList, QString filename)
{
    QFile inputFile(filename);
    inputFile.open(QFile::ReadOnly);

    StudentListXMLDoc d;
    d.setContent(&inputFile);

    inputFile.close();

    walkTree(d.documentElement());

    return studentList;
}
