# Noun–Verb Analysis

| Noun Found | Keep as a Class? | Reason |
|---|---|---|
| Movie | Yes | A movie has its own information, such as its title, language, and duration. |
| Cinema | Yes | It represents the theatre and keeps track of its screens. |
| Customer | Yes | A customer has their own details, such as name and phone number. |
| Show | Yes | A show represents a particular movie being played on a specific screen at a specific time. |
| Seat | Yes | Each seat is a physical seat with its own number and type. |
| Screen | Yes | A screen represents an auditorium and contains its physical seats. |
| ShowSeat | Yes | It keeps track of whether a particular seat is available or booked for a specific show. |
| Booking | Yes | A booking keeps all the information related to a customer's reservation. |
| Payment | Yes | Payment needs to support different methods such as UPI, Card, and Cash. |
| Ticket | No | We only need to print the ticket details, so a separate Ticket class is not necessary. |
| Seat Layout | No | The seat layout is just a way of displaying the seats of a show, not a separate object. |
| Seat Type | No | It only represents a fixed set of options, so an enum is enough. |
| Start Time | No | It is simply information about a show, so it can be stored inside the Show class. |
| Screen Number | No | It is just a property of a screen and does not need its own class. |
| Booking ID | No | It is used to identify a booking, so it can be stored as part of the Booking class. |
| Total Amount | No | It is calculated for a booking and can be stored as part of the Booking class. |


# Core Entity Classes

| Class | Data members | Methods | Access modifiers | Knows | Does | Must NOT do |
|-------|--------------|---------|------------------|-------|------|-------------|
|`Movie` |`string title`<br>`string language`<br>`float duration`|`getTitle()`<br>`getLanguage()`<br>`getDuration()`|Data: `private`<br>Methods: `public`|Title, Language, Duration|Stores information about the movie|Manage seats, bookings, payments|
| `Seat` | `int seatNumber`<br>`SeatType Type` | `getNumber()`<br>`getType()` | Data: `private`<br>Methods: `public` |Seat number, type|Representaion of a physical seat|Booking|
| `Screen` | `int screenNumber`<br>`vector<Seat> seats` | `getScreenNumber()`<br>`getSeat()`<br>`addSeat()` |Data: `private`<br>Methods: `public`|Screen number, seats|Manages physical seats|Track booking status for the show, payments|
|`Cinema`|`string name`<br>`vector<Screen> screens`|`getName()`<br>`getScreens()`<br>`addScreens()`|Data: `private`<br>Methods: `public`|Cinema name and screens|Manages screens|Handle payments or bookings|
|`Show`|`Movie* movie`<br>`Screen* screen`<br>`string startTime`<br>`vector<ShowSeats> showSeats`|`getMovie()`<br>`getStartTime()`<br>`getShowSeats()`<br>`getScreen()`|Data: `private`<br>Methods: `public`|Movie,Screen,Start time,Seats(show specific)|Shows one screening|Manage payments, bookings|
|`ShowSeat`|`Seat* seat`<br>`SeatStatus status`|`getSeat()`<br>`setStatus()`<br>`getStatus()`|Data: `private`<br>Methods: `public`|Seat and it's status (show specific)|Trackes the status of a seat (available/booked)|Booking and payments|
|`Customer`|`string name`<br>`string phone`|`getName()`<br>`getPhone()`|Data: `private`<br>Methods: `public`|Customer's name, phone number|Stores customer information|Manage bookings and payments|
|`Booking`|`Customer* customer`<br>`string bookingId`<br>`Show* show`<br>`vector<ShowSeats*> seats`<br>`double totalAmount`<br>`BookingStatus status`|`getBookingId()`<br>`getShow()`<br>`getSeats()`<br>`getTotalAmount()`<br>`getStatus()`<br>`setStatus()`|Data: `private`<br>Methods: `public`|Booking details|Sotres data about a customer's booking|Print ticket, payment processing|


## Behaviour / Service Classes

| Class | Data Members | Methods | Access Specifiers | Knows | Does | Must NOT Do |
|-------|--------------|---------|-------------------|-------|------|-------------|
| `Payment` | None | `virtual bool pay(double amount) = 0`<br>`virtual ~Payment()` | Methods: `public` | The basic payment structure | Provides the common payment interface | Handle a specific type of payment |
| `UpiPayment` |`string upiId` | `bool pay(double amount) override` | Data: `private`<br>Methods: `public` | Information needed for UPI payment | Handles payments made through UPI | Handle card or cash payments or manage bookings |
| `CardPayment` |`string cardNumber`<br>`string expiryDate` | `bool pay(double amount) override` |Data: `private`<br>Methods: `public` | Information needed for card payment | Handles payments made through cards | Handle UPI or cash payments or manage bookings |
| `CashPayment` | None | `bool pay(double amount) override` |Methods: `public` | Information needed for cash payment | Handles cash payments | Handle UPI or card payments or manage bookings |
| `PriceCalculator` | None | `double calculate(vector<Seat>)` | Methods: `public` | The prices of different seat types | Calculates the total price for the selected seats | Handle payments or change booking details |
| `TicketPrinter` | None | `void print(const Booking&)` | Methods: `public` | The information needed for a ticket | Formats and prints the ticket | Create bookings, handle payments, or calculate prices |
| `BookingService` |`Cinema* cinema`<br>`PriceCalculator* calculator` | `bool bookSeats()`<br>`bool cancelBooking()`<br>`bool processPayment()` | Data: `private`<br>Methods: `public` | The different parts needed to complete a booking | Coordinates the booking process from seat selection to payment and confirmation | Calculate prices, implement payment methods, or format tickets |
| `Menu` | `Cinema* cinema`<br>`BookingService* bookingService` | `void displayMenu()`<br>`int readInput()`<br>`void run()` | Data: `private`<br>Methods: `public` | The available menu options and user input | Shows the menu and takes input from the user | Handle the actual booking logic or business rules |