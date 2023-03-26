#ifndef _LINEARACTUATOR_H
#define _LINEARACTUATOR_H

#include <DigitalOutput.h>



class LinearActuator{
    private:
        DigitalOutput* _digitalOutput;
    public:
        LinearActuator(DigitalOutput*);
        int moveForMs(int ms);
};

#endif