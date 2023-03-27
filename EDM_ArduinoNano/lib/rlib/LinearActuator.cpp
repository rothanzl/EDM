#include <LinearActuator.h>

LinearActuator::LinearActuator(DigitalOutput* digitalOutput){
    _digitalOutput = digitalOutput;
};

int LinearActuator::moveForMs(int ms){
    return ms;
};