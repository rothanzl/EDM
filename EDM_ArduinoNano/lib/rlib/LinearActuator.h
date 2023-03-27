#ifndef _LINEARACTUATOR_H
#define _LINEARACTUATOR_H

#include <AnalogOutput.h>
#include <Stopwatch.h>

class LinearActuator{
    private:
        AnalogOutput* _outputA = nullptr;
        AnalogOutput* _outputB = nullptr;
        Stopwatch* _stopwatch = nullptr;
        unsigned int _duration = 0;
        
    public:
        LinearActuator(AnalogOutput* outputA, AnalogOutput* outputB);
        ~LinearActuator();
        int moveForMs(unsigned int ms, byte value, bool direction);
        int move(byte value, bool direction);
        void ping();
};


LinearActuator::LinearActuator(AnalogOutput* outputA, AnalogOutput* outputB){
    _outputA = outputA;
    _outputB = outputB;
    _stopwatch = new Stopwatch();
};

LinearActuator::~LinearActuator(){
    delete _stopwatch;
}

int LinearActuator::moveForMs(unsigned int ms, byte value, bool direction){
    _stopwatch->start();
    _duration = ms;

    return this->move(value, direction);
};

int LinearActuator::move(byte value, bool direction){
    if(direction){
        _outputA->set(0);
        _outputB->set(value);
    }else{
        _outputA->set(value);
        _outputB->set(0);
    }

    return 1;
}

void LinearActuator::ping(){
    if(!_stopwatch->running())
        return;

    if(_stopwatch->elapsedMs() < _duration)
        return;

    _stopwatch->stop();
    _duration = 0;

    _outputA->set(0);
    _outputB->set(0);
}

#endif