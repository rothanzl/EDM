#include <unity.h>
#include <Loader.h>
#include <LinearActuator.h>
#include <SerialCommands.h>


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
    TEST_MESSAGE((String("Move for ") + String(ms) + String(" ms, value ") + String(value) + String(" direction ") + String(direction)).c_str());
};


void testSerial(){

    fakeit::When(Method(ArduinoFake(Serial), readString)).Return("move 200; move -1", "00; move 100 "," end");
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




int main(int argc, char **argv) {

    UNITY_BEGIN();
    RUN_TEST(test01);
    RUN_TEST(testSerial);
    UNITY_END();

    return 0;
}