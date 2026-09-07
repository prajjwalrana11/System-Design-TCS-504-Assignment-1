#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#include "Movie.cpp"
#include "Seat.cpp"
#include "ShowSeat.cpp"     // needs Seat
#include "Screen.cpp"       // needs Seat
#include "Show.cpp"         // needs Movie, Screen, ShowSeat
#include "Cinema.cpp"       // needs Screen
#include "Customer.cpp"
#include "Booking.cpp"      // needs Show, ShowSeat, Customer
#include "Payment.cpp"
#include "PaymentTypes.cpp" // needs Payment
#include "PriceCalculator.cpp" // needs ShowSeat, Seat
#include "TicketPrinter.cpp"   // needs Booking
#include "BookingService.cpp"  // needs Cinema, PriceCalculator, TicketPrinter, Booking, Payment


vector<string> splitSeatNumbers(const string& raw) {
    // Compile-time polymorphism: no function overloading is used in this project.
    vector<string> result;
    stringstream ss(raw);
    string token;
    while (getline(ss, token, ',')) {
        // trim spaces
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start != string::npos) {
            result.push_back(token.substr(start, end - start + 1));
        }
    }
    return result;
}

int readMenuChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Invalid input, enter a number: ";
    }
    return choice;
}

// ---- demo data setup ----

Cinema* buildDemoCinema() {
    Cinema* cinema = new Cinema("PVR");

    Screen* screen1 = new Screen(1);
    screen1->addSeat("A1", SeatType::SILVER);
    screen1->addSeat("A2", SeatType::SILVER);
    screen1->addSeat("A3", SeatType::SILVER);
    screen1->addSeat("A4", SeatType::SILVER);
    screen1->addSeat("B1", SeatType::GOLD);
    screen1->addSeat("B2", SeatType::GOLD);
    screen1->addSeat("B3", SeatType::GOLD);
    screen1->addSeat("C1", SeatType::PLATINUM);
    screen1->addSeat("C2", SeatType::PLATINUM);

    Screen* screen2 = new Screen(2);
    screen2->addSeat("A1", SeatType::SILVER);
    screen2->addSeat("A2", SeatType::SILVER);
    screen2->addSeat("B1", SeatType::GOLD);
    screen2->addSeat("B2", SeatType::GOLD);
    screen2->addSeat("C1", SeatType::PLATINUM);

    cinema->addScreen(screen1);
    cinema->addScreen(screen2);
    return cinema;
}

void printSeatLayout(Show* show) {
    cout << "\n  SCREEN-" << show->getScreen()->getScreenNumber()
         << "  " << show->getStartTime() << "  |  " << show->getMovie()->getTitle() << "\n";

    SeatType groups[3] = { SeatType::SILVER, SeatType::GOLD, SeatType::PLATINUM };
    for (SeatType type : groups) {
        bool any = false;
        stringstream line;
        line << "  " << seatTypeToString(type);
        for (ShowSeat* ss : show->getShowSeats()) {
            if (ss->getSeat()->getType() == type) {
                any = true;
                line << " " << ss->getSeat()->getNumber()
                     << (ss->isAvailable() ? "[ ]" : "[X]");
            }
        }
        if (any) cout << line.str() << "\n";
    }
    cout << "  ( [ ] = available   [X] = booked )\n";
}

// ---- menu flows ----

void listMovies(const vector<Movie*>& movies) {
    cout << "\n";
    for (size_t i = 0; i < movies.size(); i++) {
        cout << "  [" << (i + 1) << "] " << movies[i]->getTitle()
             << "\t" << movies[i]->getLanguage()
             << "\t" << movies[i]->getDuration() << " min\n";
    }
}

