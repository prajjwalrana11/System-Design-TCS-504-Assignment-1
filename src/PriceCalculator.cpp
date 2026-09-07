#include <vector>
using namespace std;

// SOLID: Single Responsibility Principle - calculates prices only.
class PriceCalculator{
public:
    // Compile-time polymorphism: no overloads or templates are used here.
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0.0;

        for(ShowSeat* s : seats){
            total += priceForSeatType(s->getSeat()->getType()); 
        }
        return total;
    }
};