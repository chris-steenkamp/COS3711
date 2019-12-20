#include "student.h"

Student::Student()
{

}

Student::Student(QString studentNumber)
    : m_StudentNumber(studentNumber)
{
}

void Student::setNumber(QString studentNumber)
{
    m_StudentNumber = studentNumber;
}

void Student::addModule(QString moduleCode, int mark)
{
    m_Modules[moduleCode] = mark;
}

QString Student::getNumber() const
{
    return m_StudentNumber;
}

QHash<QString, int> Student::getModules() const
{
    return m_Modules;
}

double Student::average() const
{
    int total(0);
    QHash<QString, int>::ConstIterator i;
    for (i = m_Modules.cbegin(); i != m_Modules.cend(); ++i)
    {
        total += i.value();
    }

    return total / m_Modules.count();
}

int getYearCode(QString moduleCode)
{
    return QString(moduleCode[3]).toInt();
}

bool Student::graduate() const
{
    int modulesPassed[3] = {0};
    int totalPassed(0);

    QHash<QString, int>::ConstIterator i;
    for (i = m_Modules.cbegin(); i != m_Modules.cend(); ++i)
    {
        if (i.value() >= 50)
        {
            ++totalPassed;
            ++modulesPassed[getYearCode(i.key()) - 1];
        }
    }

    if (totalPassed >= 5 && modulesPassed[0] <= 2 && modulesPassed[2] >= 1)
    {
        return true;
    }

    return false;
}

void Student::setModules(QHash<QString, int> modules)
{
    m_Modules = modules;
}
