#-------------------------------------------------
#
# Project created by QtCreator 2015-06-30T13:33:55
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -D__MACOSX_CORE__

mac: LIBS += -framework CoreMIDI
mac: LIBS += -framework CoreAudio
mac: LIBS += -framework CoreFoundation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleSynth
TEMPLATE = app


SOURCES += main.cpp\
    RtMidi.cpp\
    MidiWindow.cpp

HEADERS  += RtMidi.h \
    MidiHandler.h \
    MidiWindow.h
