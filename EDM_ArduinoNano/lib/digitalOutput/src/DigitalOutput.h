#ifndef _DIGITAL_OUTPUT_H
#define _DIGITAL_OUTPUT_H

struct DigitalOutputParams{
    DigitalOutputParams(char pin){
        Pin = pin;
        Reverse = false;
    };

    DigitalOutputParams(char pin, bool reverse){
        Pin = pin;
        Reverse = reverse;
    };

    char Pin;
    bool Reverse;
};

class DigitalOutput{
    private:
        DigitalOutputParams * Params;
    public:
        DigitalOutput(DigitalOutputParams * params);
        void Set();
        void Reset();
};


#endif