#pragma once
// Observer pattern, modify to use smart ptr based on the code from https://refactoring.guru/design-patterns/observer/cpp/example

#include <iostream>
#include <list>
#include <string>
#include <memory>

class ISubject;

class IObserver : public std::enable_shared_from_this<IObserver>
{
public:
    virtual ~IObserver(){};
    virtual bool Subscribe(std::shared_ptr<ISubject> &subject) = 0;
    virtual void Update(const std::string &messageFromSubject) = 0;
};

class ISubject
{
public:
    virtual ~ISubject(){};
    virtual void Attach(std::shared_ptr<IObserver> &observer) = 0;
    virtual void Attach(std::weak_ptr<IObserver> observer) = 0;
    virtual void Detach(std::shared_ptr<IObserver> &observer) = 0;
    virtual void Detach(std::weak_ptr<IObserver> observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject
{
public:
    virtual ~Subject()
    {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    /**
     * The subscription management methods.
     */
    void Attach(std::shared_ptr<IObserver> &observer) override
    {
        _listObserver.emplace_back(observer);
    }

    void Attach(std::weak_ptr<IObserver> observer) override
    {
        _listObserver.push_back(observer);
    }

    void Detach(std::shared_ptr<IObserver> &observer) override
    {
        _listObserver.remove_if([&](std::weak_ptr<IObserver> wptr) // C++ 20
                                { 
        if(!wptr.expired()){
            if(wptr.lock().get() == observer.get()){
                return true;
            }
        }    
        return false; });
    }

    void Detach(std::weak_ptr<IObserver> observer) override
    {
        if (!observer.expired())
        {
            auto sp = observer.lock();
            Detach(sp);
        }
    }

    void Notify() override
    {
        auto iter = _listObserver.begin();
        HowManyObserver();
        while (iter != _listObserver.end()){
            if (!(iter->expired())){
                auto sp = iter->lock();
                sp->Update(_message);
                ++iter;
            }else{
               iter = _listObserver.erase(iter);
            }
        }
    }

    void CreateMessage(std::string message = "Empty")
    {
        this->_message = message;
        Notify();
    }
    void HowManyObserver()
    {
        std::cout << "There are " << _listObserver.size() << " observers in the list.\n";
    }

    /**
     * Usually, the subscription logic is only a fraction of what a Subject can
     * really do. Subjects commonly hold some important business logic, that
     * triggers a notification method whenever something important is about to
     * happen (or after it).
     */
    void SomeBusinessLogic()
    {
        this->_message = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    std::list<std::weak_ptr<IObserver>> _listObserver;
    std::string _message;
};

class Observer : public IObserver
{
public:
    Observer()
    {   // Don't ever use shared_from_this or weak_from_this in a ctor!!!
        // Because it is not constructed yet, therefore will get an bad_weak_ptr
        this->_number = Observer::_staticNumber++;
    }

    virtual bool Subscribe(std::shared_ptr<ISubject> &subject) override
    {
        if(subject){
            _subject = subject;
            _subject->Attach(weak_from_this());
            std::cout << "Subscribe sucesseful! \nHi, I'm the Observer \"" << Observer::_staticNumber 
                << "subscribe for subject"<< subject.get() << "\".\n";
            return true;
        }
        std::cout<<"Subscribe failed!\n";
        return false;
    }

    virtual ~Observer()
    {
        std::cout << "Goodbye, I was the Observer \"" << this->_number << "\".\n";
    }

    void Update(const std::string &messageFromSubject) override
    {
        _messageFromSubject = messageFromSubject;
        PrintInfo();
    }
    void RemoveMeFromTheList()
    {
        _subject->Detach(weak_from_this());
        std::cout << "Observer \"" << _number << "\" removed from the list.\n";
    }
    void PrintInfo()
    {
        std::cout << "Observer \"" << this->_number << "\": a new message is available --> " << this->_messageFromSubject << "\n";
    }

private:
    std::string _messageFromSubject;
    std::shared_ptr<ISubject> _subject;
    static int _staticNumber;
    int _number;
};

int Observer::_staticNumber = 0;
