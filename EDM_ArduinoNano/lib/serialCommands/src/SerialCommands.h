#ifndef _SERIAL_COMMANDS_H
#define _SERIAL_COMMANDS_H

#include <Loader.h>

class SerialCommands{
    private:
        Serial_ * _serial;
        String _buffer;
        void (*_moveForMsCallback)(int);
        void executeSingleCommand(String commandMessage);
    public:
        SerialCommands(Serial_ * serial){
            _serial = serial;
            _buffer = "";
            _moveForMsCallback = nullptr;
        };
        void ReadLink();
        void RegisterMoveForMsCallback(void (*clbk)(int)) { _moveForMsCallback = clbk; };
};


#endif