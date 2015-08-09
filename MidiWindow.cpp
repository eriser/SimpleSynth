#include "MidiWindow.h"

MidiWindow::MidiWindow(QWidget *parent) : QWidget(parent)
{

        // Create the layout container
        mwLayout = new QVBoxLayout;

        createStatusGroup();
        createEntitiesGroup();
        createEventsGroup();
        // App console group - this may become a seperate window
        createAppGroup();
        // set up the window
        setLayout(mwLayout);
        setWindowTitle(tr("Midi Window"));
}

void MidiWindow::createStatusGroup()
{
    // Midi status group
    statusLabel = new QGroupBox(tr("MIDI Status"));
    status = new QLabel(tr("Idle"));
    connectButton = new QPushButton("&Connect");
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectClient()));
    startButton = new QPushButton("S&tart");
    startButton->setEnabled(false);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startMidi()));

    // layout
    midiStatusLayout = new QHBoxLayout;
    midiStatusLayout->addWidget(status);
    midiStatusLayout->addWidget(connectButton);
    midiStatusLayout->addWidget(startButton);
    statusLabel->setLayout(midiStatusLayout);
    mwLayout->addWidget(statusLabel);
}

void MidiWindow::createEntitiesGroup()
{
    midiEntitiesLabel = new QGroupBox(tr("MIDI Connections"));
    sourcesLabel = new QLabel(tr("Sources: "));
    destLabel = new QLabel(tr("Destinations: "));
    sourceDropdown = new QComboBox();
    destDropdown = new QComboBox();

    // Layout
    midiEntityLayout = new QGridLayout();
    midiEntitiesLabel->setLayout(midiEntityLayout);
    mwLayout->addWidget(midiEntitiesLabel);
    midiEntityLayout->addWidget(sourcesLabel, 2, 0);
    midiEntityLayout->addWidget(destLabel, 4, 0);
    midiEntityLayout->addWidget(sourceDropdown, 2, 2);
    midiEntityLayout->addWidget(destDropdown, 4, 2);
}

void MidiWindow::createEventsGroup()
{
    midiEventLabel = new QGroupBox(tr("MIDI Event Log"));

    midiGridModel = new QStandardItemModel(4,1,this);
    midiGridModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Byte 0")));
    midiGridModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Byte 1")));
    midiGridModel->setHorizontalHeaderLabels(2, new QStandardItem(QString("Byte 2")));
    midiGridModel->setHorizontalHeaderLabels(3, new QStandardItem(QString("Timestamp")));

    eventTable = new QTableView();
    eventTable->setGridStyle(Qt::PenStyle::SolidLine);
    eventTable->setShowGrid(true);

    eventScroll = new QScrollArea();
    eventScroll->setWidget(eventTable);

    midiEventLayout = new QVBoxLayout();
    midiEventLayout->addWidget(eventScroll);
    midiEventLabel->setLayout(midiEventLayout);
    mwLayout->addWidget(midiEventLabel);
}

void MidiWindow::createAppGroup()
{
    appConsoleLabel = new QGroupBox(tr("App Console"));
    logText = new QTextEdit();
    logScroll = new QScrollArea();
    logScroll->setWidget(logText);

    logLayout = new QVBoxLayout();
    logLayout->addWidget(logScroll);
    appConsoleLabel->setLayout(logLayout);
    mwLayout->addWidget(appConsoleLabel);
}

// for the buttons
void MidiWindow::connectClient()
{
    // Disconnect if we are already running
    if(rtm_in && rtm_in->isPortOpen())
    {
        rtm_in->cancelCallback();
        rtm_in->closePort();
    }

    if(rtm_out && rtm_out->isPortOpen())
    {
        rtm_out->closePort();
    }

    // connect In
    try {
      rtm_in = new RtMidiIn();
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
    }

    // connect Out as well
    try {
      rtm_out = new RtMidiOut();
    }
    catch ( RtMidiError &error ) {
      error.printMessage();
    }

    // get all the names for the available ports
    getEntityList();

    // enable start button
    startButton->setEnabled(true);

    // change connect to disconnect
    connectButton->setText("Disconnect");
    disconnect(connectButton, 0, 0, 0);
    connect(connectButton, SIGNAL(clicked()), this, SLOT(disconnectClient()));

}

