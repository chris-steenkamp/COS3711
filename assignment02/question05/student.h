#ifndef STUDENT_H
#define STUDENT_H

#include <QHash>
#include <QString>

typedef QHash<QString, int> ModuleContainer;

class Student
{
public:
    Student();
    Student(QString studentNumber);

    void setNumber(QString studentNumber);
    void addModule(QString moduleCode, int mark);

    QString getNumber() const;
    ModuleContainer getModules() const;

    double average() const;
    bool graduate() const;
private:
    void setModules(ModuleContainer modules);
    QString m_StudentNumber;
    ModuleContainer m_Modules;
};

#endif // STUDENT_H
