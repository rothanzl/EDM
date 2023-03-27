#include <Loader.h>
#include <DigitalOutput.h>

DigitalOutput::DigitalOutput(char pin, bool reverse){
    _pin = pin;
    _reverse = reverse;
    pinMode(_pin, OUTPUT);
};

void DigitalOutput::Set(){
    digitalWrite(_pin, _reverse ? LOW : HIGH);
};

void DigitalOutput::Reset(){
    digitalWrite(_pin, _reverse ? HIGH : LOW);
};
