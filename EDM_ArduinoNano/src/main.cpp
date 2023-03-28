#include <Loader.h>
#include <SerialCommands.h>
#include <LinearActuator.h>
#include <AnalogInput.h>

#define MOTOR_PIN_A 12
#define MOTOR_PIN_B 13
#define ANALOG_READ_PIN PIN_A0

#define JUSTIFI_UPPER_VALUE 4.0
#define JUSTIFI_LOWER_VALUE 3.0
#define JUSTIFI_SPEED 254
#define JUSTIFI_DIRECTION true



SerialCommands* _serialCommands;
LinearActuator* _linearActuator;
AnalogInput* _analogInput;

float _voltageValue;


void moveForMsCallback(unsigned int ms, byte value, byte direction){
  _linearActuator->moveForMs(ms, value, (bool) direction);
}

void justification(){
  if(_voltageValue > JUSTIFI_UPPER_VALUE){
    _linearActuator->move(JUSTIFI_SPEED, JUSTIFI_DIRECTION);
  }else if(_voltageValue < JUSTIFI_LOWER_VALUE){
    _linearActuator->move(JUSTIFI_SPEED, ! JUSTIFI_DIRECTION);
  }else{
    _linearActuator->move(0, JUSTIFI_DIRECTION);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  
  _serialCommands = new SerialCommands(&Serial);
  _linearActuator = new LinearActuator(new AnalogOutput(MOTOR_PIN_A), new AnalogOutput(MOTOR_PIN_B));
  _analogInput = new AnalogInput(ANALOG_READ_PIN);

  _voltageValue = 0;
  _serialCommands->RegisterMoveForMsCallback(moveForMsCallback);
}

void loop() {
  _serialCommands->ReadLink();
  _linearActuator->ping();
  _voltageValue = _analogInput->readVoltage();

  if(!_linearActuator->isRunningAutomated())
    justification();
}