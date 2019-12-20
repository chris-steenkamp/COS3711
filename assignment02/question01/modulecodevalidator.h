#ifndef MODULECODEVALIDATOR_H
#define MODULECODEVALIDATOR_H

#include <QRegExpValidator>

class ModuleCodeValidator : public QRegExpValidator
{
    Q_OBJECT
public:
    explicit ModuleCodeValidator(QObject *parent = 0);
};

#endif // MODULECODEVALIDATOR_H
