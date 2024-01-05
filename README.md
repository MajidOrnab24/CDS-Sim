# Central Departmental Store (CDS) Simulation Documentation

## 1. Introduction

The Central Departmental Store (CDS) simulation is a discrete-event simulation designed to model the operation of a departmental store with multiple service counters. The simulation tracks the arrival, service, and departure of customers at different counters, generating detailed trace files and reports.

## 2. Classes

### 2.1. `Scheduler` Class

#### 2.1.1. Description

The `Scheduler` class is responsible for managing the scheduling and execution of events in the simulation.

#### 2.1.2. Member Functions

- **Constructor:** Initializes the `eventList_` to null.
- **now():** Returns the current simulation time.
- **instance():** Returns a reference to the singleton instance of the `Scheduler` class.
- **schedule(Event* e):** Schedules an event for future execution.
- **updateClock(double t):** Updates the simulation clock to the specified time.
- **initialize():** Initializes the simulation clock.
- **addEvent(Event *e):** Adds an event to the event list in chronological order.
- **removeEvent():** Removes and returns the next event from the event list.
- **cancel(Event *e):** Cancels a scheduled event.
- **trigger():** Executes the next scheduled event.
- **run():** Executes events until the event list is empty.

### 2.2. `Counter` Class

#### 2.2.1. Description

The `Counter` class represents a service counter in the departmental store. Each counter serves customers, manages queues, and records statistics.

#### 2.2.2. Member Functions

- **Constructor:** Initializes the counter with a unique ID and creates a queue.
- **exponential(double mean):** Generates a random number from an exponential distribution.
- **initialize():** Initializes various counter-related variables.
- **startArrival():** Initiates the arrival process.
- **createTraceFile():** Creates a trace file for simulation output.
- **arrivalHandler():** Handles the arrival of a customer.
- **extra_arrivalHandler():** Handles the arrival of a customer with extra service.
- **departureHandler():** Handles the departure of a customer.
- **extra_departureHandler():** Handles the departure of a customer with extra service.
- **updateStat():** Updates statistics based on elapsed time.
- **report():** Generates and writes a report based on simulation results.
- **getArrival():** Activates the arrival event for regular customers.
- **getExtraArrival():** Activates the arrival event for customers with extra service.
- **extraServiceSwitch():** Initiates the arrival of a customer with extra service at another counter.
- **arrivalSwitch():** Decides whether to activate the arrival event for the current or next counter.
- **setNext(Counter* s):** Sets the next counter in the sequence.
- **extraService(Counter* s):** Sets the counter for extra service.
- **prevService(Counter* s):** Sets the counter for previous service.

### 2.3. `Event` Class

#### 2.3.1. Description

The `Event` class represents an event in the simulation, such as arrival, departure, or extra service.

#### 2.3.2. Member Functions

- **Constructor:** Initializes an event with a specified expiration time and type.
- **expire():** Returns the expiration time of the event.
- **eventType():** Returns the type of the event.
- **handle():** Executes the event-specific handling logic.

### 2.4. `Queue` Class

#### 2.4.1. Description

The `Queue` class represents a simple first-in-first-out (FIFO) queue for managing customers at each service counter.

#### 2.4.2. Member Functions

- **Constructor:** Initializes an empty queue.
- **enque(Item* item):** Adds an item to the back of the queue.
- **deque():** Removes and returns the front item from the queue.
- **length():** Returns the current size of the queue.

### 2.5. `ServiceFacility` Class

#### 2.5.1. Description

The `ServiceFacility` class initializes and manages multiple counters in the departmental store.

#### 2.5.2. Member Functions

- **Constructor:** Initializes three counters (`s1`, `s2`, and `s3`) with different departure means and interconnects them.
- **generateReport():** Generates reports for each counter using the `generateReport()` function.

## 3. Simulation Workflow

1. **Initialization:**
   - Create an instance of `ServiceFacility`.
   - Initialize the simulation clock.

2. **Event Scheduling:**
   - Events such as arrivals, departures, and extra services are scheduled using the `Scheduler` class.

3. **Event Execution:**
   - The `Scheduler` triggers events in chronological order.
   - Events are handled by the respective counter classes.

4. **Statistics Update:**
   - Counters update statistics during event handling.

5. **Report Generation:**
   - After simulation completion, generate reports for each counter using the `generateReport()` function in `ServiceFacility`.

## 4. Running the Simulation

- To run the simulation, create an instance of the `ServiceFacility` class with appropriate parameters.
- Execute the `run()` function of the `Scheduler` to start the simulation.

## 5. Output

- Trace files and reports are generated for each counter, providing detailed information about the simulation.

## 6. Conclusion

The Central Departmental Store simulation provides insights into the efficiency and performance of a departmental store with multiple service counters. By analyzing generated reports, users can optimize counter configurations for improved customer service.
