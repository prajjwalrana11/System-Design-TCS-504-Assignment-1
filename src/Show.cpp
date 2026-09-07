#include <string>
#include <vector>
using namespace std;

class Show{
private:
    Movie* movie; // Association: show refers to a movie.
    Screen* screen; // Association: show refers to a screen.
    string startTime;
    vector<ShowSeat*> showSeats; // Composition: Show owns ShowSeats.

public:
    Show(Movie* movie, Screen* screen, string startTime){
        // this keyword: refers to the current object.
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        for(Seat* seat : screen->getSeats()){
            showSeats.push_back(new ShowSeat(seat, SeatStatus::AVAILABLE));
        }
    }
    ~Show(){
        for(ShowSeat* s : showSeats){
            delete s;
        }
    }

    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }

    const vector<ShowSeat*>& getShowSeats() const { return showSeats; }

    ShowSeat* findShowSeat(const string& seatNumber) const  {
        for(ShowSeat* s : showSeats){
            if(s->getSeat()->getNumber() == seatNumber){
                return s;
            }
        }
        return nullptr;
    }
};