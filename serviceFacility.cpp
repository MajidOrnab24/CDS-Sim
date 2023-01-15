#include "serviceFacility.h"

ServiceFacility::ServiceFacility(double arrivalMean, double departMean1, double departMean2,double departMean3) {
    s1 = new Counter(1);
    s2 = new Counter(2);
    s3 = new Counter(3);

    s1->createTraceFile ();
    s2->createTraceFile ();
    s3->createTraceFile2 ();

    s1->arrivalMean () = arrivalMean;
    s2->arrivalMean () = arrivalMean;
    s3->arrivalMean () = arrivalMean;

    s1->departureMean () = departMean1;
    s2->departureMean () = departMean2;
    s3->departureMean () = departMean3;

    s1->setNext(s2);
    s2->setNext(s1);

    s1->extraService(s3);
    s2->extraService(s3);

     s3->prevService(s1);

    s1->initialize ();
    s2->initialize ();
    s3->initialize ();

    s1->startArrival();
}

void ServiceFacility::generateReport() {
    s1->report();
    s2->report();
    s3->report2();
}
