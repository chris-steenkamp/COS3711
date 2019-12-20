#include "student.h"
#include "studentlist.h"

#include <QDebug>
#include <QHash>

StudentList* StudentList::s_Instance = 0;

StudentList *StudentList::getInstance()
{
    if (!s_Instance)
    {
        s_Instance = new StudentList();
    }

    return s_Instance;
}

StudentList::StudentList()
    : m_Students(new QList<Student*>())
{
    qDebug() << "Creating new StudentList instance" << endl;
}

StudentList::StudentList(const StudentList &)
    : m_Students(new QList<Student*>())
{
}

StudentList::~StudentList()
{
    qDebug() << "Cleaning up StudentList instance" << endl;
    qDeleteAll(*m_Students);
    m_Students->clear();
    delete m_Students;
    m_Students = 0;
}

StudentList &StudentList::operator=(const StudentList &)
{
    return *this;
}

void StudentList::addStudent(Student *student)
{
    int index = studentExists(student->getNumber());
    if (index < 0)
    {
        m_Students->append(student);
    }
    else
    {
        Student *existingStudent = getStudent(index);

        //add all modules from new student to existing student
        //if a modules already exists, it will be updated with the new mark, if provided
        QHash<QString, int>::ConstIterator i;
        for (i = student->getModules().cbegin(); i != student->getModules().cend(); ++i)
        {
            existingStudent->addModule(i.key(), i.value());
        }
    }
}

int StudentList::studentExists(QString studentNumber) const
{
    QList<Student*>::ConstIterator i;
    for (i = m_Students->cbegin(); i != m_Students->cend(); ++i)
    {
        if ((*i)->getNumber() == studentNumber)
        {
            return m_Students->indexOf(*i);
        }
    }

    return -1;
}

QList<Student*> StudentList::getStudents() const
{
    return *m_Students;
}

Student *StudentList::getStudent(int index) const
{
    if (index >= 0 && index < count())
    {
        return m_Students->value(index);
    }

    return 0;
}

int StudentList::count() const
{
    return m_Students->count();
}
