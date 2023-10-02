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
    Destroyer(){
        std::cout << "Destroyer Created" << std::endl;
    }
    void Fire() override {
        std::cout << "Destoryer Fire" << std::endl;
    }
    void Steer() override {
        std::cout << "Destroyer Steer" << std::endl;
    }
    ShipType type = ShipType::Destroyer;
};

class Carrier : public Battleship {
public:
    Carrier(){
        std::cout << "Carrier Created" << std::endl;
    }
    void Fire() override {
        std::cout << "Carrier Fire" << std::endl;
    }
    void Steer() override {
        std::cout << "Carrier Steer" << std::endl;
    }
    ShipType type = ShipType::Carrier;
};

// step 1
// class ShipCreator {
// public:
//     Battleship* FactoryMethod() {
//         if(type==ShipType::Carrier) {
//             return new Carrier();
//         }
//         else if(type==ShipType::Destroyer) {
//             return new Destroyer();
//         } else {
//             return nullptr;
//         }
//     };

//     void CreateShip(ShipType type) {
//         this->type = type;
//         Battleship* ptr = this->FactoryMethod();
//     }

//     ShipType type;
// };

// Step 2
class ShipCreator {
public:
    virtual Battleship* FactoryMethod() = 0;

    void CreateShip() {
        Battleship* ptr = this->FactoryMethod();
    }
};

class CarrierCreator : public ShipCreator {
    Battleship* FactoryMethod() override {
        return new Carrier();
    }
};

class DestroyerCreator : public ShipCreator {
    Battleship* FactoryMethod() override {
        return new Destroyer();
    }
};


int main() {
    // calling step 1
    // ShipCreator creator;
    // creator.CreateShip(ShipType::Carrier);
    // creator.CreateShip(ShipType::Destroyer);

    // calling step 2
    // CarrierCreator carrier_creator;
    // carrier_creator.CreateShip();
    // DestroyerCreator destroyer_creator;
    // destroyer_creator.CreateShip();

    ShipCreator* creator = new CarrierCreator();
    creator->CreateShip();
    creator = new DestroyerCreator();
    creator->CreateShip();

    return 0;
}