#ifndef MIDIWINDOW_H
#define MIDIWINDOW_H

#include <QWidget>
#include <QtWidgets>
#define __MACOSX_CORE__
#include "RtMidi.h"

class MidiWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MidiWindow(QWidget *parent = 0);

//    friend void debugCallback(double deltatime, std::vector< unsigned char > *message, void *userData);

signals:

public slots:

private slots:

    // for the buttons
    void connectClient();
    void disconnectClient();
    void startMidi();
    void stopMidi();

    // for entities
    void selectSource();
    void selectDestination();
    void getEntityList();

private:
    QVBoxLayout* mwLayout;
    RtMidiIn* rtm_in = 0;
    RtMidiOut* rtm_out = 0;

    // Midi Status group
    QGroupBox* statusLabel;
    QLabel* status;
    QPushButton* connectButton;
    QPushButton* startButton;
    // RtMidi has no flush. Will we have to implement ourselves?
    // QPushButton* flushButton;
    QHBoxLayout* midiStatusLayout;

    // Midi Entities group
    QGroupBox* midiEntitiesLabel;
    QLabel* sourcesLabel;
    QLabel* destLabel;
    QLabel* devicesLabel;
    QComboBox* sourceDropdown;
    QComboBox* destDropdown;
    QComboBox* deviceDropdown;
    QGridLayout* midiEntityLayout;

    // Midi Event log group
    QGroupBox* midiEventLabel;
    QScrollArea* eventScroll;
    QTableView* eventTable;
    QLayout* midiEventLayout;

    // App console group
    QGroupBox* appConsoleLabel;
    QScrollArea* logScroll;
    QTextEdit* logText;
    QLayout* logLayout;

    // local data
    QStringList sourceNames;
    QStringList destNames;
    QStringList deviceNames;

    // creation functions

    void createStatusGroup();
    void createEntitiesGroup();
    void createEventsGroup();
    void createAppGroup();

};

void debugCallback(double deltatime, std::vector< unsigned char > *message, void *userData);


#endif // MIDIWINDOW_H
