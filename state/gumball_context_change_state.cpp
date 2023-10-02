#include <iostream>

class State {
public:
    virtual ~State() = default;
    virtual void Dispense() = 0;
    virtual void Eject() = 0;
};

class NoCoin : public State {
    void Dispense() override {
        std::cout << "No Coin Loaded. Not Dispensing" << std::endl;
    }
    void Eject() override {
        std::cout << "No Coin Loaded. Not Ejecting" << std::endl;
    }
};

class CoinLoaded : public State {
    void Dispense() override {
        std::cout << "Dispensing Gumball" << std::endl;
    }
    void Eject() override {
        std::cout << "Ejecting Coin" << std::endl;
    }
};

class GumballMachine {
private:
    State* state{nullptr};

    void SetState(State* new_state){
        if(state!=nullptr) {
            delete state;
        }
        state = new_state;
    }
public:
    GumballMachine() {
        SetState(new NoCoin());
    }

    void Deposit(double value) {
        if(value>=0.25) {
            std::cout << "Money is loaded" << std::endl;
            SetState(new CoinLoaded());
        }
    }

    void RequestEject() {
        state->Eject();
        if(dynamic_cast<CoinLoaded*>(state)) {
            SetState(new NoCoin());
        }
    }

    void RequestDispense() {
        state->Dispense();
        if(dynamic_cast<CoinLoaded*>(state)) {
            SetState(new NoCoin());
        }
    }
};

void ClientCode() {
    GumballMachine gm;
    gm.Deposit(0.25);
    gm.RequestDispense();
    gm.RequestDispense();
    gm.Deposit(0.25);
    gm.RequestEject();
    gm.RequestEject();
}

int main() {
    ClientCode();
    return 0;
}