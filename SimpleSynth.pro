#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T13:33:55
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

linux: QMAKE_CXXFLAGS += -D__LINUX_ALSA__
linux: LIBS += -lasound -lpthread

mac: QMAKE_CXXFLAGS += -D__MACOSX_CORE__
mac: LIBS += -framework CoreMIDI
mac: LIBS += -framework CoreAudio
mac: LIBS += -framework CoreFoundation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSynth
TEMPLATE = app


SOURCES += main.cpp\
    RtMidi.cpp \
    RtAudio.cpp \
    MidiWindow.cpp \
    AudioSetupWindow.cpp \
    AppManager.cpp \
    gm-lib/Command.cpp \
    gm-lib/MidiCommand.cpp \
    gm-lib/Synth.cpp

HEADERS  += RtMidi.h \
    RtAudio.h \
    MidiWindow.h \
    AudioSetupWindow.h \
    RtAudio.h \
    AppManager.h \
    gm-lib/Command.h \
    gm-lib/MidiCommand.h \
    gm-lib/Synth.h
