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

    // these states can be checked thru checkState()
    enum{ mw_start, mw_config, mw_running};
    enum{ mw_src, mw_dest, mh_device};

    // check mh state
    int checkState() const;
    friend void mycallback(double deltatime, std::vector< unsigned char > *message, void *userData);

signals:

public slots:

private slots:

    // for the buttons
    void connectClient();
    void disconnectClient();
    void startMidi();
    void stopMidi();
    void flushMidi();

    // internal methods
    void displayComponents();
    void clearComponents();

    // for entities
    void selectSource();
    void selectDestination();
    void selectDevice();
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
    QPushButton* flushButton;
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

void mycallback(double deltatime, std::vector< unsigned char > *message, void *userData);


#endif // MIDIWINDOW_H
