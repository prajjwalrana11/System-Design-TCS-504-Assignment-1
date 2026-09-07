### THE PROBLEM :
    Build a small movie ticket booking system for a single cinema (like PVR or INOX), as a menu-driven C++ console program. 
    A customer should be able to see which movies are playing, pick a show, see which seats are free, book seats, pay, get a 
    ticket, and cancel a booking.

### Scope - Features that must be built
    1. List all movies currently playing
    2. For a chosen movie list it's shows (screen + start time)
    3. For a chosen show display the seat layout with AVAILABLE/BOOKED status.
    4. Book one or more seats for a show (reject an already booked seat).
    5. Price the booking by seat type: SILVER - Rs.150
                                       GOLD - Rs.250
                                       PLATINUM - Rs.400
    6. Pay by UPI, CASH or CARD -- a failed payment must NOT confirm the booking.
    7. Print a ticket : booking_id, movie, screen time, seat numbers, total amount.
    8. Cancel a Booking -- the seat becomes AVAILABLE again.

### What must be submitted
    1. [✅]Requirement analysis (FR + NFR)
    2. [✅]Noun–verb analysis table (list of classes and their methods).
    3. [✅]Relationship table with justification.
    4. [✅]Class Diagram
    5. [✅]Sequence diagram for "book a ticket and make payment".
    6. [✅]Modular working code + demo run.
    7. [✅]SOLID mapping + one thing you deliberately did NOT do.


### CLEAN CODE CHECKLIST
    - [✅] intention-revealing names — bookedSeatCount, not bsc or c1 
    - [✅] no number-series names — no list1, list2, temp1 
    - [✅] every function does ONE thing; if you need "and" to describe it, split it 
    - [✅] no function longer than ~20 lines 
    - [✅] maximum 2 levels of indentation; name your conditions (bool isSeatFree = ...; if (isSeatFree && isPaid)) 
    - [✅] 0–2 parameters preferred; 4+ means they want to become a struct/class 
    - [✅] no side effects — a function named showSeats() must not book anything 
    - [✅] constants instead of magic numbers — SILVER_PRICE, not 150 
    - [✅] no repeated code (DRY) 