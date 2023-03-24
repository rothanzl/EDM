#include <unity.h>
#include <ArduinoFake.h>
#include <LinearActuator.h>


LinearActuator *lm;

void test01(){
    delete lm;

    TEST_MESSAGE("aaaaaaaaaaaa 1");


    fakeit::When(Method(ArduinoFake(), pinMode)).Return();
    fakeit::When(Method(ArduinoFake(), digitalWrite)).Return();



    


    lm = new LinearActuator(
        new LinearActuatorConstructParameter(
            new DigitalOutput(
                new DigitalOutputParams(13))));

    int result = lm->moveForMs(100);
    TEST_ASSERT_INT32_WITHIN_MESSAGE(0, 100, result, "Actuator move for ms should return 1");

    int anotherResult = lm->moveForMs(-100);
    TEST_ASSERT_INT32_WITHIN_MESSAGE(0, -100, anotherResult, "Actuator move for ms should return 1");
    
    delete lm;
}


int main(int argc, char **argv) {

    UNITY_BEGIN();
    RUN_TEST(test01);
    UNITY_END();

    return 0;
}