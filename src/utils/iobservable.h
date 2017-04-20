#ifndef __I_OBSERVABLE__H_
#define __I_OBSERVABLE__H_

#include <list>
#include <iostream>
#include <memory>
#include "iobserver.h"

template <class T>
class IObservable
{
    public:
        /********************
         * Public Functions *
         ********************/
        void Attach(std::shared_ptr<IObserver<T> > observer)
        {
            observers.push_back(observer);
        }

        void Notify()
        {
            for (auto observer : observers)
                observer->Update(static_cast<T*>(this));
        }

        void ClearObservers()
        {
            observers.clear();
        }

    private:
        /********************
         * Private Variable *
         ********************/
        std::list<std::shared_ptr<IObserver<T> > > observers;
};

#endif