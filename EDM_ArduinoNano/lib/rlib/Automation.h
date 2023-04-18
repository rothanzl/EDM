#ifndef _AUTOMATION_H
#define _AUTOMATION_H

#include <Loader.h>
#include <LinearActuator.h>

#define DOUCHE_LIMIT 20000
#define DOUCHE_UP_LIMIT 2000
#define DOUCHE_DOWN_LIMIT 1700

#define VOLTAGE_UPPER_LIMIT 2
#define VOLTAGE_LOWER_LIMIT 1.4

class Automation
{
private:
    bool _automate;
    LinearActuator* _linearActuator;
    bool _doucheUp;
    bool _doucheDown;
    Stopwatch* _doucheStopwatch;
public:
    Automation(LinearActuator* linearActuator){
        _automate = false;
        _linearActuator = linearActuator;
        _doucheUp = false;
        _doucheDown = false;
        _doucheStopwatch = new Stopwatch();
    }

    void Start(){
        _automate = true;
        _doucheStopwatch->start();
    }

    void Stop(){
        _automate = false;
        _linearActuator->move(0, false);
    }

    void Ping(float voltage){
        if(!_automate)
            return;

        if(voltage < VOLTAGE_LOWER_LIMIT){
            _linearActuator->move(255, false);
            return;
        }

        if(_doucheUp){
            if(_doucheStopwatch->elapsed() >= DOUCHE_UP_LIMIT){
                _doucheUp = false;
                _doucheDown = true;
                _linearActuator->move(255, true);
                _doucheStopwatch->start();
            }else{
                return;
            }
        }

        if(_doucheDown){
            if(_doucheStopwatch->elapsed() >= DOUCHE_DOWN_LIMIT){
                _doucheDown = false;
                _doucheStopwatch->start();
            }else{
                return;
            }
        }

        if(_doucheStopwatch->elapsed() >= DOUCHE_LIMIT){
            _doucheUp = true;
            _linearActuator->move(255, false);
            _doucheStopwatch->start();
            return;
        }


        if(voltage > VOLTAGE_UPPER_LIMIT){
            _linearActuator->move(70, true);
            return;
        }

        _linearActuator->move(0, true);
    }


};


#endif