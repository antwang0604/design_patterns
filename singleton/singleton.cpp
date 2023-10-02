#include <iostream>

class Singleton {
private:
    static Singleton* one_and_only_instance;
    static int unique_id;
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

Singleton* Singleton::one_and_only_instance = nullptr;
int Singleton::unique_id = 0;

int main() {
    Singleton* s1 = Singleton::get_instance(10);
    s1->PrintUniqueID();
    std::cout << "memory location: " << s1 << std::endl;
    Singleton* s2 = Singleton::get_instance(5);
    s2->PrintUniqueID();
    std::cout << "memory location: " << s2 << std::endl;
}