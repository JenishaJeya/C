#include <stdbool.h>

#ifndef DEF_H
#define DEF_H

struct reservation {
    int seatNumber;
    char name[50]; // Alow up to 50 characters in name
    int age;
};

struct reservationNode {
    struct reservation data;
    struct reservationNode* next;
};

struct plane {
    char flightId[5]; // e.g., AB-25
    char destination[50];
    int seats;
    int departureTime;
    bool delayed;

    struct reservationNode *reservationHead;
};

struct planeNode {
    struct plane data;
    struct planeNode* next;
    struct planeNode* previous;
};

#endif