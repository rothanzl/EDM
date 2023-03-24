
#include <DigitalOutput.h>

#ifdef UNIT_TEST
    #include <ArduinoFake.h>
#else
    #include <Arduino.h>
#endif

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