#ifndef MSQS_2_SERVERS_SCENARIO_1_SERVICEFACILITY_H
#define MSQS_2_SERVERS_SCENARIO_1_SERVICEFACILITY_H
#include "counter.h"

class ServiceFacility {
private:
    Counter* s1;
    Counter* s2;
    Counter* s3;
public:
    ServiceFacility(double arrivalMean, double departMean1, double departMean2,double departMean3);
    void generateReport();
};


#endif
