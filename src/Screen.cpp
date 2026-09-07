#include <vector>
#include <string>
using namespace std;

class Screen{
private:
    // Encapsulation: screen data is private.
    int screenNumber;
    vector<Seat*> seats; // Composition: Screen owns its seats.

public:
    Screen(int screenNumber) : screenNumber(screenNumber) {}

    ~Screen(){
        for(Seat* s : seats){
            delete s;
        }
    }

    int getScreenNumber() const { return screenNumber; }

    void addSeat(string seatNumber, SeatType type){
        seats.push_back(new Seat(seatNumber, type));
    }

    const vector<Seat*>& getSeats() const { return seats; }
};