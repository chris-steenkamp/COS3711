#include <QApplication>
#include "albumlistviewer.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    AlbumListViewer form;

    form.show();

    return app.exec();
}
