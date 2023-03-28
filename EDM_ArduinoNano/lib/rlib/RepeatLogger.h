#ifndef _REPEATLOGGER_H
#define _REPEATLOGGER_H

#include <Loader.h>

class RepeatLoggerValue{
    private:
    public:
};

class RepeatLogger{
    private:
    public:
        RepeatLogger(Stream * serial, unsigned int periodMs, RepeatLoggerValue * values[]);
};


RepeatLogger::RepeatLogger(Stream * serial, unsigned int periodMs, RepeatLoggerValue * values[]){

}

#endif