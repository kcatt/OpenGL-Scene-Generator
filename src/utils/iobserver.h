#ifndef __I_OBSERVER__H_
#define __I_OBSERVER__H_

template <class T>
class IObserver
{
    public:
        /**********************
         * Abstract Functions *
         **********************/
        virtual void Update(T* observable) = 0;
};

#endif