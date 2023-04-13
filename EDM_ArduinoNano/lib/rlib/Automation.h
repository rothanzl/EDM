#ifndef _AUTOMATION_H
#define _AUTOMATION_H

#include <Loader.h>
#include <LinearActuator.h>

class Automation
{
private:
    bool _automate;
    float _voltageUpperLimit;
    float _voltageLowerLimit;
    LinearActuator* _linearActuator;
public:
    Automation(LinearActuator* linearActuator){
        _automate = false;
        _voltageUpperLimit = 3.3;
        _voltageLowerLimit = 1.;
        _linearActuator = linearActuator;
    }

    void Start(){
        _automate = true;
    }

    void Stop(){
        _automate = false;
        _linearActuator->move(0, false);
    }

    void Ping(float voltage){
        if(!_automate)
            return;

        if(voltage > _voltageUpperLimit){
            _linearActuator->move(70, true);
        }else if(voltage < _voltageLowerLimit){
            _linearActuator->move(255, false);
        }
    }


};


#endif