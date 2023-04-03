#ifndef _ORDER_HANDLER_H
#define _ORDER_HANDLER_H

#include <Loader.h>
#include <Order.h>

class OrderHandler{
    private:
        static const int MaxSize = 100;
        Order* _stack[MaxSize];
        int _freePosition;

    public:
        OrderHandler(){
            _freePosition = 0;
        };

        void Handle(){
            if(_freePosition == 0)
                return;

            if(!_stack[0]->Started())
                _stack[0]->Start();

            if(_stack[0]->Running())
                return;
            
            delete _stack[0];
            for(int i = 1; i < _freePosition; i++){
                _stack[i-1] = _stack[i];
            }

            if(_freePosition > 0)
                _freePosition--;
        }

        bool Register(Order* order){
            if(_freePosition == MaxSize)
                return false;
            
            _stack[_freePosition] = order;
            _freePosition++;

            return true;
        }
};

#endif