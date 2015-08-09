#ifndef AUDIOSETUPWINDOW_H
#define AUDIOSETUPWINDOW_H

#include "RtAudio.h"
#include <QWidget>
#include <QtWidgets>

class AudioSetupWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AudioSetupWindow(QWidget *parent = 0);

signals:

public slots:

private slots:

    // for buttons
    void resetAudioSetup();
    void cancelAudioSetup();
    void applyAudioSetup();

    // parameter changes
    void changeDevice(int devNum);
    void changeNumChans(int numChan);
    void changeBufSize(int bufSize);
    void changeSampRate(int sampRate);
    void changeBitDepth(int bitDepth);

    // for init
    void audioInit();

private:

    QVBoxLayout* aswLayout;
    RtAudio* rt_audio;

    // This window is mostly dropdowns
    QGroupBox* audioConfigGroupLabel;
    QLabel* deviceLabel;
    QComboBox* deviceDropdown;
    QLabel* chanLabel;
    QComboBox* chanDropdown;
    QLabel* bufferLabel;
    QComboBox* bufferDropdown;
    QLabel* srLabel;
    QComboBox* srDropdown;
    QLabel* bitsLabel;
    QComboBox* bitsDropdown;
    QGridLayout* configLayout;

    // modal style buttons
    QHBoxLayout* aswButtonsLayout;
    QPushButton* resetAudioSetupButton;
    QPushButton* cancelAudioSetupButton;
    QPushButton* applyAudioSetupButton;
};

#endif // AUDIOSETUPWINDOW_H
