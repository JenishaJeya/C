#include <stdbool.h>
#include <stdlib.h>
#include "definition.h"
#include "Flight-management.h"
#include <string.h>
#include <stdio.h>

struct plane createFlight(int* flightNumIncremented) {
    struct plane newFlight;

    printf("Enter flight destination: ");
    scanf("%s", newFlight.destination);

    char firstTwoCharsDestination[2];
    memcpy(firstTwoCharsDestination, newFlight.destination , 2);
    snprintf(newFlight.flightId, 5, "%s-%d", firstTwoCharsDestination, *flightNumIncremented);
    ++*flightNumIncremented;

    printf("Enter number of seats: ");
    scanf("%d", &(newFlight.seats));

    printf("Enter departure time (Unix Timestamp): ");
    scanf("%d", &(newFlight.departureTime));
    printf("Flight created %s.\n\n", newFlight.flightId);

    newFlight.delayed = false;
    newFlight.reservationHead = NULL;
    return newFlight;
}

void setNewDepartureTime(struct plane* flight) {
    printf("Enter a new departure time (Unix Timestamp): ");
    scanf("%d", &(flight->departureTime));
    flight->delayed = true;
    printf("Departure time updated.\n\n");
}

struct planeNode* addFlight(struct planeNode* headRef, struct plane newFlight) {
    // Create new flight
    struct planeNode* newFlightNode = (struct planeNode*) malloc(sizeof(struct planeNode));

    // Add the new flight to node data
    newFlightNode->data = newFlight;
 
    // Select next of new node as the previous head and previous of new node as NULL
    newFlightNode->next = headRef;
    newFlightNode->previous = NULL;
 
    // Change previous of old head node to new node
    if (headRef != NULL)
        headRef->previous = newFlightNode;
 
    // Change the head flight to point to the new flight
    headRef = newFlightNode;
    return headRef;
}

int numberOfReservations(struct reservationNode* headRef) {
    int count = 0;
    struct reservationNode* tempRef = headRef;

    while (tempRef != NULL) {
        count++;
        tempRef = tempRef->next;
    }
    return count;
}

int listAllFlights(struct planeNode* headRef, bool showCapacity) {
    int count = 0;
    struct planeNode* tempRef = headRef;

    printf("\nStart of flight list.\n\n");
    while (tempRef != NULL) {
        count++;
        if(showCapacity) {
            int reservations = numberOfReservations(tempRef->data.reservationHead);
            float percetange = (float)reservations / tempRef->data.seats * 100.0;
            printf("%d: Flight: %s. Destination: %s. Seats: %d. Coverage: %f %% \n", count, tempRef->data.flightId, tempRef->data.destination, tempRef->data.seats, percetange);
        } else {
            printf("%d: Flight: %s. Destination: %s. Seats: %d. \n", count, tempRef->data.flightId, tempRef->data.destination, tempRef->data.seats);
        }
        tempRef = tempRef->next;
    }
    printf("\nEnd of flight list.\n\n");
    return count;
}

void listAllDelayedFlights(struct planeNode* headRef) {
    int count = 0;
    struct planeNode* tempRef = headRef;

    printf("\nStart of delayed flight list.\n\n");
    while (tempRef != NULL) {
        if(tempRef->data.delayed == 1){
            count++;
            printf("%d: Flight ID: %s. Destination: %s. New time: %d \n", count, tempRef->data.flightId, tempRef->data.destination, tempRef->data.departureTime);
        }
        tempRef = tempRef->next;
    }
    printf("\nEnd of delayed flight list.\n\n");
    printf("\nTotal number of delayed flights %d. \n\n", count);
}

struct plane* getFlightFromList(struct planeNode* headRef, int numOfFlights) {
    int flightNumSelected = 0;
    do {
        printf("Select a flight by its number in the list: ");
        scanf("%d", &flightNumSelected);
    } while (flightNumSelected < 0 || flightNumSelected > numOfFlights);

    int count = 1;
    struct planeNode* tempRef = headRef;

    if(flightNumSelected == count) {
        return &headRef->data;
    }

