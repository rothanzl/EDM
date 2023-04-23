#include <Loader.h>
#include <SerialCommands.h>
#include <LinearActuator.h>
#include <AnalogInput.h>
#include <OrderHandler.h>
#include <RepeatLogger.h>
#include <Automation.h>

#define MOTOR_PIN_A 9
#define MOTOR_PIN_B 10
#define ANALOG_READ_PIN PIN_A0
#define POWER_SWITCH_PIN 3



SerialCommands* _serialCommands;
LinearActuator* _linearActuator;
AnalogInput* _analogInput;
OrderHandler* _orderHandler;
RepeatLogger* _repeatLogger;
LogRepeatMinMax* _voltageLogger;
Automation* _automation;


float _voltageValue;


void setupPowerSwitch();



void setup() {
  Serial.begin(9600, SERIAL_8O2);
  while (!Serial) { }

  _orderHandler = new OrderHandler();
  _linearActuator = new LinearActuator(new AnalogOutput(MOTOR_PIN_A), new AnalogOutput(MOTOR_PIN_B));
  _automation = new Automation(_linearActuator);
  _serialCommands = new SerialCommands(&Serial, _orderHandler, _linearActuator, _automation);
  _analogInput = new AnalogInput(ANALOG_READ_PIN);

  
  _voltageLogger = new LogRepeatMinMax("Analog ", " V");
  _repeatLogger = new RepeatLogger(&Serial, 1000, 1,  new RepeatLoggerValue* [1] { _voltageLogger });

  _voltageValue = 0;

  setupPowerSwitch();
}


void loop() {

  _serialCommands->ReadLink();
  _linearActuator->ping();
  _orderHandler->Handle();
  _voltageValue = _analogInput->readVoltage();
  _voltageLogger->set(_voltageValue);
  _automation->Ping(_voltageValue);


  _linearActuator->ping();

  _repeatLogger->TryPrint();


}

void setupPowerSwitch(){
  pinMode(POWER_SWITCH_PIN, OUTPUT);
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  // TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22); // 16MHz / 1024
  TCCR2B = _BV(CS21) | _BV(CS22); // 16MHz / 256
  OCR2B = 55;
}