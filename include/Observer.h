#ifndef OBSERVER_H
#define OBSERVER_H
#include <forward_list>
#include <iostream>
#include <string>

class Observer_Interface
{
public:
    virtual ~Observer_Interface() {}
    virtual void OnNotifyAll() = 0;

};
class Subject_Interface
{
public:
    Subject_Interface() {}
    virtual ~Subject_Interface() {} // virtual destructors are necessary when you have a base class with derived classes and at least one virtual function.  The base class is assumed to be used polymorphically

    virtual void AddObserver(Observer_Interface* ob_i) {
        observers.push_front(ob_i);
    }

    virtual void RemoveObserver(Observer_Interface* ob_i) {
        observers.remove(ob_i);
    }

    virtual void NotifyAll() {
        for(Observer_Interface* o : observers)
            o->OnNotifyAll();
    }

private:   
    std::forward_list<Observer_Interface*> observers;
};


class Watcher : public Observer_Interface
{
public:
    explicit Watcher(const std::string& name): name(name) {};

    void OnNotifyAll() override {
        std::cout << name << " has been notified\n";
    }

private:
    std::string name;
};

class Concrete_Subject : public Subject_Interface
{
public:
    
};
#endif