#ifndef MIDICOMMAND_H
#define MIDICOMMAND_H

#include "Command.h"

class MidiCommand : public Command
{
public:
    MidiCommand();
    virtual void execute(Synth &theSynth);
};

#endif // MIDICOMMAND_H
