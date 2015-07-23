#include "MidiWindow.h"
#include "AudioSetupWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MidiWindow w;
    AudioSetupWindow w;

    w.show();

    return a.exec();
}
