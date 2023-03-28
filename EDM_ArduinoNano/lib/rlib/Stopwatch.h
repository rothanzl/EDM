#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <Loader.h>

class Stopwatch
{
private:
    unsigned long _startedAt;
    unsigned long _stoppedAt;
    bool _running;
    bool _highSpeed;
    unsigned long currentValue();
public:
    Stopwatch(bool highSpeed = false);
    void start();
    void stop();
    unsigned long elapsed();
    bool running();
};

Stopwatch::Stopwatch(bool highSpeed)
{
    _startedAt = 0;
    _stoppedAt = 0;
    _running = false;
    _highSpeed = highSpeed;
}

void Stopwatch::start(){
    _startedAt = currentValue();
    _running = true;
}

void  Stopwatch::stop(){
    _stoppedAt = currentValue();
    _running = false;
}

unsigned long Stopwatch::elapsed(){
    if(!_running)
        return _stoppedAt - _startedAt;

    return currentValue() - _startedAt;
}

bool Stopwatch::running(){
    return _running;
}

unsigned long Stopwatch::currentValue(){
    if(_highSpeed)
        return micros();
    
    return millis();
}


#endif