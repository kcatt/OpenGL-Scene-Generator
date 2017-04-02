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
        void Attach(IObserver<T> &observer)
        {
            observers.push_back(&observer);
        }

        void Notify()
        {
            for (auto observer : observers)
                observer->Update(static_cast<T*>(this));
        }

    private:
        /********************
         * Private Variable *
         ********************/
        std::list<IObserver<T> *> observers;
};

#endif