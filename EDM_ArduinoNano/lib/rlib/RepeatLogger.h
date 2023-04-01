#ifndef _REPEATLOGGER_H
#define _REPEATLOGGER_H

#include <Loader.h>
#include <Stopwatch.h>

class RepeatLoggerValue{
    private:
    public:
        virtual String getMessage();
};

String RepeatLoggerValue::getMessage(){
    return String("");
}

class LogRepeatLastString : public RepeatLoggerValue{
    private:
        String _value;
    public:
        void set(String value){
            _value = value;
        }
        String getMessage(){
            return _value;
        }
};

class RepeatLogger{
    private:
        int _valuesCount;
        Stream* _serial;
        unsigned int _periodMs;
        Stopwatch* _stopwatch;
        RepeatLoggerValue** _values;
    public:
        RepeatLogger(Stream * serial, unsigned int periodMs, int count, RepeatLoggerValue* values[]);
        void TryPrint();
};


RepeatLogger::RepeatLogger(Stream * serial, unsigned int periodMs, int count, RepeatLoggerValue* values[]){
    _valuesCount = count;
    _serial = serial;
    _periodMs = periodMs;
    _stopwatch = new Stopwatch();
    _stopwatch->start();

    _values = values;
}

void RepeatLogger::TryPrint(){
    
    if(_stopwatch->elapsed() < _periodMs)
        return;

    _stopwatch->stop();
    _stopwatch->start();

    unsigned long time = millis();

    for(int i = 0; i < _valuesCount; i++){
        RepeatLoggerValue* logger = _values[i];
        String message = logger->getMessage();
        _serial->write((String(time) + String(" ")  + message + String("\n") ).c_str() );
    }
}


#endif