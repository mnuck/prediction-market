#ifndef OBSERVER_HPP
#define OBSERVER_HPP

template <typename T>
class Observer
{
public:
    virtual ~Observer() {}
    virtual void OnNotify(const T& notification) = 0;
protected:
    Observer() {}
    Observer(const Observer& rhs) {}
    Observer& operator=(const Observer& source) { return *this; }
};

#endif // OBSERVER_HPP
