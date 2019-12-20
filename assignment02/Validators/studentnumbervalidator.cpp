#include "studentnumbervalidator.h"

#include <QRegExp>

StudentNumberValidator::StudentNumberValidator(QObject *parent) :
    QRegExpValidator(QRegExp("^\\d{4}$"), parent)
{

}