    while (flightNumSelected != count) {
        tempRef = tempRef->next;
        count++;
    }

    return &tempRef->data;
}

void printFlightFromListByDestination(struct planeNode* headRef) {
    int count = 0;
    char destination[50];
    printf("Search flights by chosen destination: ");
    scanf("%s", destination);

    struct planeNode* tempRef = headRef;

    while (tempRef != NULL) {
        if(strcmp(destination,tempRef->data.destination) == 0) {
            count++;
            printf("%d: Flight ID: %s. Destination: %s.\n", count, tempRef->data.flightId, tempRef->data.destination);
        }
        tempRef = tempRef->next;
    }

    if(count == 0) {
        printf("No flights for destination found.\n\n");
    } else {
        printf("Total of %d flights found for destination: %s.\n\n", count, destination);
    }
}

void printFlightFromListByPassenger(struct planeNode* headRef) {
    int count = 0;
    char name[50];
    printf("Search flights by chosen passenger name: ");
    scanf("%s", name);

    struct planeNode* tempRef = headRef;

    while (tempRef != NULL) {
        struct reservationNode* tempRes = tempRef->data.reservationHead;
        while(tempRes != NULL) {
            if(strcmp(name,tempRes->data.name) == 0) {
                count++;
                printf("%d: Flight ID: %s. Destination: %s. Passenger: %s\n", count, tempRef->data.flightId, tempRef->data.destination, tempRes->data.name);
            }
            tempRes = tempRes->next;
        }
        tempRef = tempRef->next;
    }

    if(count == 0) {
        printf("No flights for passenger found.\n\n");
    } else {
        printf("Total of %d flights found for passenger: %s.\n\n", count, name);
    }
}


struct planeNode* getFlightNodeFromList(struct planeNode* headRef, int numOfFlights) {
    int flightNumSelected = 0;
    do {
        printf("Select a flight by its number in the list: ");
        scanf("%d", &flightNumSelected);
    } while (flightNumSelected < 0 || flightNumSelected > numOfFlights);

    int count = 1;
    struct planeNode* tempRef = headRef;

    if(flightNumSelected == count) {
        return headRef;
    }

    while (flightNumSelected != count) {
        tempRef = tempRef->next;
        count++;
    }

    return tempRef;
}

struct planeNode* deleteFlight(struct planeNode* flightHead, struct planeNode* flightToBeDeleted) 
{ 
    if (flightHead == NULL || flightToBeDeleted == NULL) 
        return flightHead; 
  
    // If the node we are deleted is the head node, we need to set the next 
    // node in the list as head
    if (flightHead == flightToBeDeleted) 
        flightHead = flightToBeDeleted->next; 
  
    // If it is not the last node, update the next nodes previous
    if (flightToBeDeleted->next != NULL) 
        flightToBeDeleted->next->previous = flightToBeDeleted->previous; 

    // If it is not the head node, update the previous nodes next
    if (flightToBeDeleted->previous != NULL) 
        flightToBeDeleted->previous->next = flightToBeDeleted->next; 
  
    // Free up memory
    printf("Deleting flight %s \n", flightToBeDeleted->data.flightId);

    struct reservationNode* tmp;
    while (flightToBeDeleted->data.reservationHead != NULL)
    {
        tmp = flightToBeDeleted->data.reservationHead;
        flightToBeDeleted->data.reservationHead = flightToBeDeleted->data.reservationHead->next;
        free(tmp);
    }

    free(flightToBeDeleted); 
    printf("Done\n\n");

    return flightHead; 
}

int findNextAvailableSeat(struct reservationNode* headRef) {
    int seat = 1;
    struct reservationNode* tempRef = headRef;

    while (tempRef != NULL) {
        seat++;
        tempRef = tempRef->next;
    }
    return seat;
}

