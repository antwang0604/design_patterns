#include <iostream>
#include <string>

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

class Employee {
public:
    virtual ~Employee() = default;
    Employee() = default;
    int GetLimit() {return approval_limit;}
    void Approve(PurhcaseRequest& request) {
        std::cout << "Order is approved by " << name << std::endl;
        request.ProcessPR(name);
    }
    std::string name;
    int approval_limit;
protected:
    Employee(const std::string& name, const int& limit) : 
    name{name}, approval_limit{limit} {}
};

class JuniorAssociate : public Employee{
public:
    JuniorAssociate() : Employee("Junior",500) {}
};

class SeniorAssociate : public Employee{
public:
    SeniorAssociate() : Employee("Senior", 1500) {}
};

class Manager : public Employee{
public:
    Manager() : Employee("Manager", 3000) {}
};


class ApprovalSystem {
public:
    void ProcessRequest(PurhcaseRequest& request) {
        const int request_amount = request.GetAmount();

        if(request_amount <= junior.GetLimit()) {
            junior.Approve(request);
        }
        else if (request_amount <= senior.GetLimit()) {
            senior.Approve(request);
        }
        else if (request_amount <= manager.GetLimit()) {
            manager.Approve(request);
        }
        else {
            std::cout << "order cannot be approved by anyone" << std::endl;
        }
        request.GetStatus();
    }

private:
    Manager manager;
    SeniorAssociate senior;
    JuniorAssociate junior;
};



int main() {
    PurhcaseRequest PR_200(200);
    PurhcaseRequest PR_600(600);
    PurhcaseRequest PR_1600(1600);
    PurhcaseRequest PR_5000(5000);

    ApprovalSystem sys;
    sys.ProcessRequest(PR_200);  // Should be approved by Junior
    sys.ProcessRequest(PR_600);  // Should be approved by Senior
    sys.ProcessRequest(PR_1600); // Should be approved by Manager
    sys.ProcessRequest(PR_5000); // Should be approved by No One

    return 0;
}