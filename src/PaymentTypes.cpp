#include  <iostream>
#include <string>
using namespace std;

// Inheritance: UPI payment derives from Payment.
class UpiPayment : public Payment{
private:
    string upiId;

public:
    UpiPayment(string upiId) : upiId(upiId) {}

    // Runtime polymorphism: overrides Payment::pay.
    bool pay(double amount) override {
        if(upiId.empty()){
            cout<<"Invalid UPI id.\n";
            return false;
        }
        cout<<"Charged Rs. "<<amount<<" to "<<upiId<<"...\n";
        cout<<"Payment Success? ";
        
        // Manually checking because no proper gateway implemented.
        int choice; cin>>choice;

        if(choice == 1){
            cout<<"Rs."<<amount<<" paid successfully!\n";
            return true;
        }

        cout<<"Payment Failed!\n";
        return false;
    }
};

// Inheritance: card payment derives from Payment.
class CardPayment : public Payment{
private:
    string cardNumber;
    string expiryDate;

public:
    CardPayment(string cardNumber, string expiryDate) :
        cardNumber(cardNumber), expiryDate(expiryDate) {}

    // Runtime polymorphism: overrides Payment::pay.
    bool pay(double amount) override {
        if(cardNumber.size()<12 || expiryDate.empty()){
            cout<<"Invalid card details.\n";
            return false;
        }
        cout<<"Charged Rs. "<<amount<<" to "<<cardNumber<<"...\n";
        cout<<"Payment Success? ";
        
        // Manually checking because no proper gateway implemented.
        int choice; cin>>choice;

        if(choice == 1){
            cout<<"Rs."<<amount<<" paid successfully!\n";
            return true;
        }

        cout<<"Payment Failed!\n";
        return false;
    }
};

// Inheritance: cash payment derives from Payment.
class CashPayment : public Payment{
public:
    // Runtime polymorphism: overrides Payment::pay.
    bool pay(double amount) override{
        cout<<"Rs. "<<amount<<" collected at the counter!\n";
        return true;
    }
    
};