void MidiWindow::disconnectClient()
{
    // check rtm_in and rtm_out - gaurd against nullptr
    // delete them if they are anything
    if(rtm_in && rtm_in->isPortOpen())
    {
        rtm_in->cancelCallback();
        rtm_in->closePort();
    }

    if(rtm_out && rtm_out->isPortOpen())
    {
        rtm_out->closePort();
    }

    // switch disconnect to connect
    connectButton->setText("Connect");
    disconnect(connectButton, 0,0,0);
    connect(connectButton, SIGNAL(clicked()), this, SLOT(connectClient()));

    // fix start button
    startButton->setEnabled(false);

    // delete dropdown items
    sourceDropdown->clear();
    destDropdown->clear();

}

void MidiWindow::startMidi()
{
    static int i=0;
    std::cout<<i++<<std::endl;

    // open a port
    if(rtm_in && !rtm_in->isPortOpen()) {rtm_in->openPort(0, std::string("Simple Synth In"));}
    if(rtm_out && !rtm_out->isPortOpen()) {rtm_out->openPort(0, std::string("Simple Synth Out"));}

    // register callback
    rtm_in->setCallback(&debugCallback);

    // set start to stop, connect the signal
    startButton->setText("Stop");
    disconnect(startButton, 0, 0, 0);
    connect(startButton, SIGNAL(clicked()), this, SLOT(stopMidi()));

    // disable the disconnect button - no disconnecting while running
    connectButton->setEnabled(false);

}

void MidiWindow::getEntityList()
{
    // get port counts, clear data
    unsigned int numInPorts = rtm_in->getPortCount();
    unsigned int numOutPorts = rtm_out->getPortCount();
    std::string portName;

    // clear the name lists
    sourceNames.clear();
    destNames.clear();

    // retrieve all names - input
    if(numInPorts>0)
    {
      for ( unsigned int i=0; i<numInPorts; i++ )
      {
          try {
            portName = rtm_in->getPortName(i);
            sourceNames<<QString::fromStdString(portName);
          }
          catch ( RtMidiError &error ) {
            error.printMessage();
            std::cout<<"Error getting input ports."<<std::endl;
          }
          std::cout << "Input Port #" << i+1 << ": " << portName << '\n';
       }

    }else {
        std::cout<<"No input ports available."<<std::endl;
    }

    if(numOutPorts>0)
    {
         for ( unsigned int i=0; i<numOutPorts; i++ )
         {
             try {
               portName = rtm_out->getPortName(i);
               destNames<<QString::fromStdString(portName);
             }
             catch ( RtMidiError &error ) {
               error.printMessage();
               std::cout<<"Error getting output ports."<<std::endl;
             }
             std::cout << "Output Port #" << i+1 << ": " << portName << '\n';
          }

    }else {
         std::cout<<"No output ports available."<<std::endl;
    }

     // populate dropdowns
     sourceDropdown->addItems(sourceNames);
     destDropdown->addItems(destNames);

     // hookup user selection signals
}

void MidiWindow::stopMidi()
{
    // unplug the callback
    rtm_in->cancelCallback();

    // close the ports
    rtm_in->closePort();
    rtm_out->closePort();

    // set stop to start
    startButton->setText("Start");
    disconnect(startButton, 0, 0, 0);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startMidi()));

    // enable the disconnect button
    connectButton->setEnabled(true);
}

void MidiWindow::selectSource()
{

}

void MidiWindow::selectDestination()
{

}

void debugCallback(double deltatime, std::vector<unsigned char> *message, void *userData)
{
  unsigned int nBytes = message->size();

  for ( unsigned int i=0; i<nBytes; i++ )
  {
    std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
  }
  if ( nBytes > 0 )
  {
    std::cout << "stamp = " << deltatime << std::endl;
  }
}
