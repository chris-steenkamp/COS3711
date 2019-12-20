#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include "getstudentdetails.h"
#include "modulecodevalidator.h"
#include "studentnumbervalidator.h"

static QTextStream cout(stdout);

GetStudentDetails::GetStudentDetails(QWidget *parent)
    : QWidget(parent),
      m_StudentNumber(new QLineEdit(this)),
      m_ModuleCode(new QLineEdit(this)),
      m_Mark(new QSpinBox(this))
{
    m_StudentNumber->setInputMask("9999");
    m_ModuleCode->setInputMask(">A>A>A999!N");
    m_Mark->setRange(0, 100);

    setWindowTitle("Get Student");

    QFormLayout *form = new QFormLayout(this);
    form->addRow(tr("Student Number"), m_StudentNumber);
    form->addRow(tr("Module Code"), m_ModuleCode);
    form->addRow(tr("Mark"), m_Mark);

    QPushButton *btnAdd = new QPushButton(tr("&Add"), this);
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(handleAddClicked()));
    form->addWidget(btnAdd);

    this->setLayout(form);
}

GetStudentDetails::~GetStudentDetails()
{

}

bool isValidStudentNumber(QString input)
{
   int pos(0);

   return StudentNumberValidator().validate(input, pos) == QValidator::Acceptable;
}

bool isValidModuleCode(QString input)
{
    int pos(0);
    return ModuleCodeValidator().validate(input, pos)== QValidator::Acceptable;
}

void GetStudentDetails::handleAddClicked()
{
    if (!isValidStudentNumber(m_StudentNumber->text()))
    {
        m_StudentNumber->setFocus();
    }
    else if (!isValidModuleCode(m_ModuleCode->text()))
    {
        m_ModuleCode->setFocus();
    }
    else
    {
        QStringList list;
        list << m_StudentNumber->text();
        list << m_ModuleCode->text();
        list << QString::number(m_Mark->value());
        cout << list.join('\t') << endl << flush;

        m_StudentNumber->clear();
        m_ModuleCode->clear();
        m_Mark->setValue(0);
        m_StudentNumber->setFocus();

        return;
    }

    QMessageBox::warning(this, "Invalid Input", "The current information is not valid. Please enter valid information and try again.");
}

