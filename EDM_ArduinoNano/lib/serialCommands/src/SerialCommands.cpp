#include <SerialCommands.h>

void SerialCommands::ReadLink(){
  if(!_serial)
    return;

  if(_serial->available() == 0)
    return;

  String line = _serial->readString();
  _serial->write(line.c_str());
};

