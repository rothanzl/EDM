#include <Loader.h>
#include <SerialCommands.h>
#include <LinearActuator.h>

SerialCommands* _serialCommands;
LinearActuator* _linearActuator;


void moveForMsCallback(int ms){
  _linearActuator->moveForMs(ms);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  
  _serialCommands = new SerialCommands(&Serial);
  _linearActuator = new LinearActuator(new DigitalOutput(13, false));

  _serialCommands->RegisterMoveForMsCallback(moveForMsCallback);
}

void loop() {
  _serialCommands->ReadLink();
}