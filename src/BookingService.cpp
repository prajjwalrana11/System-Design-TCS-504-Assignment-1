#include <vector>
#include <string>
#include <iostream>
using namespace std;

class BookingService {
private:
    // SOLID: Single Responsibility Principle - handles booking operations.
    Cinema* cinema;                 // Association: does not own the cinema.
    PriceCalculator* calculator;    // Association: uses the calculator.
    TicketPrinter* printer;         // Association: uses the printer.
    vector<Booking*> bookings;      // Composition: owns its bookings.

public:
    BookingService(Cinema* cinema, PriceCalculator* calculator, TicketPrinter* printer) {
        // this keyword: refers to the current object.
        this->cinema = cinema;
        this->calculator = calculator;
        this->printer = printer;
    }

    ~BookingService() {
        for (Booking* b : bookings) {
            delete b;
        }
    }

    Cinema* getCinema() const { return cinema; }

    Booking* bookSeats(Show* show, Customer* customer, const vector<string>& seatNumbers) {
        vector<ShowSeat*> selected;

        for (const string& num : seatNumbers) {
            ShowSeat* ss = show->findShowSeat(num);
            if (ss == nullptr) {
                cout << "  Seat " << num << " does not exist on this show.\n";
                return nullptr;
            }
            if (!ss->isAvailable()) {
                cout << "  Seat " << num << " is already BOOKED.\n";
                return nullptr;
            }
            selected.push_back(ss);
        }

        double amount = calculator->calculate(selected);
        Booking* booking = new Booking(show, customer, selected, amount);
        bookings.push_back(booking);
        return booking;
    }

    bool processPayment(Booking* booking, Payment* payment) {
        if (booking == nullptr || booking->getStatus() != BookingStatus::PENDING) {
            return false;
        }

        // Runtime polymorphism: calls the selected Payment subclass.
        bool success = payment->pay(booking->getTotalAmount());

        if (success) {
            for (ShowSeat* ss : booking->getSeats()) {
                ss->setStatus(SeatStatus::BOOKED);
            }
            booking->setStatus(BookingStatus::CONFIRMED);
            return true;
        } else {
            booking->setStatus(BookingStatus::FAILED);
            return false;
        }
    }

    bool cancelBooking(const string& bookingId) {
        Booking* booking = findBooking(bookingId);
        if (booking == nullptr || booking->getStatus() != BookingStatus::CONFIRMED) {
            return false;
        }
        for (ShowSeat* ss : booking->getSeats()) {
            ss->setStatus(SeatStatus::AVAILABLE);
        }
        booking->setStatus(BookingStatus::CANCELLED);
        return true;
    }

    Booking* findBooking(const string& bookingId) const {
        for (Booking* b : bookings) {
            if (b->getBookingId() == bookingId) {
                return b;
            }
        }
        return nullptr;
    }

    void printTicket(const Booking& booking) const {
        printer->print(booking);
    }
};
