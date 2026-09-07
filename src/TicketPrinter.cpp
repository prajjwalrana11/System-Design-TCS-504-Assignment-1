#include <iostream>
#include <string>
#include <vector>
using namespace std;

// SOLID: Single Responsibility Principle - prints tickets only.
class TicketPrinter{
public:
    void print(const Booking& booking) const {
        cout<<"\n=====================TICKET=====================\n";
        cout<<"Booking ID : "<<booking.getBookingId()<<"\n";
        cout<<"Movie : "<<booking.getShow()->getMovie()->getTitle()<<"\n";
        cout<<"Screen : "<<booking.getShow()->getScreen()->getScreenNumber()<<" "<<booking.getShow()->getStartTime()<<"\n";
        
        const vector<ShowSeat*>& seats = booking.getSeats();
        for(size_t i=0; i<seats.size(); i++){
            cout<<seats[i]->getSeat()->getNumber();
            if(i+1 < seats.size()){
                cout<<", ";
            }
        }
        cout<<"\n";
        cout<<"Amount : Rs. "<<booking.getTotalAmount()<<"      Status : "<<bookingStatusToString(booking.getStatus())<<"\n";
        cout<<"-----x-----x-----x-----x-----x-----x"<<"\n";
    }
};