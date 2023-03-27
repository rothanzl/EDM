#ifndef _ANALOGOUTPUT_H
#define _ANALOGOUTPUT_H

#include <Loader.h>


class AnalogOutput
{
private:
    char _pin = 0;
    bool _reverse = false;
public:
    AnalogOutput(char pin, bool reverse = false);
    ~AnalogOutput();
    void set(byte value);
};

AnalogOutput::AnalogOutput(char pin, bool reverse)
{
    _pin = pin;
    _reverse = reverse;

    pinMode(_pin, OUTPUT);
}

AnalogOutput::~AnalogOutput()
{
}

void AnalogOutput::set(byte value){
    analogWrite(_pin, value);
}

#endif