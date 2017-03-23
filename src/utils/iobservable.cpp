#include <algorithm>
#include "iobservable.h"

template<class T>
void IObservable<T>::Attach(IObserver<T> &observer)
{
    observers.push_back(&observer);
}

template<class T>
void IObservable<T>::Notify()
{
    for (auto observer : observers)
        observer->update(static_cast<T*>(this));
}