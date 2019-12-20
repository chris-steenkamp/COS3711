#include <QFormLayout>
#include <QListWidget>
#include <QMessageBox>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "processstudent.h"

ProcessStudent::ProcessStudent(QWidget *parent)
    : QWidget(parent),
      m_ModuleList(new QListWidget(this)),
      m_Process(new QProcess(this))
{
    setWindowTitle("Process Student");

    QFormLayout *form = new QFormLayout(this);

    QPushButton *addModule = new QPushButton(tr("&Add Module"), this);
    connect(addModule, SIGNAL(clicked()), this, SLOT(handleAddModuleClicked()));
    form->addWidget(addModule);

    form->addWidget(m_ModuleList);

    connect(m_Process, SIGNAL(readyReadStandardOutput()), this, SLOT(handleProcessOutput()));

    this->setLayout(form);
}

ProcessStudent::~ProcessStudent()
{
    m_Process->close();
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

void ProcessStudent::handleProcessOutput()
{
    QString input = m_Process->readAllStandardOutput();
    QStringList lines = input.split('\t');
    for (int i = 0; i < lines.length(); ++i)
    {
        m_ModuleList->addItem(lines[i]);
    }
}
