#include "AudioSetupWindow.h"

AudioSetupWindow::AudioSetupWindow(QWidget *parent) : QWidget(parent)
{
    aswLayout = new QVBoxLayout;

    // config dropdowns
    audioConfigGroupLabel = new QGroupBox("Audio Setup");
    deviceLabel = new QLabel(tr("Audio Device: "));
    deviceDropdown = new QComboBox();
    chanLabel = new QLabel(tr("Channel Configuration: "));
    chanDropdown = new QComboBox();
    bufferLabel = new QLabel(tr("Buffer Size: "));
    bufferDropdown = new QComboBox();
    srLabel = QLabel(tr("Sample Rate: "));
    srDropdown = new QComboBox();
    bitsLabel = new QLabel(tr("Bit Depth: "));
    bitsDropdown = new QComboBox();

    configLayout = new QGridLayout();
    audioConfigGroupLabel->setLayout(configLayout);
    configLayout->addWidget(deviceLabel, 2, 0);
    configLayout->addWidget(deviceDropdown, 2, 2);
    configLayout->addWidget(chanLabel, 4, 0);
    configLayout->addWidget(chanDropdown, 4, 2);
    configLayout->addWidget(bufferLabel, 6, 0);
    configLayout->addWidget(bufferDropdown, 6, 2);
    configLayout->addWidget(srLabel, 8, 0);
    configLayout->addWidget(srDropdown, 8, 2);
    configLayout->addWidget(bitsLabel, 10, 0);
    configLayout->addWidget(bitsDropdown, 10, 2);

    aswLayout->addWidget(configLayout);

    // button group
    resetAudioSetupButton = new QPushButton("R&eset");
    connect(resetAudioSetupButton, SIGNAL(clicked()), this, SLOT(resetAudioSetup()));
    cancelAudioSetupButton = new QPushButton("C&ancel");
    connect(cancelAudioSetupButton, SIGNAL(clicked()), this, SLOT(cancelAudioSetup()));
    applyAudioSetupButton = new QPushButton("A&pply");
    connect(applyAudioSetupButton, SIGNAL(clicked()), this, SLOT(applyAudioSetup()));

    aswButtonsLayout = new QHBoxLayout;
    aswButtonsLayout->addWidget(resetAudioSetupButton);
    aswButtonsLayout->addWidget(cancelAudioSetupButton);
    aswButtonsLayout->addWidget(applyAudioSetupButton);

    aswLayout->addWidget(aswButtonsLayout);

}
