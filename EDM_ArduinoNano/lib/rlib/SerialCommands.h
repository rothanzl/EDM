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

        char** splitMessage(const char* message, char deliminer, byte count){
            const char* result[count];

            String m = String(message);
            m.trim();
            
            for(byte i = 0; i < count; i++){
                int firstDelimIndex = m.indexOf(deliminer);
                String substring = m.substring(0, firstDelimIndex);
                substring.trim();
                result[i] = substring.c_str();
                m = m.substring(firstDelimIndex+1);
            }

            return result;
        };

        void executeSingleCommand(String orderMessage){
            orderMessage.trim();


            _serial->println((String("single command: ") + orderMessage).c_str());
            _serial->flush();
            _serial->println((String("move index: ") + String(orderMessage.indexOf("move"))).c_str());
            _serial->flush();

            if(orderMessage.indexOf("move") >= 0){
                _serial->println((String("move: ") + orderMessage).c_str());

                orderMessage.replace("move", "");
                orderMessage.trim();

                //const char** splittedMessage = splitMessage(orderMessage.c_str(), ' ', 3);

                //_serial->println((String(splittedMessage[0])).c_str());


                //_serial->println(String(String(splittedMessage[0]).toInt()));

                // _orderHandler->Register(new LinearActuatorOrder(
                //     _linearActuator, 
                //     String(splittedMessage[0]).toInt(), 
                //     String(splittedMessage[1]).toInt(), 
                //     (bool) String(splittedMessage[2]).toInt()));

                return;

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