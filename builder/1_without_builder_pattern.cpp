#include <iostream>
#include <vector>

enum class Bread {Toast, HotdogBun, BurgerBun};
enum class Protein {BeefPatty, Dog, Bacon};
enum class Side{Lettuce, Tomato, Onions, Cheese};
enum class Sauce {Mayo, Ketchup, YumYum, Mustard};
enum class Wrapper {Paper, Box, Plastic};

class Sandwich {
public:
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


int main() {

    Sandwich burger(Bread::BurgerBun, Protein::BeefPatty, std::vector<Side>{Side::Lettuce,Side::Cheese,Side::Tomato}, std::vector<Sauce>{Sauce::YumYum}, Wrapper::Paper);
    Sandwich hotdog(Bread::HotdogBun, Protein::Dog, std::vector<Side>{Side::Onions}, std::vector<Sauce>{Sauce::Ketchup, Sauce::Mustard}, Wrapper::Box);
    Sandwich BLT(Bread::Toast, Protein::Bacon, std::vector<Side>{Side::Tomato, Side::Lettuce}, std::vector<Sauce>{Sauce::Mayo}, Wrapper::Plastic);

    return 0;
}

