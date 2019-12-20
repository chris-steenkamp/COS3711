#ifndef PROCESSSTUDENT_H
#define PROCESSSTUDENT_H

#include <QWidget>

class QLineEdit;
class QListWidget;
class QProcess;

class ProcessStudent : public QWidget
{
    Q_OBJECT

public:
    ProcessStudent(QWidget *parent = 0);
    ~ProcessStudent();
private slots:
    void handleAddModuleClicked();
    void handleDisplayStudentClicked();
    void handleAverageClicked();
    void handleGraduateClicked();
    void handleProcessOutput();
private:
    QListWidget *m_ModuleList;
    QProcess *m_Process;
    QLineEdit *m_StudentNumber;
};

#endif // PROCESSSTUDENT_H
