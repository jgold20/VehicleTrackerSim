// Name of Author(s): Joshua Gold
// Course Number and Name: CSE 220, Programming for Computer Engineering
// Semester: Spring 2015
// Lab Project Number: 1
// Time Spent: 10 hours


#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>

//structure of linked list for vehicle neighbors'
typedef struct neighbor_list{
    int neighbor;
    struct neighbor_list* next;
}LLIST;

//structure of vehicles
typedef struct vehicle{
    int pid;
    float xloc;
    float yloc;
    float speed;
    float theta;
    LLIST *head;
}CAR;
#endif
