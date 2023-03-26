
#include <Loader.h>
#include <DigitalOutput.h>

DigitalOutput::DigitalOutput(DigitalOutputParams * params){
    Params = params;
    pinMode(Params->Pin, OUTPUT);
};

void DigitalOutput::Set(){
    digitalWrite(Params->Pin, Params->Reverse ? LOW : HIGH);
};

void DigitalOutput::Reset(){
    digitalWrite(Params->Pin, Params->Reverse ? HIGH : LOW);
};