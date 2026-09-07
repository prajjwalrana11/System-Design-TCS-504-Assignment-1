// Abstraction: defines a common payment interface.
// SOLID: Open/Closed Principle - new payment types can be added as subclasses.
// SOLID: Dependency Inversion Principle - services use Payment abstraction.
class Payment{
public:
    virtual bool pay(double amount) = 0;
    virtual ~Payment() {}
};