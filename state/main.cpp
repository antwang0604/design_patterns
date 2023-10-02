#include <iostream>

class State {
public:
    virtual ~State() = default;
    virtual void DoThis() = 0;
};

class ConcreteStateA : public State {
    void DoThis() {
        std::cout << "Concrete State A's Implementation" << std::endl;
    }
};

class ConcreteStateB : public State {
    void DoThis() {
        std::cout << "Concrete State B's Implementation" << std::endl;
    }
};

class Context {
private:
    State* state{nullptr};
public:
    void ChangeState(State* new_state){
        if(state!=nullptr) {
            delete state;
        }
        state = new_state;
    }

    void PerformThis() {
        state->DoThis();
    }
};

void ClientCode() {
    Context c;
    c.ChangeState(new ConcreteStateA());
    c.PerformThis();
    c.ChangeState(new ConcreteStateB());
    c.PerformThis();
}

int main() {
    ClientCode();
    return 0;
}