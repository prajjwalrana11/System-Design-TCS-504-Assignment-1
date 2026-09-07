enum class SeatStatus{
    AVAILABLE,
    BOOKED
};

class ShowSeat{
private:
    Seat* seat; // Aggregation: refers to an existing Seat.
    SeatStatus status;

public:
    ShowSeat(Seat* seat, SeatStatus status) : seat(seat), status(status) {}

    Seat* getSeat() const { return seat; }
    void setStatus(SeatStatus status) { this->status = status; }
    SeatStatus getStatus() const { return status; }

    bool isAvailable() const { return status==SeatStatus::AVAILABLE; }
};