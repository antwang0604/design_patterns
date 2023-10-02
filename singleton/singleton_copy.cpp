#include <iostream>

class Singleton {
private:
    static Singleton* one_and_only_instance = nullptr;
    static int unique_id = 0;
    Singleton(const int num){
        unique_id = num;
    }

public:
    static Singleton* get_instance(const int num) {
        if(one_and_only_instance==nullptr) {
            std::cout << "creating a new instance" << std::endl;
            one_and_only_instance = new Singleton(num);
        } 
        std::cout << "returning instance with unique id: " << unique_id << std::endl;
        return one_and_only_instance;
    }
    void operator=(const Singleton &) = delete;
    Singleton(Singleton &other) = delete;
    void PrintUniqueID() {
        std::cout << "Current Instance's unique id: " << this->unique_id << std::endl;
    }

};

// Singleton* Singleton::one_and_only_instance = nullptr;
// int Singleton::unique_id = 0;


int main() {
    Singleton* s1 = s1->get_instance(10);
    Singleton* s2 = s2->get_instance(15);
}