#ifndef STUDENTNUMBERVALIDATOR_H
#define STUDENTNUMBERVALIDATOR_H

#include <QRegExpValidator>

class StudentNumberValidator : public QRegExpValidator
{
    Q_OBJECT
public:
    explicit StudentNumberValidator(QObject *parent = 0);
};

#endif // STUDENTNUMBERVALIDATOR_H
