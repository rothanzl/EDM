#ifndef _DIGITAL_OUTPUT_H
#define _DIGITAL_OUTPUT_H

class DigitalOutput{
    private:
        char _pin = 0;
        bool _reverse = 0;
    public:
        DigitalOutput(char pin, bool reverse = false);
        void Set();
        void Reset();
};

#endif