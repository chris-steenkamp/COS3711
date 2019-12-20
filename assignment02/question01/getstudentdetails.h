#ifndef GETSTUDENTDETAILS_H
#define GETSTUDENTDETAILS_H

#include <QWidget>
class QLineEdit;
class QSpinBox;

class GetStudentDetails : public QWidget
{
    Q_OBJECT
public:
    GetStudentDetails(QWidget *parent = 0);
    ~GetStudentDetails();
private slots:
    void handleAddClicked();
private:
    QLineEdit *m_StudentNumber;
    QLineEdit *m_ModuleCode;
    QSpinBox *m_Mark;
};

#endif // GETSTUDENTDETAILS_H
