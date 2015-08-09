#include "MidiWindow.h"
#include "AudioSetupWindow.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // identification
    QCoreApplication::setOrganizationName("GarryKling");
    QCoreApplication::setOrganizationDomain("garrykling.com");
    QCoreApplication::setApplicationName("SimpleSynth");

    MidiWindow w;
    // AudioSetupWindow w;

    w.show();

    return a.exec();
}
