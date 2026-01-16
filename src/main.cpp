#include <QCoreApplication>
#include <QTimer>
#include "managelib.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ManageLib lib;

    lib.init();
    lib.run();

    QTimer::singleShot(1000, &a, QCoreApplication::quit);
    return a.exec();
}
