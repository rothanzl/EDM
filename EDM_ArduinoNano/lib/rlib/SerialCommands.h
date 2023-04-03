#ifndef _SERIAL_COMMANDS_H
#define _SERIAL_COMMANDS_H

#include <Loader.h>
#include <OrderHandler.h>

class SerialCommands{
    private:
        Stream * _serial = nullptr;
        String _buffer;
        OrderHandler* _orderHandler;
        LinearActuator* _linearActuator;

        void executeSingleCommand(String orderMessage){
            orderMessage.trim();

            if(orderMessage.indexOf("move") >= 0){
                orderMessage.replace("move", "");
                orderMessage.trim();

                int firstDelimIndex = orderMessage.indexOf(" ");
                String msString = orderMessage.substring(0, firstDelimIndex);
                msString.trim();
                unsigned int ms = msString.toInt();

                orderMessage = orderMessage.substring(firstDelimIndex+1);
                orderMessage.trim();
                int secondDelimIndex = orderMessage.indexOf(" ");
                String valueString = orderMessage.substring(0, secondDelimIndex);
                valueString.trim();
                byte value = valueString.toInt();

                orderMessage = orderMessage.substring(secondDelimIndex+1);
                orderMessage.trim();
                byte direction = orderMessage.toInt();

                
                _orderHandler->Register(new LinearActuatorOrder(_linearActuator, ms, value, (bool) direction));
            }
        };

    public:
        SerialCommands(Stream * serial, OrderHandler* orderHandler, LinearActuator* linearActuator){
            _serial = serial;
            _buffer = "";
            _orderHandler = orderHandler;
            _linearActuator = linearActuator;
        };
        void ReadLink(){
            if(!_serial)
                return;

            if(_serial->available() == 0)
                return;

            String line = _serial->readString();
            _serial->write(line.c_str());

            _buffer += line;

            int endIndex = _buffer.indexOf("end");
            if(endIndex == -1)
                return;


            String substring = _buffer.substring(0, endIndex);
            int deliminerIndex = substring.indexOf(";");

            while(deliminerIndex >= 0){
                String message = substring.substring(0, deliminerIndex);
                executeSingleCommand(message);

                substring = substring.substring(deliminerIndex+1);
                deliminerIndex = substring.indexOf(";");
            }

            executeSingleCommand(substring);

            _buffer = "";
        }
};

#endif