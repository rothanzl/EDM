#ifndef _ANALOGINPUT_H
#define _ANALOGINPUT_H

#include <Loader.h>

class AnalogInput{
    private:
        byte _pin;
        static float _leastDiff;
    public:
        AnalogInput(byte pin);
        float readVoltage();
};

AnalogInput::AnalogInput(byte pin){
    _pin = pin;
}

float AnalogInput::readVoltage(){
    return analogRead(_pin) * _leastDiff;
}

float AnalogInput::_leastDiff = 5.0 / 1023.0;


#endif