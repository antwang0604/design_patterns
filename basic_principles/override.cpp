#include <string>
#include <iostream>

using namespace std;

struct Animal {
    string base_name{"animal"};
};
struct Cat : public Animal {
    string derived_name{"cat"};
};
struct PersianCat : public Cat {
    string type_name{"Persian Cat"};
};

class Base {
public:
    virtual void func(Animal a){
        std::cout << a.base_name << std::endl;
    }
};

class Derived : public Base {
public:
    void func(Cat c){
        std::cout << "hi " << c.base_name << std::endl;
    }
};

void InvokeFunction(Base* b) {
    Animal a;
    b->func(a);
}

int main() {
    Base b;
    Base* bptr = new Derived();
    Derived d;
    Animal a;
    Cat c;
    InvokeFunction(new Derived());
    return 0;
}