// Name of Author(s): Joshua Gold
// Course Number and Name: CSE 220, Programming for Computer Engineering
// Semester: Spring 2015
// Lab Project Number: 1
// Time Spent: 10 hours

//includes
#include <math.h>
#include "main.h"
#include "vehicles.h"

//constants
#define PI 3.14159265

//returns info on a car based on the cars ID#
void updateLocation(CAR *car, int carCount, int N) {
    float xloc, yloc, speed, theta, speedAndAngleX, speedAndAngleY;
    int i;
    //updates each car's x and y coord
    for(i = 0; i < carCount; i++) {
        xloc = car[i].xloc;
        yloc = car[i].yloc;
        speed = car[i].speed;
        theta = car[i].theta;
        theta = theta * PI;
        theta = theta/180;

        //formula xloc + speed*cosTheta*N
        speedAndAngleX = speed * cos(theta);
        speedAndAngleX = speedAndAngleX * N;
        xloc = xloc + speedAndAngleX;
        car[i].xloc = xloc;

        //same formula but yloc
        speedAndAngleY = speed * sin(theta);
        speedAndAngleY = speedAndAngleY * N;
        yloc = yloc + speedAndAngleY;
        car[i].yloc = yloc;
    }
}

//returns info on a car based on the cars ID#
double distanceCalc(CAR *car, int pid, int pid1) {
    float x0 = car[pid].xloc, x1= car[pid1].xloc, y0 = car[pid].yloc, y1 = car[pid1].yloc;
    double distance;
    double x = x1 - x0;
    double y = y1 - y0;
    //to the power of two
    x = x * x;
    y = y * y;
    //square root that
    distance = sqrt(x+y);
    return distance;
}

//cleans the linked lists
void cleanList(CAR *car, int carCount) {
    LLIST *temp;
    int i;
    //deletes the linked list for each car
    for(i = 0; i < carCount; i++) {
        while (car[i].head) {
            temp = car[i].head;
            car[i].head = car[i].head->next;
            free(temp);
        }
    }
}

//neighbor location update
void getNeighbors(CAR *car, int carCount) {
    LLIST *ptr;
    int i,k;

    for(i = 0; i < carCount; i++) {
        for(k = 0; k < carCount; k++) {
            if(distanceCalc(car, car[i].pid, car[k].pid) <= 250) {
                if(car[i].pid != car[k].pid) {
                    ptr = (LLIST*)malloc(sizeof(LLIST));
                    ptr->neighbor = car[k].pid;
                    ptr->next = car[i].head;
                    car[i].head = ptr;
                }
            }
        }
    }
}
