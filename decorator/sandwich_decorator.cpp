#include <string>
#include <iostream>

class SandwichOrder{
public:
    virtual int GetCost() = 0;
    virtual std::string GetIngredient() = 0;
};

class BasicSandwich : public SandwichOrder{
public:
    int cost = 5;
    int GetCost() {
        // std::cout << "cost of basic sandwich is " << cost << std::endl;
        return cost;
    }
    std::string GetIngredient() {
        return "Basic Bread, Basic Meat";
    }
};

class DeluxeSandwich : public SandwichOrder{
public:
    int cost = 8;
    int GetCost() {
        // std::cout << "cost of deluxe sandwich is " << cost << std::endl;
        return cost;
    }
    std::string GetIngredient() {
        return "Oraganic Bread, Organic Meat, Cheese, Veggie";
    }
};

class Decorator : public SandwichOrder {
public:
    SandwichOrder* order_;
    Decorator(SandwichOrder* order) : order_{order} {}
    int GetCost() { 
        return order_->GetCost();
    }
    std::string GetIngredient() {
        return order_->GetIngredient();
    }
};

class CondimentDecorator : public Decorator {
public:
    std::string condiment_;
    int cost = 1;

    CondimentDecorator(std::string condiment, SandwichOrder* order) : 
        condiment_{condiment}, Decorator(order) {}

    int GetCost() {
        return cost + Decorator::GetCost();
    }

    std::string GetIngredient() {
        return condiment_ + " " + order_->GetIngredient();
    }

};

class SideDecorator : public Decorator {
public:
    std::string side_;
    int cost = 2;

    SideDecorator(std::string side, SandwichOrder* order) : 
        side_{side}, Decorator(order) {}
    int GetCost() {
        return cost + Decorator::GetCost();
    }

    std::string GetIngredient() {
        return side_ + " " + order_->GetIngredient();
    }

};


void ServeOrder(SandwichOrder* order) {
    std::cout << "Total Cost: " << order->GetCost() << std::endl;
    std::cout << "Ingredients: " << order->GetIngredient() << std::endl;
}

int main () {
    SandwichOrder* sandwich1 = new DeluxeSandwich;
    SandwichOrder* decorated1 = new CondimentDecorator("mayo", sandwich1);
    SandwichOrder* decorated2 = new SideDecorator("pickle", decorated1);
    SandwichOrder* decorated3 = new CondimentDecorator("mustard", decorated2);
    SandwichOrder* final_order = new SideDecorator("onion", decorated3);
    ServeOrder(final_order);

    

    // SandwichOrder* sandwich2 = new Decorator(sandwich1);
    // std::cout << sandwich2->GetCost() << std::endl;
    // std::cout << sandwich2->GetIngredient() << std::endl;

    // SandwichOrder* sandwich3 = new CondimentDecorator("ketchup", sandwich2);
    // std::cout << sandwich3->GetCost() << std::endl;
    // std::cout << sandwich3->GetIngredient() << std::endl;

    // SandwichOrder* sandwich4 = new CondimentDecorator("mustard", sandwich3);
    // std::cout << sandwich4->GetCost() << std::endl;
    // std::cout << sandwich4->GetIngredient() << std::endl;



    return 0;
}