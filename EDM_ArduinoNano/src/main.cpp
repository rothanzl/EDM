#include <Loader.h>
#include <SerialCommands.h>
#include <LinearActuator.h>

#define MOTOR_PIN_A 12
#define MOTOR_PIN_B 13


SerialCommands* _serialCommands;
LinearActuator* _linearActuator;


void moveForMsCallback(unsigned int ms, byte value, byte direction){
  _linearActuator->moveForMs(ms, value, (bool) direction);
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  
  _serialCommands = new SerialCommands(&Serial);
  _linearActuator = new LinearActuator(new AnalogOutput(MOTOR_PIN_A), new AnalogOutput(MOTOR_PIN_B));

  _serialCommands->RegisterMoveForMsCallback(moveForMsCallback);
}

void loop() {
  _serialCommands->ReadLink();
  _linearActuator->ping();
}