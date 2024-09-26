#include <stdio.h>
#include <stdlib.h>
#include "definition.h"
#include "Flight-management.h"

int main() {
    printf("\n\n\t\tFlight management system\n\n\n");
    int choice, flightNumIncremented, numOfFlights;
    struct plane* selectedFlight;
    struct planeNode* selectedFlightNode;
    struct planeNode* flightHead = NULL;

    while(1)
    {
        printf("1. Add a new flight \n");
        printf("2. Add passenger to flight\n");
        printf("3. Set new departure time\n");
        printf("4. Show delayed flights\n");
        printf("5. Delete flight\n");
        printf("6. Delete reservation\n");
        printf("7. Show all flights and number of seats\n");
        printf("8. Search flights by destination\n");
        printf("9. Search flights by passenger name\n");
        printf("10. Exit\n\n");

        printf("Enter your choice :  ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1: {
               struct plane flight = createFlight(&flightNumIncremented);
               flightHead = addFlight(flightHead, flight);
               break;
            }
        
            case 2:
               numOfFlights = listAllFlights(flightHead, false);
               if(numOfFlights == 0) {
                  printf("No flights available. \n\n");
                  continue;
               }
               selectedFlight = getFlightFromList(flightHead, numOfFlights);
               createReservation(selectedFlight, numOfFlights);
               break;

            case 3:
               numOfFlights = listAllFlights(flightHead, false);
               if(numOfFlights == 0) {
                  printf("No flights available. \n\n");
                  continue;
               }
               selectedFlight = getFlightFromList(flightHead, numOfFlights);
               setNewDepartureTime(selectedFlight);
               break;

            case 4:
               listAllDelayedFlights(flightHead);
               break;

            case 5:
               numOfFlights = listAllFlights(flightHead, false);
               if(numOfFlights == 0) {
                  printf("No flights available. \n\n");
                  continue;
               }
               selectedFlightNode = getFlightNodeFromList(flightHead, numOfFlights);
               flightHead = deleteFlight(flightHead, selectedFlightNode);
               break;

            case 6:
               numOfFlights = listAllFlights(flightHead, false);
               if(numOfFlights == 0) {
                  printf("No flights available. \n\n");
                  continue;
               }
               selectedFlightNode = getFlightNodeFromList(flightHead, numOfFlights);
               int numOfSeats = listAllReservations(selectedFlightNode->data.reservationHead);
               if(numOfSeats == 0) {
                  printf("No bookings made. \n\n");
                  continue;
               }
               struct reservationNode* reservationNode = getReservationFromList(selectedFlightNode->data.reservationHead, numOfSeats);
               selectedFlightNode->data.reservationHead = deleteReservation(selectedFlightNode->data.reservationHead, reservationNode);
               break;

            case 7:
               numOfFlights = listAllFlights(flightHead, true);
               break;

            case 8:
               printFlightFromListByDestination(flightHead);
               break;

            case 9:
               printFlightFromListByPassenger(flightHead);
               break;
        
            case 10:
               cleanupFlightManagement(flightHead);
               printf("\n\n\t\t\tFlight management system shutting down!\n\n\n");
               exit(0);
        }
    }
    return 0;
}