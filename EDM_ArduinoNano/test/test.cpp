#include <unity.h>
#include <Loader.h>
#include <LinearActuator.h>
#include <SerialCommands.h>
#include <AnalogInput.h>
#include <RepeatLogger.h>


LinearActuator *lm = nullptr;

void test01(){

    TEST_MESSAGE("aaaaaaaaaaaa 1");


    fakeit::When(Method(ArduinoFake(), pinMode)).AlwaysReturn();
    fakeit::When(Method(ArduinoFake(), analogWrite)).AlwaysReturn();
    fakeit::When(Method(ArduinoFake(), millis)).AlwaysReturn();
    
    lm = new LinearActuator(new AnalogOutput(12), new AnalogOutput(13));

    int result = lm->moveForMs(100, 255, true);
    TEST_ASSERT_INT32_WITHIN_MESSAGE(0, 1, result, "Actuator move for ms should return 1");

    int anotherResult = lm->moveForMs(100, 255, false);
    TEST_ASSERT_INT32_WITHIN_MESSAGE(0, 1, anotherResult, "Actuator move for ms should return 1");
    
    delete lm;
}

void moveForMsCallback(unsigned int ms, byte value, byte direction){
    TEST_MESSAGE((String("Move for '") + String(ms) + String("' ms, value '") + String(value) + String("' direction '") + String(direction) + String("'")).c_str());
};


void testSerial(){

    fakeit::When(Method(ArduinoFake(Serial), readString)).Return("   move   200   255   1   ;    move   1", "00   200   0  ;   move   1   20   1   ","   end  ");
    fakeit::When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);
    fakeit::When(OverloadedMethod(ArduinoFake(Serial), write, size_t(const uint8_t *, size_t))).AlwaysReturn(1);

    TEST_MESSAGE("a");

    SerialCommands * serialCommands = new SerialCommands(&Serial);
    serialCommands->RegisterMoveForMsCallback(moveForMsCallback);
    serialCommands->ReadLink();
    serialCommands->ReadLink();
    serialCommands->ReadLink();

    TEST_MESSAGE("c");
};

void testAnalogRead(){
    AnalogInput * analogInput = new AnalogInput(A0);

    fakeit::When(Method(ArduinoFake(), analogRead)).Return(0.);
    float v = analogInput->readVoltage();
    TEST_ASSERT_FLOAT_WITHIN(0., 0, v);
    
    fakeit::When(Method(ArduinoFake(), analogRead)).Return(1023);
    v = analogInput->readVoltage();
    TEST_ASSERT_FLOAT_WITHIN(0., 5.0, v);

    fakeit::When(Method(ArduinoFake(), analogRead)).Return(511);
    v = analogInput->readVoltage();
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.5, v);

}

void testRepeatLogger(){

    RepeatLoggerValue * values[] = { new RepeatLoggerValue(), new RepeatLoggerValue() };
    RepeatLogger * repeatLogger = new RepeatLogger(&Serial, 1000, values);

    
    TEST_MESSAGE( (String("Length ") + String(sizeof(values) / sizeof(RepeatLoggerValue*))).c_str() );
}

int main(int argc, char **argv) {

    UNITY_BEGIN();
    RUN_TEST(test01);
    RUN_TEST(testSerial);
    RUN_TEST(testAnalogRead);
    RUN_TEST(testRepeatLogger);
    UNITY_END();

    return 0;
}