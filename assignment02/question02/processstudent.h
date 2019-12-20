#ifndef PROCESSSTUDENT_H
#define PROCESSSTUDENT_H

#include <QWidget>

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
    void handleProcessOutput();
private:
    QListWidget *m_ModuleList;
    QProcess *m_Process;
};

#endif // PROCESSSTUDENT_H
