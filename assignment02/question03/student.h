#ifndef STUDENT_H
#define STUDENT_H

#include <QHash>
#include <QString>

class Student
{
public:
    Student();
    Student(QString studentNumber);

    void setNumber(QString studentNumber);
    void addModule(QString moduleCode, int mark);

    QString getNumber() const;
    QHash<QString, int> getModules() const;

    double average() const;
    bool graduate() const;
private:
    QString m_StudentNumber;
    QHash<QString, int> m_Modules;
};

#endif // STUDENT_H
