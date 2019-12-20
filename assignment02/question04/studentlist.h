#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include <QList>

class Student;
class QString;

class StudentList
{
public:
    //provide access to Single static instance
    static StudentList *getInstance();

    void addStudent(Student *student);

    int studentExists(QString studentNumber) const;
    QList<Student*> getStudents() const;
    Student *getStudent(int index) const;
    int count() const;
private:
    static StudentList *s_Instance;
    QList<Student*> *m_Students;

    //disable external construction
    StudentList();
    //disable copy constructor
    StudentList(const StudentList&);
    //disable external destruction
    ~StudentList();
    //disable assigment
    StudentList &operator=(const StudentList&);
};

#endif // STUDENTLIST_H
