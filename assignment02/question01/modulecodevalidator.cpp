#include "modulecodevalidator.h"

#include <QRegExp>

ModuleCodeValidator::ModuleCodeValidator(QObject *parent)
    : QRegExpValidator(QRegExp("^[A-Z]{3}[1-3]\\d{2}[a-zA-Z0-9]$"), parent)
{

}
