#include <vector>
#include <string>
using namespace std;

enum class SeatType { SILVER, GOLD, PLATINUM };

inline double priceForSeatType(SeatType type){
    switch(type){
        case SeatType::SILVER : return 150.0;
        case SeatType::GOLD : return 250.0;
        case SeatType::PLATINUM : return 400.0;
    }
    return 0.0;
}

inline string seatTypeToString(SeatType type){
    switch(type){
        case SeatType::SILVER : return "SILVER";
        case SeatType::GOLD : return "GOLD";
        case SeatType::PLATINUM : return "PLATINUM";
    }
    return "UNKNOWM";
}

class Seat{
private:
    string seatNumber;
    SeatType type;

public:
    Seat(string seatNumber, SeatType type) :
        seatNumber(seatNumber),type(type) {}

    string getNumber() const { return seatNumber; }
    SeatType getType() const { return type; }
};