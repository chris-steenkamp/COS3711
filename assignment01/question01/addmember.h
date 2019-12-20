#ifndef ADDMEMBER_H
#define ADDMEMBER_H

#include <QDate>
#include <QString>
#include <QWidget>

class QLineEdit;
class QDateEdit;
class QComboBox;

class AddMember : public QWidget
{
    Q_OBJECT
public:
    explicit AddMember(QWidget *parent = 0);

signals:
    void memberCreated(QString, QDate, QString);

public slots:
    void handleAddClicked();
    void handleCloseClicked();
private:
    QLineEdit *m_NameLineEdit;
    QDateEdit *m_BirthdateDateEdit;
    QComboBox *m_AppointmentTypeComboBox;
};

#endif // ADDMEMBER_H
