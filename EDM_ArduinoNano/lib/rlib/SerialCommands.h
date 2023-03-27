#ifndef _SERIAL_COMMANDS_H
#define _SERIAL_COMMANDS_H

#include <Loader.h>

class SerialCommands{
    private:
        Stream * _serial = nullptr;
        String _buffer;
        void (*_moveForMsCallback)(unsigned int, byte, byte);
        void executeSingleCommand(String commandMessage);
    public:
        SerialCommands(Stream * serial){
            _serial = serial;
            _buffer = "";
            _moveForMsCallback = nullptr;
        };
        void ReadLink();
        void RegisterMoveForMsCallback(void (*clbk)(unsigned int, byte, byte)) { _moveForMsCallback = clbk; };
};

#endif