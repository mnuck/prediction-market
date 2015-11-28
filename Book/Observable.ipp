template <typename T>
//void Observable<T>::RegisterObserver(std::weak_ptr<Observer<T> > pObserver)
void Observable<T>::RegisterObserver(Observer<T>* pObserver)
{
    Observable<T>::_observers.push_back(pObserver);
    ++(Observable<T>::_obsCount);
}

template <typename T>
void Observable<T>::Notify(const T& notification)
{
    for (auto& wPtr : Observable<T>::_observers)
    {
//        auto sPtr = wPtr.lock();
//        if (sPtr)
            wPtr->OnNotify(notification);
    }
}
