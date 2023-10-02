#include <iostream>
#include <vector>

// This example demonstrates a simple builder pattern with a director (encapsulates the builder)

enum class Bread {Toast, HotdogBun, BurgerBun};
enum class Protein {BeefPatty, Dog, Bacon};
enum class Side{Lettuce, Tomato, Onions, Cheese};
enum class Sauce {Mayo, Ketchup, YumYum, Mustard};
enum class Wrapper {Paper, Box, Plastic};

// step 1: Clearly define building steps
// Burger, Hot Dog, BLT
// AddBread -> AddProtein -> AddSides -> Add Sauce -> AddWrapper -> ReturnProduct
class Sandwich {
public:
    Sandwich() {
        std::cout << "Default Construction of Sandwich" << std::endl;
        sauces = std::vector<Sauce>();
        sides = std::vector<Side>();
    }
    Sandwich(Bread b, Protein p, std::vector<Side> sides, std::vector<Sauce> sauces, Wrapper w) :
    b{b}, p{p}, sides{sides}, sauces{sauces}, w{w} {
        std::cout << "A Sandwich is Constructed" << std::endl;
    }
    Bread b;
    Protein p;
    std::vector<Side> sides;
    std::vector<Sauce> sauces;
    Wrapper w;
};


// step 2: Declare these step using a base interface
class SandwichBuilder {
public:
    virtual void AddBread() = 0;
    virtual void AddProtein() = 0;
    void AddSide(Side s) {product.sides.push_back(s);}
    void AddSauce(Sauce s) {product.sauces.push_back(s);}
    virtual void AddWrapper() = 0;
    Sandwich ReturnProduct() {return product;} // Note that this should be decalred in concrete builders if returned products are different.
    Sandwich product;
};

// step 3: Implement Concrete SandwichBuilders
class BurgerBuilder : public SandwichBuilder {
public:
    void AddBread() {
        std::cout << "Heating up the Seasame Sprinked Bun" << std::endl;
        product.b = Bread::BurgerBun;
    }
    void AddProtein() {
        std::cout << "Grilling the Wagyu" << std::endl;
        product.p = Protein::BeefPatty;
    }
    void AddWrapper() {
        std::cout << "Wrapping with 100% recycled paper" << std::endl;
        product.w = Wrapper::Paper;
    }
};

class HotdogBuilder : public SandwichBuilder {
public:
    void AddBread() {
        std::cout << "Steaming up the buns" << std::endl;
        product.b = Bread::HotdogBun;
    }
    void AddProtein() {
        std::cout << "Boiling the hotdog in brine" << std::endl;
        product.p = Protein::Dog;
    }
    void AddWrapper() {
        std::cout << "Placing hotdog into box" << std::endl;
        product.w = Wrapper::Box;
    }
};

class BLTBuilder : public SandwichBuilder {
public:
    void AddBread() {
        std::cout << "Toasting bread in toaster" << std::endl;
        product.b = Bread::Toast;
    }
    void AddProtein() {
        std::cout << "Sizzling bacon in cast iron pan" << std::endl;
        product.p = Protein::Bacon;
    }
    void AddWrapper() {
        std::cout << "Wrapping up in a decompostable plastic wrap" << std::endl;
        product.w = Wrapper::Plastic;
    }
};

Sandwich BuildBurger() {
    BurgerBuilder builder;
    builder.AddBread();
    builder.AddProtein();
    builder.AddSide(Side::Lettuce);
    builder.AddSide(Side::Tomato);
    builder.AddSauce(Sauce::YumYum);
    builder.AddWrapper();
    return builder.ReturnProduct();
}

Sandwich BuildHotdog() {
    HotdogBuilder builder;
    builder.AddBread();
    builder.AddProtein();
    builder.AddSide(Side::Onions);
    builder.AddSauce(Sauce::Ketchup);
    builder.AddSauce(Sauce::Mustard);
    builder.AddWrapper();
    return builder.ReturnProduct();
}

Sandwich BuildBLT() {
    BLTBuilder builder;
    builder.AddBread();
    builder.AddProtein();
    builder.AddSide(Side::Lettuce);
    builder.AddSide(Side::Tomato);
    builder.AddSauce(Sauce::Mayo);
    builder.AddWrapper();
    return builder.ReturnProduct();
}

int main() {

    Sandwich burger = BuildBurger();
    Sandwich hotdog = BuildHotdog();
    Sandwich BLT = BuildBLT();
    return 0;
}


// Step 4: Create a Director Class
// Director should provide method such as: 
// CreateDineInOrder vs CreateTakeOutOrder
// where the steps used to build are different but common amongst builders
// For example dine in order doesn't need wrapper step, but the rest stays the same.
// It's shouldn't be for cases where the steps to build are different
// rather than mthods like BuildHotdog vs BuildBurger
class Director {    // 
public:
    
};



