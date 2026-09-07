# Functional Requirements

## **FR1** - ***Movies :***
Should dislay all the movies with title and screening time.
##
## **FR2** - ***Shows :***
The system should display all the available shows for the selected movies along with screen number and start time.
##
## **FR3** - ***Seat Layout :***
For the selected show the system should display the seat layout along with the status of every seat (AVAILABLE / BOOKED).
##
## **FR4** - ***Booking :***
A customer selects one or more seat numebers for a show. If any selected seat is already BOOKED,
whole booking is rejected and no seat changes it's state. Booking is confirmed only after payment succeeds.
##
## **FR5** - ***Calculate price :***
The total price should be calculated based on the type of the seat. SILVER:Rs.150, GOLD:Rs.250 and PLATINUM:Rs.400,
##
## **FR6** - ***Payment :***
Exactly one method (UPI/CASH/CARD) per booking. If payment fails, seats are released and booking status becomes FAILED.
##
## **FR7** - ***Ticket :***
Only after the payment is successful display a ticket containing - Booking iD, Movie name, Screen number, Show's start time,
booked seat numbers, and total amount paid for the seats.
##
## **FR8** - ***Cancel Booking :***
After a BOOKED seat is cancelled it's status should be set to AVAILABLE again. If there are multiple seats booked by the same ID
the status of all the seats should be set to AVAILABLE again.

# Non-Functional Requirements

## **NFR1** - ***Modularity :***
Each class should have its own source file. And the system has to be organized with classes and modules.
If making changes to one class should not affect other classes or methods.
##
## **NFR2** - ***Extensibility :***
Design should be such that adding any new classes does NOT require modifying any other existing classes.
For example - If we add a new payment method we shouldn't have to modify other payment classes.
##
## **NFR3** - ***Input Validation :***
If someone accidently inputs an invalid value the system should immediately reject that value.
Invalid input can be anything such that invalid show number, invalid seat number,etc.
##
## **NFR4** - ***Clean Code :***
Every variable, every funtion name should clarify what its purpose is.
NO long functions, NO Magic numbers, NO redundant code, NO inheritance should go too deep.
##