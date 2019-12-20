#include <QFormLayout>
#include <QHash>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "processstudent.h"
#include "student.h"
#include "studentlist.h"
#include "studentlistxmlwriter.h"

ProcessStudent::ProcessStudent(QWidget *parent)
    : QWidget(parent),
      m_ModuleList(new QListWidget(this)),
      m_Process(new QProcess(this)),
      m_StudentNumber(new QLineEdit(this))
{
    setWindowTitle("Process Student");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *input = new QFormLayout();
    QHBoxLayout *buttons = new QHBoxLayout();

    QPushButton *displayStudent = new QPushButton(tr("&Display"), this);
    QPushButton *calculateStudentAverage = new QPushButton(tr("&Average"), this);
    QPushButton *graduateStudent = new QPushButton(tr("&Graduate?"), this);
    QPushButton *addModule = new QPushButton(tr("Add &Module"), this);

    input->addRow(tr("&Student Number"), m_StudentNumber);

    buttons->addWidget(displayStudent);
    buttons->addWidget(calculateStudentAverage);
    buttons->addWidget(graduateStudent);
    buttons->addWidget(addModule);

    mainLayout->addItem(input);
    mainLayout->addItem(buttons);
    mainLayout->addWidget(m_ModuleList);

    connect(m_Process, SIGNAL(readyReadStandardOutput()), this, SLOT(handleProcessOutput()));
    connect(displayStudent, SIGNAL(clicked()), this, SLOT(handleDisplayStudentClicked()));
    connect(calculateStudentAverage, SIGNAL(clicked()), this, SLOT(handleAverageClicked()));
    connect(graduateStudent, SIGNAL(clicked()), this, SLOT(handleGraduateClicked()));
    connect(addModule, SIGNAL(clicked()), this, SLOT(handleAddModuleClicked()));

    this->setLayout(mainLayout);
    QList<Student*> l = QList<Student*>(StudentList::getInstance()->getStudents());
}

ProcessStudent::~ProcessStudent()
{
    m_Process->close();
    StudentListXMLWriter writer;
    writer.write(*StudentList::getInstance(), "studentlist.xml");
}

void ProcessStudent::handleAddModuleClicked()
{
    if (m_Process->state() != QProcess::Running)
    {
        m_Process->start("question01.exe");
        if (m_Process->state() != QProcess::Running)
        {
            QMessageBox::critical(this, "Unable to Start Process",  m_Process->errorString().append(".\nPlease ensure question01.exe is in the application build path."));
        }
    }
}

void displayStudentDetails(const Student &student, QListWidget &list)
{
    list.clear();
    list.addItem(QString("Student %0").arg(student.getNumber()));
    for (QHash<QString, int>::ConstIterator i = student.getModules().cbegin(); i != student.getModules().cend(); ++i)
    {
        list.addItem(QString("Module: %0, Mark: %1").arg(i.key()).arg(QString::number(i.value())));
    }
}

Student *findStudent(QString studentNumber)
{
    StudentList *list = StudentList::getInstance();
    int index = list->studentExists(studentNumber);
    Student *s = list->getStudent(index);

    return s;
}

void ProcessStudent::handleDisplayStudentClicked()
{
    Student *s = findStudent(m_StudentNumber->text());

    if (s)
    {
        displayStudentDetails(*s, *m_ModuleList);
    }
    else
    {
        m_ModuleList->clear();
        m_ModuleList->addItem(QString("No student with number %0 could be found!").arg(m_StudentNumber->text()));
    }
}

void ProcessStudent::handleAverageClicked()
{
    Student *s = findStudent(m_StudentNumber->text());
    if (s)
    {
        displayStudentDetails(*s, *m_ModuleList);
        m_ModuleList->addItem(QString("Average %0").arg(QString::number(s->average())));
    }
    else
    {
        m_ModuleList->clear();
        m_ModuleList->addItem(QString("No student with number %0 could be found!").arg(m_StudentNumber->text()));
    }
}

void ProcessStudent::handleGraduateClicked()
{
    Student *s = findStudent(m_StudentNumber->text());
    m_ModuleList->clear();
    if (s)
    {
        m_ModuleList->addItem(QString("Student %0 %1 graduated!").arg(s->getNumber()).arg(s->graduate()?"has" : "has not"));
    }
    else
    {
        m_ModuleList->addItem(QString("No student with number %0 could be found!").arg(m_StudentNumber->text()));
    }
}

Student* createStudent(QString input)
{
    QStringList lines = input.split('\t');

    Student *s = new Student(lines[0]);
    s->addModule(lines[1], lines[2].toInt());

    StudentList::getInstance()->addStudent(s);

    return s;
}

void ProcessStudent::handleProcessOutput()
{
    QString input = m_Process->readAllStandardOutput();
    Student *s = createStudent(input);
    displayStudentDetails(*s, *m_ModuleList);
}
