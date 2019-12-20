#include <QApplication>
#include <QObject>
#include "addmember.h"
#include "staffmemberfilestore.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    StaffMemberFileStore store("staff.lst");

    AddMember mainWidget;
    QObject::connect(&mainWidget, &AddMember::memberCreated, &store, &StaffMemberFileStore::addMember);

    mainWidget.show();

    return app.exec();
}