void bookFlow(vector<Movie*>& movies, vector<Show*>& shows, BookingService& service, Customer& customer) {
    listMovies(movies);
    cout << "Choose movie: ";
    int mChoice = readMenuChoice();
    if (mChoice < 1 || mChoice > (int)movies.size()) {
        cout << "  Invalid movie choice.\n";
        return;
    }
    Movie* movie = movies[mChoice - 1];

    vector<Show*> movieShows;
    for (Show* s : shows) {
        if (s->getMovie() == movie) movieShows.push_back(s);
    }
    if (movieShows.empty()) {
        cout << "  No shows for this movie.\n";
        return;
    }
    for (size_t i = 0; i < movieShows.size(); i++) {
        cout << "  [" << (i + 1) << "] Screen-" << movieShows[i]->getScreen()->getScreenNumber()
             << "\t" << movieShows[i]->getStartTime() << "\n";
    }
    cout << "Choose show: ";
    int sChoice = readMenuChoice();
    if (sChoice < 1 || sChoice > (int)movieShows.size()) {
        cout << "  Invalid show choice.\n";
        return;
    }
    Show* show = movieShows[sChoice - 1];

    printSeatLayout(show);

    cin.ignore(10000, '\n');
    cout << "\nSeats (e.g. A1,B2): ";
    string rawSeats;
    getline(cin, rawSeats);
    vector<string> seatNumbers = splitSeatNumbers(rawSeats);
    if (seatNumbers.empty()) {
        cout << "  No seats entered.\n";
        return;
    }

    Booking* booking = service.bookSeats(show, &customer, seatNumbers);
    if (booking == nullptr) {
        cout << "  Booking rejected - no seats were changed.\n";
        return;
    }

    cout << "\n";
    for (ShowSeat* ss : booking->getSeats()) {
        cout << "  " << ss->getSeat()->getNumber() << " " << seatTypeToString(ss->getSeat()->getType())
             << "\tRs." << priceForSeatType(ss->getSeat()->getType()) << "\n";
    }
    cout << "  TOTAL\t\tRs." << booking->getTotalAmount() << "\n";

    // F6: pay
    cout << "\nPay by: 1.UPI  2.Card  3.Cash > ";
    int payChoice = readMenuChoice();
    Payment* payment = nullptr;
    if (payChoice == 1) {
        string upiId;
        cout << "  Enter UPI id: ";
        cin >> upiId;
        payment = new UpiPayment(upiId);
    } else if (payChoice == 2) {
        string cardNumber, expiry;
        cout << "  Enter card number: ";
        cin >> cardNumber;
        cout << "  Enter expiry (MM/YY): ";
        cin >> expiry;
        payment = new CardPayment(cardNumber, expiry);
    } else if (payChoice == 3) {
        payment = new CashPayment();
    } else {
        cout << "  Invalid payment method. Booking left PENDING (uncollected).\n";
        return;
    }

    bool paid = service.processPayment(booking, payment);
    delete payment;

    if (!paid) {
        cout << "  Payment failed - booking NOT confirmed, seats remain AVAILABLE.\n";
        return;
    }

    service.printTicket(*booking);
}

void cancelFlow(BookingService& service) {
    cout << "Enter booking id to cancel: ";
    string id;
    cin >> id;
    bool ok = service.cancelBooking(id);
    if (ok) {
        cout << "  Booking " << id << " cancelled. Seats are AVAILABLE again.\n";
    } else {
        cout << "  Could not cancel - booking not found or not CONFIRMED.\n";
    }
}

void myTicketsFlow(BookingService& service, const vector<Show*>& shows) {
    // Simple listing across all shows' known bookings via lookup is not tracked
    // per-customer in this minimal scope, so we ask for a booking id to reprint
    // instead of maintaining a separate customer->bookings index (kept out of
    // scope deliberately - see Step G "one thing we did NOT do").
    cout << "Enter booking id to view: ";
    string id;
    cin >> id;
    Booking* b = service.findBooking(id);
    if (b == nullptr) {
        cout << "  No such booking.\n";
        return;
    }
    service.printTicket(*b);
}

int main() {
    Cinema* cinema = buildDemoCinema();

    vector<Movie*> movies;
    movies.push_back(new Movie("3 Idiots", "Hindi", 170));
    movies.push_back(new Movie("Interstellar", "English", 169));

    vector<Show*> shows;
    shows.push_back(new Show(movies[0], cinema->getScreens()[0], "06:00 PM"));
    shows.push_back(new Show(movies[0], cinema->getScreens()[1], "09:00 PM"));
    shows.push_back(new Show(movies[1], cinema->getScreens()[0], "09:30 PM"));

    Customer customer("Guest", "9999999999");
    PriceCalculator calculator;
    TicketPrinter printer;
    BookingService service(cinema, &calculator, &printer);

    cout << "===== MOVIE TICKET BOOKING =====\n";
    bool running = true;
    while (running) {
        cout << "\n1. Movies  2. Book  3. Cancel  4. My tickets   0. Exit\nChoose: ";
        int choice = readMenuChoice();
        switch (choice) {
            case 1: listMovies(movies); break;
            case 2: bookFlow(movies, shows, service, customer); break;
            case 3: cancelFlow(service); break;
            case 4: myTicketsFlow(service, shows); break;
            case 0: running = false; break;
            default: cout << "  Invalid choice.\n"; break;
        }
    }

    // cleanup - reverse of ownership: BookingService owns bookings (its own
    // destructor handles that), Cinema owns screens which own seats, Show owns
    // ShowSeats. Movies and Shows are owned here in main since nothing else claims them.
    for (Show* s : shows) delete s;
    for (Movie* m : movies) delete m;
    delete cinema;

    cout << "Goodbye.\n";
    return 0;
}
