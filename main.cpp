#include "MidiWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MidiWindow w;
    w.show();

    return a.exec();
}
