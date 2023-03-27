#ifndef _STOPWATCH_H
#define _STOPWATCH_H

#include <Loader.h>

class Stopwatch
{
private:
    unsigned long _startedAt;
    unsigned long _stoppedAt;
    bool _running;
public:
    Stopwatch();
    ~Stopwatch();
    void start();
    void stop();
    unsigned long elapsedMs();
    unsigned long elapsedMs();
};

Stopwatch::Stopwatch()
{
    _startedAt = 0;
    _stoppedAt = 0;
    _running = false;
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::start(){
    _startedAt = millis();
    _running = true;
}

void  Stopwatch::stop(){
    _stoppedAt = millis();
    _running = false;
}

unsigned long Stopwatch::elapsedMs(){
    if(!_running)
        return _stoppedAt - _startedAt;

    return millis() - _startedAt;
}


#endif