#include <SerialCommands.h>

void SerialCommands::ReadLink(){
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
};

void SerialCommands::executeSingleCommand(String orderMessage){
  orderMessage.replace(" ", "");

  if(orderMessage.indexOf("move") >= 0){
      if(_moveForMsCallback == nullptr)
        return;

      orderMessage.replace("move", "");

      int ms = orderMessage.toInt();

      _moveForMsCallback(ms);
  }
};