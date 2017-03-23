#ifndef __I_OBSERVABLE__H_
#define __I_OBSERVABLE__H_

#include <list>
#include "iobserver.h"

template <class T>
class IObservable
{
    public:
        /********************
         * Public Functions *
         ********************/
        void Attach(IObserver<T> &observer);
        void Notify();

    private:
        /********************
         * Private Variable *
         ********************/
        std::list<IObserver<T> *> observers;
};

#endif