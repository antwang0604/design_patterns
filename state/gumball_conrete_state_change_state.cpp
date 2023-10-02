#include <iostream>

class GumballMachine; // forward declaration

class State {
protected:
    GumballMachine* gm{nullptr};
public:
    void SetContext(GumballMachine* gm){
        this->gm = gm;
    }
    virtual ~State() = default;
    virtual void Dispense() = 0;
    virtual void Eject() = 0;
};

class NoCoin : public State {
public:
    void Dispense() override;
    void Eject() override;
};
class CoinLoaded : public State {
public:
    void Dispense() override;
    void Eject() override;
};

class GumballMachine {
private:
    State* state{nullptr};
public:
    GumballMachine() {
        SetState(new NoCoin());
    }

    void SetState(State* new_state){
        if(state!=nullptr) {
            delete state;
        }
        state = new_state;
        state->SetContext(this);
    }

    void Deposit(double value) {
        if(value>=0.25) {
            std::cout << "Money is loaded" << std::endl;
            SetState(new CoinLoaded());
        }
    }

    void RequestEject() {
        state->Eject();
    }

    void RequestDispense() {
        state->Dispense();
    }
};

// Implementation of Class Functions
void NoCoin::Dispense() {
    std::cout << "No Coin Loaded. Not Dispensing" << std::endl;
}
void NoCoin::Eject() {
    std::cout << "No Coin Loaded. Not Ejecting" << std::endl;
}
void CoinLoaded::Dispense() {
    std::cout << "Dispensing Gumball" << std::endl;
    this->gm->SetState(new NoCoin());
}
void CoinLoaded::Eject() {
    std::cout << "Ejecting Coin" << std::endl;
    this->gm->SetState(new NoCoin());
}

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