#ifndef _SERIAL_COMMANDS_H
#define _SERIAL_COMMANDS_H

#include <Loader.h>

class SerialCommands{
    private:
        Serial_ * _serial;
    public:
        SerialCommands(Serial_ * serial){
            _serial = serial;
        };
        void ReadLink();
};


#endif