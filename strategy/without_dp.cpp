#include <iostream>

enum class Strategy {A, B};

class Context {

private:
    Strategy s;

public:
    void PerformWork()
    {
        if (s == Strategy::A)
        {
            std::cout << "Doing work using strategy A" << std::endl;
        }
        else if (s == Strategy::B)
        {
            std::cout << "Doing work using strategy B" << std::endl;
        }
    }

    void SetStrategy(const Strategy& s)
    {
        this->s = s;
    }
};

int main()
{
    Context c;
    c.SetStrategy(Strategy::A);
    c.PerformWork();
    c.SetStrategy(Strategy::B);
    c.PerformWork();
}