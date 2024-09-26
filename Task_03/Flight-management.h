#ifndef DEF_FM
#define DEF_FM

struct plane createFlight(int* flightNumIncremented);
struct planeNode* addFlight(struct planeNode* headRef, struct plane newFlight);
int listAllFlights(struct planeNode* headRef, bool showSeatCapacity);
void createReservation(struct plane* selectedFlight, int count);
struct plane* getFlightFromList(struct planeNode* headRef, int numOfFlights);
void setNewDepartureTime(struct plane* flight);
void listAllDelayedFlights(struct planeNode* headRef);
struct planeNode* deleteFlight(struct planeNode* flightHead, struct planeNode* flightToBeDeleted);
struct planeNode* getFlightNodeFromList(struct planeNode* headRef, int numOfFlights);
int listAllReservations(struct reservationNode* headRef);
struct reservationNode* getReservationFromList(struct reservationNode* headRef, int numOfSeats);
struct reservationNode* deleteReservation(struct reservationNode* reservationHead, struct reservationNode* reservationToBeDeleted);
void bubbleSort(struct reservationNode* head, int count);
void printFlightFromListByDestination(struct planeNode* headRef);
void printFlightFromListByPassenger(struct planeNode* headRef);
void cleanupFlightManagement(struct planeNode* flightHead);

#endif