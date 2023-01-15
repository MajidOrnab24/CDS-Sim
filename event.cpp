
#include "event.h"
#include "counter.h"
#include "scheduler.h"

void
Event :: activate (double t) {
    Scheduler &s = Scheduler :: instance ();
    stime_ = Scheduler :: now ();
    rtime_ = stime_ + t;

    s.schedule (this);  ///Adding in event list
}

void
Event :: cancel () {
    //Scheduler :: cancel (this);
}


void
ArrivalEvent :: handle () {
    counter->updateStat();
    counter->arrivalHandler ();
}

void
DepartureEvent :: handle () {
    counter->updateStat();
    counter->departureHandler ();
}



void ExtraArrivalEvent::handle(){
    counter->updateStat();
    counter->extra_arrivalHandler ();

}

void ExtraDepartureEvent::handle(){
    counter->updateStat();
    counter->extra_departureHandler ();
}
