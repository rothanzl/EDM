#ifndef _REPEATLOGGER_H
#define _REPEATLOGGER_H

#include <Loader.h>
#include <Stopwatch.h>
#include <MemoryFree.h>

class RepeatLoggerValue{
    private:
    public:
        virtual String getMessage() = 0;
};

class LogRepeatLastString : public RepeatLoggerValue{
    private:
        String _value;
        const char* _prefix; 
        const char* _postfix;
    public:
        LogRepeatLastString(const char* prefix, const char* postfix){
            _prefix = prefix;
            _postfix = postfix;
        };
        void set(String value){
            _value = _prefix + value + _postfix;
        }
        String getMessage(){
            return _value.c_str();
        }
};

class LogRepeatMinMax : public RepeatLoggerValue{
    private:
        double _min = __DEC64_MAX__;
        double _max = -__DEC64_MIN__;
        const char* _prefix; 
        const char* _postfix;
    public:
        LogRepeatMinMax(const char* prefix, const char* postfix){
            _prefix = prefix;
            _postfix = postfix;
        };
        void set(double value){
            if(_min > value)
                _min = value;

            if(_max < value)
                _max = value;
        }
        String getMessage(){
            String result = (_prefix + String(_min) + String(" - ") + String(_max) + _postfix);
            _min = __DEC64_MAX__;
            _max = -__DEC64_MIN__;
            return result;
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
        RepeatLogger(Stream * serial, unsigned int periodMs, int count, RepeatLoggerValue** values);
        void TryPrint();
};


RepeatLogger::RepeatLogger(Stream * serial, unsigned int periodMs, int count, RepeatLoggerValue** values){
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

    float time = (float)millis() / 1000;

    String toWrite = String(time) + String(" ") + String(freeMemory()) + String("; ");
    for(int i = 0; i < _valuesCount; i++){
        RepeatLoggerValue* logger = _values[i];
        
        toWrite += logger->getMessage() + "; ";
    }
    toWrite += "\n";
    _serial->write(toWrite.c_str());
}


#endif