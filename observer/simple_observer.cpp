#include <list>
#include <iostream>

enum class State{
High = 0,
Medium = 1,
Low = 2,
Unknow = 3,
};

class Observer {
public:
    virtual ~Observer(){};
    virtual void Update(const State& s) = 0;
protected:
    State observed_state;
};

class Subject {
private:
    std::list<Observer*> observers{};
    State state{State::Unknow};
public:
    void AddObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void DeleteObserver(Observer* observer) {
        observers.remove(observer);
    }
    void NotifyObservers() {
        std::list<Observer *>::iterator iterator = observers.begin();
        while (iterator != observers.end()) {
            (*iterator)->Update(state);
            ++iterator;
        }
    }
    void UpdateState(const State& s) {
        state = s;
        NotifyObservers();
    }
};

class ConcreteObserver : public Observer{
public:
    void PrintStatus(){
        if(observed_state == State::High) {
            std::cout << "High" << std::endl;
        }
        else if(observed_state == State::Medium) {
            std::cout << "Medium" << std::endl;
        }
        else if (observed_state == State::Low) {
            std::cout << "Low" << std::endl;
        } else {
            std::cout << "Unknown" << std::endl;
        }
    }
    void Update(const State& s) override {
        observed_state = s;
        PrintStatus();
    }
};

int main() {
    ConcreteObserver* obs1 = new ConcreteObserver();
    ConcreteObserver* obs2 = new ConcreteObserver();
    ConcreteObserver* obs3 = new ConcreteObserver();
    ConcreteObserver* obs4 = new ConcreteObserver();
    Subject s;
    s.AddObserver(obs1);
    s.AddObserver(obs2);
    s.AddObserver(obs3);
    s.AddObserver(obs4);
    s.NotifyObservers();
    s.UpdateState(State::Medium);
    s.UpdateState(State::Low);

}

