// Demonstrates simple factory method which provides generalized interface to create objects
// Instead of choosing the right class type, the user simply needs to call the Factory method, CreateShipFactory()

#include <iostream>

enum class ShipType{
    Destroyer,
    Carrier,
};

class Battleship {
public:
    Battleship() {
        std::cout << "Battleship Created" << std::endl;
    }
    virtual void Fire() = 0;
    virtual void Steer() = 0;
};

class Destroyer : public Battleship {
public:
    Destroyer(){}
    void Fire() override {
        std::cout << "Destoryer Fire" << std::endl;
    }
    void Steer() override {
        std::cout << "Destroyer Steer" << std::endl;
    }
};

class Carrier : public Battleship {
public:
    Carrier(){}
    void Fire() override {
        std::cout << "Carrier Fire" << std::endl;
    }
    void Steer() override {
        std::cout << "Carrier Steer" << std::endl;
    }
};

Battleship* CreateShipFactory(ShipType type){
    Battleship* pShip = nullptr;
    if(type == ShipType::Carrier) {
        pShip = new Carrier();
    }
    else if(type == ShipType::Destroyer) {
        pShip = new Destroyer();
    }
    return pShip;
}

void CreateObjectsUsingClassInterface(){
    Destroyer d;
    Carrier c;
    d.Fire();
    c.Fire();
}

void CreateObjectUsingFactoryMethod() {
    Battleship* d = CreateShipFactory(ShipType::Destroyer);
    Battleship* c = CreateShipFactory(ShipType::Carrier);
    d->Fire();
    c->Fire();
}



int main() {
    // Instead of specifying the correct constructor to create objects
    CreateObjectsUsingClassInterface();
    // We can create a factory method, a simple function to generalize the creation
    CreateObjectUsingFactoryMethod();
    
    return 0;
}