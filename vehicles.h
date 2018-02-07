#ifndef VEHICLES_H
#define VEHICLES_H
#include <stdio.h>
#include <stdlib.h>
#include "parseArgs.h"
#include "main.h"

void updateLocation(CAR *car, int carCount, int N);

double distanceCalc(CAR *car, int pid, int pid1);

void cleanList(CAR *car, int carCount);

void getNeighbors(CAR *car, int carCount);

#endif
