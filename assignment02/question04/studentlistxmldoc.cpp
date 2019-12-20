#include "student.h"
#include "studentlist.h"
#include "studentlistxmldoc.h"

typedef QHash<QString, int> ModuleContainer;

StudentListXMLDoc::StudentListXMLDoc()
    : QDomDocument()
{
}

QDomElement StudentListXMLDoc::setRootStudentList(const StudentList &list)
{
    QDomElement root = createElement("StudentList");
    appendChild(root);

//    QList<Student*>::ConstIterator i;

    QListIterator<Student*> i(list.getStudents());

//    for (i = list.getStudents().cbegin(); i != list.getStudents().cend(); ++i)
    while (i.hasNext())
    {
        Student *s = i.next();
        QDomElement studentEl = createStudentElement(s->getNumber());
        QDomElement modules = studentEl.firstChildElement("modules");

        ModuleContainer::ConstIterator m;

        for (m = s->getModules().cbegin(); m != s->getModules().cend(); ++m)
        {
            createModuleElement(m.key(), m.value(), modules);
        }
    }

    return root;
}
QDomElement StudentListXMLDoc::createStudentElement(QString number)
{
    QDomElement element(createElement("student"));
    createStudentNumberText(number, element);
    element.appendChild(createElement("modules"));

    documentElement().appendChild(element);

    return element;
}

QDomElement StudentListXMLDoc::createStudentNumberText(QString number, QDomElement parent)
{
    QDomElement element(createElement("number"));
    element.appendChild(createTextNode(number));
    parent.appendChild(element);

    return element;
}

QDomElement StudentListXMLDoc::createModuleElement(QString moduleName, int moduleMark, QDomElement parent)
{
    QDomElement element(createElement("module"));
    QDomElement code(createElement("code"));
    code.appendChild(createTextNode(moduleName));
    element.appendChild(code);

    QDomElement mark(createElement("mark"));
    mark.appendChild(createTextNode(QString::number(moduleMark)));
    element.appendChild(mark);

    parent.appendChild(element);

    return element;
}
