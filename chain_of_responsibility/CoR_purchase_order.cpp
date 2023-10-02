// Declare the handler interface and describe the signature of a method for handling requests.

// Decide how the client will pass the request data into the method. The most flexible way is 
// to convert the request into an object and pass it to the handling method as an argument.

// To eliminate duplicate boilerplate code in concrete handlers, it might be worth creating an
// abstract base handler class, derived from the handler interface.
// This class should have a field for storing a reference to the next handler in the chain. 
// Consider making the class immutable. However, if you plan to modify chains at runtime, 
// you need to define a setter for altering the value of the reference field.
// You can also implement the convenient default behavior for the handling method, which is to 
// forward the request to the next object unless there’s none left. Concrete handlers will be 
// able to use this behavior by calling the parent method.


// One by one create concrete handler subclasses and implement their handling methods. Each handler should make two decisions when receiving a request:

// Whether it’ll process the request.
// Whether it’ll pass the request along the chain.
// The client may either assemble chains on its own or receive pre-built chains from other objects. In the latter case, you must implement some factory classes to build chains according to the configuration or environment settings.

// The client may trigger any handler in the chain, not just the first one. The request will be passed along the chain until some handler refuses to pass it further or until it reaches the end of the chain.

// Due to the dynamic nature of the chain, the client should be ready to handle the following scenarios:
// The chain may consist of a single link.  (if (this->next) implemented)
// Some requests may not reach the end of the chain.
// Others may reach the end of the chain unhandled.

#include <iostream>
#include <string>
#include <vector>

class PurhcaseRequest {
private:
    int amount;
    bool approved_status{false};
    std::string approved_by{""};
public:
    PurhcaseRequest(const int n) : amount{n} {} 

    int GetAmount() const {return amount;}

    void ProcessPR(const std::string approver) {
        approved_by = approver;
        approved_status = true;
    }
    void GetStatus() {
        std::cout << "---- Purchase Order Summary ----" << std::endl;
        std::cout << "Amount: " << amount << std::endl;
        std::cout << "Approved Status: " <<  approved_status << std::endl;
        std::cout << "Approver Name: " << approved_by << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }

};

// Handler represents the interface (contract) for approving purchase requests. They can be think of as Approvers.
class Handler{
public:
    virtual Handler* SetNext(Handler* next) = 0;
    virtual void Handle(PurhcaseRequest& request) = 0;
};

// Base Handlers that implements the Handler Interface. Base class for approvers.
class Employee : public Handler {
public:
    Employee() : next{nullptr} {}
    Handler* SetNext(Handler* next) override{
        this->next = next;
        return next;
    }

    void Handle(PurhcaseRequest& request) override {
        if (this->next) {
            this->next->Handle(request);
        }
    }

    void Approve(PurhcaseRequest& request) {
        request.ProcessPR(name);
    }

private:
    Handler* next;

protected:
    int approval_limit;
    std::string name;
    Employee(const std::string& name, const int& limit) : 
    name{name}, approval_limit{limit}, next{nullptr} {}
};

// Concrete Handlers
class JuniorAssociate : public Employee {
public:
    JuniorAssociate() : Employee("Junior",500) {}
    
    void Handle(PurhcaseRequest& request) override {
        std::cout << name << "[ ";
        if(request.GetAmount() <= approval_limit) {
            std::cout << "O ] "; 
            Approve(request);
        } else {
            std::cout << "X ] "; 
            Employee::Handle(request);
        }
    }
};

class SeniorAssociate : public Employee{
public:
    SeniorAssociate() : Employee("Senior", 1500) {}
    
    void Handle(PurhcaseRequest& request) override {
        std::cout << name << "[ ";
        if(request.GetAmount() <= approval_limit) {
            std::cout << "O ] "; 
            Approve(request);
        } else {
            std::cout << "X ] "; 
            Employee::Handle(request);
        }
    }
};

class Manager : public Employee {
public:
    Manager() : Employee("Manager", 3000) {}
    
    void Handle(PurhcaseRequest& request) override {
        std::cout << name << "[ ";
        if(request.GetAmount() <= approval_limit) {
            std::cout << "O ] "; 
            Approve(request);
        } else {
            std::cout << "X ] "; 
            Employee::Handle(request);
        }
    }
};

void ApprovalWorkflow(Handler* handler_ptr) {
    handler_ptr->SetNext(new SeniorAssociate())->SetNext(new Manager());

    std::vector<PurhcaseRequest> PRs{PurhcaseRequest(200),PurhcaseRequest(600),PurhcaseRequest(1600),PurhcaseRequest(5000)};

    for(auto& PR : PRs) {
        std::cout << "\n";
        std::cout << "Approval Flow: ";
        handler_ptr->Handle(PR);
        std::cout << "\n\n";
        PR.GetStatus();
    }
}

int main() {

    Handler* junior_ptr = new JuniorAssociate();
    ApprovalWorkflow(junior_ptr);

    Handler* senior_ptr = new SeniorAssociate();
    ApprovalWorkflow(senior_ptr);

    return 0;
}

