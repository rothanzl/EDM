#ifndef _LINEARACTUATOR_H
#define _LINEARACTUATOR_H

#include <DigitalOutput.h>

struct LinearActuatorConstructParameter{
    LinearActuatorConstructParameter(DigitalOutput* digitalOutput){
        DigitalOutput = digitalOutput;
    };

    DigitalOutput* DigitalOutput;
};

class LinearActuator{
    public:
        LinearActuator(LinearActuatorConstructParameter*);
        int moveForMs(int ms);
};

#endif