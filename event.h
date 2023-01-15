#ifndef MSQS_2_SERVERS_SCENARIO_1_EVENT_H
#define MSQS_2_SERVERS_SCENARIO_1_EVENT_H

class Counter;

class Event
{
public:
    Event (Counter* s) : counter (s)
    {
        stime_ = 0.0;
        rtime_ = 0.0;
    }

    inline int& eventType ()
    {
        return (eventType_);
    }
    inline double& expire ()
    {
        return (rtime_);
    }
    inline double& start ()
    {
        return (stime_);
    }

    void activate (double t);
    void cancel ();
    virtual void handle () = 0;

    Event* next_;
protected:
    Counter* counter;

private:
    int eventType_;	// represented by event id
    double stime_;
    double rtime_;
    int status_;
};

class ArrivalEvent : public Event
{
public:
    ArrivalEvent (Counter* s) : Event(s) {}
    void handle ();
};

class DepartureEvent : public Event
{
public:
    DepartureEvent (Counter* s) : Event(s) {}
    void handle ();
};

class ExtraArrivalEvent : public Event
{
public:
    ExtraArrivalEvent (Counter* s) : Event(s) {}
    void handle ();
};

class ExtraDepartureEvent : public Event
{
public:
    ExtraDepartureEvent (Counter* s) : Event(s) {}
    void handle ();
};

#endif //MSQS_2_SERVERS_SCENARIO_1_EVENT_H
