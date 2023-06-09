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


void testSerial(){

    fakeit::When(Method(ArduinoFake(Serial), readString)).Return("   move   1000   255   1 end  ;    move   1", "00   200   0  ;   move   1   20   1   ","   end  ");
    fakeit::When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);
    fakeit::When(OverloadedMethod(ArduinoFake(Serial), write, size_t(const uint8_t *, size_t))).AlwaysReturn(1);

    TEST_MESSAGE("a");

    SerialCommands * serialCommands = new SerialCommands(&Serial, new OrderHandler(), 
        new LinearActuator(new AnalogOutput(A0), new AnalogOutput(A1)));
    
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

    LogRepeatLastString* logString = new LogRepeatLastString();
    RepeatLoggerValue* values[] = { new RepeatLoggerValue(), new RepeatLoggerValue(), logString};
    int count = sizeof(values) / sizeof(RepeatLoggerValue*);
    RepeatLogger * repeatLogger = new RepeatLogger(&Serial, 1000, count, values);

    TEST_MESSAGE( (String("Length ") + String(sizeof(values) / sizeof(RepeatLoggerValue*))).c_str() );


    fakeit::When(OverloadedMethod(ArduinoFake(Serial), write, size_t(const uint8_t *, size_t))).AlwaysReturn(1);
    repeatLogger->TryPrint();

    TEST_ASSERT_EQUAL_STRING("", values[0]->getMessage().c_str());
    TEST_ASSERT_EQUAL_STRING("", values[1]->getMessage().c_str());

    logString->set("this is test message!");
    TEST_ASSERT_EQUAL_STRING("this is test message!", values[2]->getMessage().c_str());

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