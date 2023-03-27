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
  orderMessage.trim();

  if(orderMessage.indexOf("move") >= 0){
      if(_moveForMsCallback == nullptr)
        return;

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

      _moveForMsCallback(ms, value, direction);
  }
};
