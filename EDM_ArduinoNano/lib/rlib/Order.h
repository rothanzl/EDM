#ifndef _ORDER_H
#define _ORDER_H

#include <Loader.h>
#include <LinearActuator.h>

class Order{
    protected:
        bool _started;

    public:
        bool Started(){ return _started; };
        virtual bool Running() = 0;
        virtual void Start() = 0;
        Order(){
            _started = false;
        };
        virtual ~Order(){};
};

class LinearActuatorOrder : public Order{
    private:
        LinearActuator* _linearActuator;
        unsigned int _ms; 
        byte _value; 
        bool _direction;

    public:
        LinearActuatorOrder(LinearActuator* linearActuator, unsigned int ms, byte value, bool direction): Order(){
            _linearActuator = linearActuator;
            _ms = ms;
            _value = value;
            _direction = direction;
        };

        void Start(){
            _started = true;
            _linearActuator->moveForMs(_ms, _value, _direction);
        }

        bool Running(){
            return _linearActuator->isRunningAutomated();
        }
};


#endif