void createReservation(struct plane* selectedFlight, int count) {
    printf("Flight ID: %s with destination: %s selected. \n", selectedFlight->flightId, selectedFlight->destination);

    int seatNumber = findNextAvailableSeat(selectedFlight->reservationHead);
    if(seatNumber > selectedFlight->seats) {
        printf("Flight is fully booked\n\n");
        return;
    }

    struct reservation newReservation;
    newReservation.seatNumber = seatNumber;
    printf("Enter passenger name: ");
    scanf("%s", newReservation.name);
    printf("Enter passenger age: ");
    scanf("%d", &(newReservation.age));

    struct reservationNode* reservationNode = (struct reservationNode*) malloc(sizeof(struct reservationNode));
    reservationNode->data = newReservation;
    reservationNode->next = NULL;

    // No existing reservation
    if(selectedFlight->reservationHead == NULL) {
        selectedFlight->reservationHead = reservationNode;
    } else {
        struct reservationNode* tmp = selectedFlight->reservationHead;
        while(tmp->next != NULL) {
            tmp = tmp->next;
        }   

        tmp->next = reservationNode;
    }

    printf("Booking created\n\n");
}

int listAllReservations(struct reservationNode* headRef) {
    int count = 0;
    struct reservationNode* tempRef = headRef;

    printf("\nStart of reservation list.\n\n");
    while (tempRef != NULL) {
        count++;
        printf("Seatnumber: %d. Passenger name: %s\n", tempRef->data.seatNumber, tempRef->data.name);
        tempRef = tempRef->next;
    }
    printf("\nEnd of reservation list.\n\n");
    return count;
}

struct reservationNode* getReservationFromList(struct reservationNode* headRef, int numOfSeats) {
    int seatSelected = 0;
    do {
        printf("Select a seat by its number in the list: ");
        scanf("%d", &seatSelected);
    } while (seatSelected < 0 || seatSelected > numOfSeats);

    int count = 1;
    struct reservationNode* tempRef = headRef;

    while (tempRef->next != NULL)
    {
        if(tempRef->data.seatNumber == seatSelected) {
            break;
        }
        tempRef = tempRef->next;
    }
    return tempRef;
    printf("Seat number: %d with passenger: %s selected", tempRef->data.seatNumber, tempRef->data.name);
}

void updateSeats(struct reservationNode* head) {
    if(head == NULL) return;

    int count = 1;
    struct reservationNode* tmp = head;
    tmp->data.seatNumber = count;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
        count++;
        tmp->data.seatNumber = count;
    }
}

struct reservationNode* deleteReservation(struct reservationNode* reservationHead, struct reservationNode* reservationToBeDeleted) 
{ 
    if (reservationHead == NULL || reservationToBeDeleted == NULL) 
        return reservationHead; 

    // If the node we are deleted is the head node, we need to set the next 
    // node in the list as head
    if (reservationHead == reservationToBeDeleted) {
        reservationHead = reservationHead->next;
        free(reservationToBeDeleted);
        return reservationHead;
    }

    struct reservationNode* previous = reservationHead;
    struct reservationNode* comparisonNode = reservationHead->next;

    while(reservationToBeDeleted != comparisonNode) {
        previous = comparisonNode;
        comparisonNode = comparisonNode->next;
    }

    if(comparisonNode->next != NULL) {
        previous->next = comparisonNode->next;
    } else {
        previous->next = NULL;
    }

    free(reservationToBeDeleted);
    updateSeats(reservationHead);
    return reservationHead;
}

void cleanupFlightManagement(struct planeNode* flightHead) {
    struct planeNode* deleteFlight = flightHead;
    struct planeNode* next = flightHead;
    while(flightHead != NULL) {
        deleteFlight = flightHead;
        flightHead = flightHead->next;

        struct reservationNode* deleteRes;
        while (deleteFlight->data.reservationHead != NULL)
        {
            deleteRes = deleteFlight->data.reservationHead;
            deleteFlight->data.reservationHead = deleteFlight->data.reservationHead->next;
            printf("Deleting reservation for passenger: %s \n", deleteRes->data.name);
            free(deleteRes);
        }

        printf("Deleting flight with ID: %s \n", deleteFlight->data.flightId);
        free(deleteFlight);
    }
}