# Relationships

| Pair | Choice | Justification |
|------|--------:|---------------|
| `Cinema - Screen` |Composition|`Cinema` owns `Screen` without the cinema, screens cannot exist independently|
| `Screen - Seat` |Composition|`Seat` and `Screen` cannot exist independently because Screen owns Seat if a Screen is removed Seat is also rmoved|
| `Show - Movie` |Aggregation| Show stores `Movie*`, never deletes it — cancel a show, the movie still plays elsewhere. |
| `Show - Screen` |Aggregation| Show stores `Screen*`, never deletes it — screen keeps hosting other shows. |
| `Show - ShowSeat` |Composition|`ShowSeat` belongs to a `Show`, if a show is cancelled the seats owned by it are also cancelled. The seats cannot exist independently because they are particular to that specific show.|
| `Booking - Customer` |Association|Neither one owns other. A `Customer` can make many bookings and a `Booking` refers to a Customer|
| `Booking - ShowSeat` |Aggregation| Booking stores `vector<ShowSeat*>` borrowed from the Show; cancelling a booking flips their status back, it doesn't destroy them. |
| `Booking - Payment` |Dependency|`Booking` doesn't store or own a `Payment`, everything is handelled through BookingService|
| `Payment - UpiPayment` |Inheritance|Because `UpiPayment` is a type of `Payment` it inherits and overrides the pay() method|
| `BookingService - Booking` |Dependency|`BookingService` uses `Booking` objects temporarily during booking process but doesn't maintain persistent references|6