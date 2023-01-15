#include "counter.h"
#include "scheduler.h"

#include <malloc.h>
#include <iostream>
#include <fstream>
using namespace std;

int arrivalTemp=0,serviceTimeTemp=0,serverNo=0,idServer=0;
Counter ::Counter (int id): a_(this), d_(this) ,e_(this),de_(this)
{
    queue_ = new Queue ();
    serverId = id;
}

double
Counter :: exponential(double mean) {

    double r = (double)rand()/(RAND_MAX + 1.0);
    double ex = -log (r)/mean;
    return ex;
}

void
Counter :: initialize () {
    status_ = 0;
    itemArrived_ = 0;
    timeLastEvent = 0.0;

    areaQueue_ = 0.0;
    areaServer_ = 0.0;
    areaSystem_ = 0.0;

    totalQueueDelay_ = 0.0;
    totalSystemDelay_ = 0.0;
    totalCustomerServed = 0;


    //double t = exponential (arrivalMean_);
    //trace_ << "interarrival time " << t << endl;
    //a_.activate (t);
}

void Counter :: startArrival(){
    arrivalSwitch();
}

void
Counter :: createTraceFile () {
    string traceName = "trace" + to_string(serverId) + ".out";
    trace_.open (traceName, ios::out);
    if (!trace_) {
        cout << "cannot open the trace file.\n";
    }
    trace_<< "trace file for the simulation" << endl;
    trace_ << "format of the file" << endl;
    trace_ << "<event> <Extra Service Status> <time> <item id> <server status> <queue size>" << endl << endl;
}
void
Counter :: createTraceFile2 () {
    string traceName = "trace" + to_string(serverId) + ".out";
    trace2_.open (traceName, ios::out);
    if (!trace2_) {
        cout << "cannot open the trace file.\n";
    }
    trace2_<< "trace file for the simulation" << endl;
    trace2_ << "format of the file" << endl;
    trace2_ << "<event><From Server> <QueueID in Server> <Last Service Time> <time> <item id> <server status> <queue size>" << endl << endl;
}
void
Counter :: arrivalHandler () {
    Item* temp;
    itemArrived_++;
    temp = (Item*) malloc (sizeof(Item));
    temp->id_ = itemArrived_;
    temp->itemArrivalTime = Scheduler::now();
    bool e_service = (rand() % 100) < 70;
    temp->hasExtraSevice=e_service;

    if(temp->hasExtraSevice==true)
    trace_ << "a\t"<<"With Extra Service  "<< Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    else
     trace_ << "a\t"<<"No Extra Service\t  "<< Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;


    if (status () == 0) {


        status() = 1;
        if(temp->hasExtraSevice==true)
         trace_ << "s\t" <<"With Extra Service  "<< Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
        else
         trace_ << "s\t" <<"No Extra Service\t  "<< Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
        itemInService_ = temp;
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;
        double t = exponential (departureMean_);
        d_.activate (t);
    } else {
        queue_->enque(temp);
    }

    if (temp->id_ < 1000) {
        //double t = exponential (arrivalMean_);
        //trace_ << "\tinterarrival time = " << t << endl;
        //a_.activate (t);

        arrivalSwitch();
    }
}
void Counter :: extra_arrivalHandler () {

    ItemExtra* temp;
    itemArrived_++;
    temp = (ItemExtra*) malloc (sizeof(ItemExtra));
    temp->id_inServer=idServer;
    temp->fromServer=serverNo;
    temp->id_ = itemArrived_;
    temp->prevArrival=arrivalTemp;
    temp->prevServiceTime=serviceTimeTemp;
    temp->itemArrivalTime = Scheduler::now();

    trace2_ << "a\t" <<temp->fromServer<< "\t\t" <<temp->id_inServer<< "\t\t"<< Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

    if (status () == 0) {
        status() = 1;
        trace2_ << "s\t"<<temp->fromServer<< "\t\t" <<temp->id_inServer<< "\t\t" << Scheduler::now () << "\t" << temp->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
        itemInService_ = temp;
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;
        double t = exponential (departureMean_);
        de_.activate (t);
    } else {
        queue_->enque(temp);
    }

  if (temp->id_ < 1000) {
        prevServer->arrivalSwitch();
    }
}

