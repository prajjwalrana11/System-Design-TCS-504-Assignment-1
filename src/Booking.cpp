#include <vector>
#include <string>
#include <sstream>
using namespace std;

enum class BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

inline string bookingStatusToString(BookingStatus status) {
    switch (status) {
        case BookingStatus::PENDING:   return "PENDING";
        case BookingStatus::CONFIRMED: return "CONFIRMED";
        case BookingStatus::FAILED:    return "FAILED";
        case BookingStatus::CANCELLED: return "CANCELLED";
    }
    return "UNKNOWN";
}
 
class Booking {
private:
    // Encapsulation: data is private and accessed through methods.
    static int nextBookingId; // Static member: shared by all bookings.

    string bookingId;
    Show* show;             // Aggregation: borrowed, not owned.
    Customer* customer;     // Association: booking knows the customer.
    vector<ShowSeat*> seats; // Aggregation: borrowed from the Show.
    double totalAmount;
    BookingStatus status;

public:
    Booking(Show* show, Customer* customer, vector<ShowSeat*> seats, double totalAmount) {
        // this keyword: refers to the current object.
        ostringstream oss;
        oss << "BK" << (1000 + nextBookingId);
        nextBookingId++;
        this->bookingId = oss.str();

        this->show = show;
        this->customer = customer;
        this->seats = seats;
        this->totalAmount = totalAmount;
        this->status = BookingStatus::PENDING;
    }

    string getBookingId() const { return bookingId; }
    Show* getShow() const { return show; }
    Customer* getCustomer() const { return customer; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }
    void setStatus(BookingStatus status) { this->status = status; }
};

int Booking::nextBookingId = 1;
