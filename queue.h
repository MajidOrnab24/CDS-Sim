#ifndef MSQS_2_SERVERS_SCENARIO_1_QUEUE_H
#define MSQS_2_SERVERS_SCENARIO_1_QUEUE_H


typedef struct ItemType
{
    int id_;
    double itemArrivalTime;
    bool hasExtraSevice;
    int prevArrival=0,prevServiceTime=0;
    int fromServer=0,id_inServer=0;
    ItemType *next_;
} Item,ItemExtra; // used for storing event info


class Queue
{
public:
    Queue ();
    inline int& length ()
    {
        return (length_);
    }
    void enque (Item *im);
    Item* deque ();

private:
    int length_;
    Item *head_;
    Item *tail_;
};


#endif //MSQS_2_SERVERS_SCENARIO_1_QUEUE_H
