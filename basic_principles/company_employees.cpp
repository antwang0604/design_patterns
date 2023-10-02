// This example demonstrates the concept of 
// Programming to an interface not an implmentation
// Depend on abstraction, not concrete classes

// Bad Design
class Designer {
public:
    void DesignUI(){}
};

class Engineer {
public:
    void WriteCode(){}
};

class TPM {
public:
    void ManageProject(){}
};

class Company {
public:
    Designer d;
    Engineer e;
    TPM t;
    void CreateSoftware() {
        d.DesignUI();
        e.WriteCode();
        t.ManageProject();
    }
};

// Intermediate Design - Implement employees from interface

class Employee {
public:
    virtual void DoWork() = 0;
};

class Intermediate_Designer : public Employee {
public:
    void DoWork() override {}
};

class Intermediate_Engineer : public Employee {
public:
    void DoWork() override {}
};

class Intermediate_TPM : public Employee {
public:
    void DoWork() override {}
};

class Intermediate_Company {
public:
    Employee* employees[3] = {new Intermediate_Designer(), new Intermediate_Engineer(), new Intermediate_TPM()};
    void CreateSoftware() {
        for (Employee* employee : employees) {
            employee->DoWork();
        }
    }
};

// Advanced Example

#include <vector>

class Advanced_Company {
public:
    virtual std::vector<Employee*> CreateEmployees() = 0;
    virtual void CreateProduct() = 0;  
    int employee_size;
};

class SoftwareCompany : Advanced_Company {
public:
    SoftwareCompany() {
        employees = CreateEmployees();
    }
    std::vector<Employee*> CreateEmployees() {
        std::vector<Employee*> employees = {new Intermediate_Designer(), new Intermediate_Engineer(), new Intermediate_TPM()};
        return employees;
    }
    void CreateProduct() {
        for (Employee* employee : employees) {
            employee->DoWork();
        }
    }
    int employee_size = 3;

    std::vector<Employee*> employees;
};


int main() {
    Company c; 
    c.CreateSoftware();

    Intermediate_Company ic;
    ic.CreateSoftware();

    SoftwareCompany sc;
    sc.CreateProduct();

    return 0;
}