void Counter :: departureHandler () {
    // write to the trace file
    if (queue_->length() > 0) {
        if(itemInService_->hasExtraSevice==true)
        trace_ << "d\t" <<"With Extra Service  "<< Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
       else
        trace_ << "d\t" <<"No Extra Service\t  "<< Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    }
    else {
       if(itemInService_->hasExtraSevice==true)
        trace_ << "d\t" <<"With Extra Service  "<< Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0<< "\t" << queue_->length() << endl;
       else
        trace_ << "d\t" <<"No Extra Service\t  "<< Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << endl;
    }
    //Update output statistics
    totalCustomerServed++;
    systemDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
    totalSystemDelay_ += systemDelay_;

    if (queue_->length() > 0) {
        itemInService_ = queue_->deque ();
        //Update output statistics
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;
        // write to the trace file
        if(itemInService_->hasExtraSevice==true)
         trace_ << "s\t" <<"With Extra Service  "<< Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
        else
         trace_ << "s\t" <<"No Extra Service\t  "<< Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;


        double t = exponential (departureMean_);
        //trace_ << "\tservice time = " << t << endl;
        d_.activate (t);
        arrivalTemp=itemInService_->itemArrivalTime;
        serviceTimeTemp=itemInService_->itemArrivalTime-Scheduler::now ();
        serverNo=this->serverId;
        idServer=itemInService_->id_;
        extraServiceSwitch();
    }
    else {
        status () = 0;
        itemInService_ = 0;
    }
}
void Counter :: extra_departureHandler(){
    // write to the trace file

    if (queue_->length() > 0) {
        trace2_ << "d\t"<<itemInService_->fromServer<< "\t\t" <<itemInService_->id_inServer<< "\t\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;
    } else {
        trace2_ << "d\t"<<itemInService_->fromServer<< "\t\t" <<itemInService_->id_inServer<< "\t\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << 0 << "\t" << queue_->length() << endl;
    }
    //Update output statistics
    totalCustomerServed++;
    systemDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
    totalSystemDelay_ += systemDelay_;

    if (queue_->length() > 0) {
        itemInService_ = queue_->deque ();
        //Update output statistics
        queueDelay_ = Scheduler::now() - itemInService_->itemArrivalTime;
        totalQueueDelay_ += queueDelay_;
        // write to the trace file
        trace2_ << "s\t"<<itemInService_->fromServer<< "\t\t" <<itemInService_->id_inServer<< "\t\t" << Scheduler::now () << "\t" << itemInService_->id_ << "\t" << status_ << "\t" << queue_->length() << endl;

        double t = exponential (departureMean_);
        //trace_ << "\tservice time = " << t << endl;
        de_.activate (t);
    }
    else {
        status () = 0;
        itemInService_ = 0;
    }
}

void Counter::updateStat()
{
    double durationSinceLastEvent;

    durationSinceLastEvent = Scheduler::now() - timeLastEvent;
    timeLastEvent = Scheduler::now();

    areaQueue() += durationSinceLastEvent*(queue_->length());
    areaServer() += durationSinceLastEvent*status();
    areaSystem() += durationSinceLastEvent*(queue_->length() + status());

}

void Counter::report()
{
    ofstream report_;
    string reportName = "report" + to_string(serverId) +".out";
    report_.open (reportName, ios::out);
    if (!report_) {
        cout << "cannot open the report file.\n";
    }
    report_<< "Report of the simulation" << endl;
    report_<<"Traffic Intensity: "<<arrivalMean()/departureMean()<<endl;
    report_<<"Average Number of Customers in the Queue : "<<(areaQueue()/(Scheduler::now()))<<endl;
    report_<<"Average Server Utilization: "<<(areaServer()/(Scheduler::now()))<<endl;
    report_<<"Average Number of Customers in the System: "<<(areaSystem()/(Scheduler::now()))<<endl;
    report_<<"Average Queueing Delay: "<<(totalQueueDelay()/totalCustomerServed)<<endl;
    report_<<"Average System Delay: "<<(totalSystemDelay()/totalCustomerServed)<<endl;
}
void Counter::report2()
{
    ofstream report2_;
    string reportName = "report" + to_string(serverId) +".out";
    report2_.open (reportName, ios::out);
    if (!report2_) {
        cout << "cannot open the report file.\n";
    }
    report2_<< "Report of the simulation" << endl;
    report2_<<"Traffic Intensity: "<<arrivalMean()/departureMean()<<endl;
    report2_<<"Average Number of Customers in the Queue : "<<(areaQueue()/(Scheduler::now()))<<endl;
    report2_<<"Average Number of Customers in the System: "<<(areaSystem()/(Scheduler::now()))<<endl;
    report2_<<"Average Queueing Delay: "<<(totalQueueDelay()/totalCustomerServed)<<endl;
    report2_<<"Average System Delay: "<<(totalSystemDelay()/totalCustomerServed)<<endl;
}

void Counter::getArrival() {
    double t = Counter::exponential(arrivalMean_);
    a_.activate(t);
}
void Counter::getExtraArrival() {
    double t = Counter::exponential(arrivalMean_);
    e_.activate(t);
}
void Counter::extraServiceSwitch(){
    extraServer->getExtraArrival();
 }
void Counter::arrivalSwitch() {
    if(queueSize() <= nextServer->queueSize()){
        getArrival();
    }
    else{
        nextServer->getArrival();
    }
}

void Counter::setNext(Counter *s) {
    nextServer = s;
}
void Counter::extraService(Counter *s) {
    extraServer = s;
}
void Counter::prevService(Counter *s) {
    prevServer = s;
}
