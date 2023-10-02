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
    virtual SandwichBuilder& AddBread(Bread b) = 0;
    virtual SandwichBuilder& AddProtein(Protein p) = 0;
    SandwichBuilder& AddSide(Side s) {
        product.sides.push_back(s);
        return *this;
    }
    SandwichBuilder& AddSauce(Sauce s) {
        product.sauces.push_back(s);
        return *this;
    }
    virtual SandwichBuilder& AddWrapper(Wrapper w) = 0;
    Sandwich ReturnProduct() {return product;} // Note that this should be decalred in concrete builders if returned products are different.
    Sandwich product;
};

// step 3: Implement Concrete SandwichBuilders
class BurgerBuilder : public SandwichBuilder {
public:
    SandwichBuilder& AddBread(Bread b) {
        std::cout << "Grilling bread on grill" << std::endl;
        product.b = b;
        return *this;
    }
    SandwichBuilder& AddProtein(Protein p) {
        std::cout << "Grilling protein on grill" << std::endl;
        product.p = p;
        return *this;
    }
    SandwichBuilder& AddWrapper(Wrapper w) {
        std::cout << "Wrapping burger into paper" << std::endl;
        product.w = w;
        return *this;
    }
};

class HotdogBuilder : public SandwichBuilder {
public:
    SandwichBuilder& AddBread(Bread b) {
        std::cout << "Steaming bread in steamer" << std::endl;
        product.b = b;
        return *this;
    }
    SandwichBuilder& AddProtein(Protein p) {
        std::cout << "Boiling protein in brine" << std::endl;
        product.p = p;
        return *this;
    }
    SandwichBuilder& AddWrapper(Wrapper w) {
        std::cout << "Placing hotdog into box" << std::endl;
        product.w = w;
        return *this;
    }
};

class BLTBuilder : public SandwichBuilder {
public:
    SandwichBuilder& AddBread(Bread b) {
        std::cout << "Toasting bread in toaster" << std::endl;
        product.b = b;
        return *this;
    }
    SandwichBuilder& AddProtein(Protein p) {
        std::cout << "Frying protein in pan" << std::endl;
        product.p = p;
        return *this;
    }
    SandwichBuilder& AddWrapper(Wrapper w) {
        std::cout << "Wrapping sandwich into plastic" << std::endl;
        product.w = w;
        return *this;
    }
};

Sandwich BuildBurger() {
    BurgerBuilder builder;
    builder.AddBread(Bread::BurgerBun).AddProtein(Protein::BeefPatty).AddSide(Side::Lettuce).AddSide(Side::Tomato).AddSauce(Sauce::YumYum).AddWrapper(Wrapper::Paper);
    return builder.ReturnProduct();
}

Sandwich BuildHotdog() {
    HotdogBuilder builder;
    builder.AddBread(Bread::HotdogBun).AddProtein(Protein::Dog).AddSide(Side::Onions).AddSauce(Sauce::Ketchup).AddSauce(Sauce::Mustard).AddWrapper(Wrapper::Box);
    return builder.ReturnProduct();
}

Sandwich BuildBLT() {
    BLTBuilder builder;
    builder.AddBread(Bread::Toast).AddProtein(Protein::Bacon).AddSide(Side::Lettuce).AddSide(Side::Tomato).AddSauce(Sauce::Mayo).AddWrapper(Wrapper::Plastic);
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



