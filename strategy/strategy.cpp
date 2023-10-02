/**
 * strategy interface
 *  - has execute method
 * context
 *  - has a strategy interface instance (unique ptr)
 *  - has a setStrategy method for client
 *  - has some business logic to execute strategy
 * 
 * concrete strategy
 *  - overrides execute method
*/
#include <memory>
#include <iostream>

class StrategyInterface {
public:
    virtual ~StrategyInterface() = default;
    virtual void execute() const = 0;
};

class ConcreteStrategyA : public StrategyInterface {
public:
    void execute() const override{
        std::cout << "Strat A Override" << std::endl;
    }
};

class ConcreteStrategyB : public StrategyInterface {
public:
    void execute() const override{
        std::cout << "Strat B Override" << std::endl;
    }
};


class Context {
private:
    std::unique_ptr<StrategyInterface> strategy_;
public:
    Context() = default;
    void SetStrategy(std::unique_ptr<StrategyInterface>& strategy) {
        strategy_ = std::move(strategy);
    }
    void DoBusinessLogic(){
        strategy_->execute();
    }
};

int main() {
    Context c;
    std::unique_ptr<StrategyInterface> strategy = std::make_unique<ConcreteStrategyA>();
    c.SetStrategy(strategy);
    c.DoBusinessLogic();

    strategy = std::make_unique<ConcreteStrategyB>();
    c.SetStrategy(strategy);
    c.DoBusinessLogic();

    return 0;
}