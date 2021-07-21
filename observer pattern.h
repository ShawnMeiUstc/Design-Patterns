#pragma once
#include "ipublisher and isubscriber.h"

/**
 * Observer Design Pattern
 *
 * Intent: Lets you define a subscription mechanism to notify multiple objects
 * about any events that happen to the object they're observing.
 *
 * Note that there's a lot of different terms with similar meaning associated
 * with this pattern. Just remember that the Subject is also called the
 * Publisher and the Observer is often called the Subscriber and vice versa.
 * Also the verbs "observe", "listen" or "track" usually mean the same thing.
 */

class IObserver : public enable_shared_from_this<IObserver> {
public:
    virtual ~IObserver() {};
    virtual void Update(const std::string& message_from_subject) = 0;
};

class ISubject : public enable_shared_from_this<ISubject> {
public:
    virtual ~ISubject() {};
    virtual void Attach(const shared_ptr<IObserver> observer) = 0;
    virtual void Detach(const shared_ptr<IObserver> observer) = 0;
    virtual void Notify() = 0;
};

/**
 * The Subject owns some important state and notifies observers when the state
 * changes.
 */

class Subject : public ISubject {
public:
    virtual ~Subject() {
        std::cout << "Goodbye, I was the Subject.\n";
    }

    /**
     * The subscription management methods.
     */
    void Attach(const shared_ptr<IObserver> observer) override {
        list_observer_.emplace_back(observer);
    }
    void Detach(const shared_ptr<IObserver> observer) override {
        list_observer_.remove_if([&](const weak_ptr<IObserver> wptr) -> bool {return observer == wptr.lock(); });
    }
    void Notify() override {
        list_observer_.remove_if([](const weak_ptr<IObserver> wptr) -> bool {return wptr.expired(); });
        HowManyObserver();
        for_each(list_observer_.begin(), list_observer_.end(), [&](const weak_ptr<IObserver> wptr) {wptr.lock()->Update(message_); });
    }

    void CreateMessage(std::string message = "Empty") {
        this->message_ = message;
        Notify();
    }
    void HowManyObserver() {
        std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
    }

    /**
     * Usually, the subscription logic is only a fraction of what a Subject can
     * really do. Subjects commonly hold some important business logic, that
     * triggers a notification method whenever something important is about to
     * happen (or after it).
     */
    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        std::cout << "I'm about to do some thing important\n";
    }

private:
    std::list<weak_ptr<IObserver>> list_observer_;
    std::string message_;
};

class Observer : public IObserver {
public:
    Observer() {
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }

    void Update(const std::string& message_from_subject) override {
        message_from_subject_ = message_from_subject;
        PrintInfo();
    }
    void AddToTheList(shared_ptr<ISubject> subject) {
        subject->Attach(shared_from_this());
    }

    void RemoveMeFromTheList(shared_ptr<ISubject> subject) {
        subject->Detach(shared_from_this());
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
    void PrintInfo() {
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
    }

private:
    std::string message_from_subject_;
    static int static_number_;
    int number_;
};

int Observer::static_number_ = 0;

void ClientCode() {
    shared_ptr<Subject> subject = make_shared<Subject>();
    shared_ptr<Observer> observer1 = make_shared<Observer>();
    observer1->AddToTheList(subject);
    shared_ptr<Observer> observer2 = make_shared<Observer>();
    observer2->AddToTheList(subject);

    shared_ptr<Observer> observer3 = make_shared<Observer>();
    observer3->AddToTheList(subject);

    shared_ptr<Observer> observer4;
    shared_ptr<Observer> observer5;


    subject->CreateMessage("Hello World! :D");
    observer3->RemoveMeFromTheList(subject);

    subject->CreateMessage("The weather is hot today! :p");
    observer4 = make_shared<Observer>();
    observer4->AddToTheList(subject);


    observer2->RemoveMeFromTheList(subject);
    observer5 = make_shared<Observer>();
    observer5->AddToTheList(subject);


    subject->CreateMessage("My new car is great! ;)");
    observer5->RemoveMeFromTheList(subject);

    observer4->RemoveMeFromTheList(subject);
    observer1->RemoveMeFromTheList(subject);
}

/* use the pattern */
class ObserverPatternPublisher final : public IPublisher
{
public:
    virtual void UsePattern() override
    {
        cout << "===============>>>>>>> Test Observer Pattern <<<<<<<===============\n";
        ClientCode();
    }
};