#include <iostream>

enum class State {A, B};

class Context
{

private:
    State s;

public:
    void PerformWork()
    {
        if (s == State::A)
        {
            std::cout << "Doing work in state A" << std::endl;
        }
        else if (s == State::B)
        {
            std::cout << "Doing work in state B" << std::endl;
        }
    }

    void SetState(const State& s)
    {
        this->s = s;
    }
};

int main()
{
    Context c;
    c.SetState(State::A);
    c.PerformWork();
    c.SetState(State::B);
    c.PerformWork();
}