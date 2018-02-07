// Name of Author(s): Joshua Gold
// Course Number and Name: CSE 220, Programming for Computer Engineering
// Semester: Spring 2015
// Lab Project Number: 1
// Time Spent: 10 hours

//includes
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "main.h"
#include "parseArgs.h"
#include <ctype.h>
#include "vehicles.h"

//function initializers
void getNeighbors(CAR *car, int carCount);
char *stpcpy (char *__dest, const char *__src);
void updateLocation(CAR *car, int carCount, int N);
double distanceCalc(CAR *car, int pid, int pid1);
void cleanList(CAR *car, int carCount);
 void print(CAR *car, int i, FILE *fs);
 void print1(int neighbor, FILE *fs);

int main(int argc, char **argv) {

    //call command line arg parser
    parseCmdLine(argc, argv);
      //structs
      struct userArguments *args = getArgs();

      //chars
      char fileNameRead[60];
      char fileData[1000];    
      char newChar;
      char yCoord[10];
      char speed[10];
      char theta[10];
      char xCoord[10];

      //ints
      int i,j, count, size = 0, charRead;
      int currentCar = 0;
      int currentValue = 0;
      int whereWasI = 0;
      int xCoordStart, yCoordStart, speedStart, thetaStart;
      int commaCount = 0;
      int badSymbolFlag = 0;
      int fileSpacingCheck = 0;
      int fileFormatCheck = 0;

    //makes sure that a time is specified
    if(args->tFlag == 0) {
     exit(0);
    }

    //make sure that it reads from a file
    if(args->fFlag == 0) {
     exit(0);
    }
      //reading file info
      strcpy(fileNameRead, args->fNameRead);
      count = 0;

      if(args->fFlag == 1) {
       FILE *fp;
       fp = fopen(fileNameRead, "r");
       do {
        charRead = fgetc(fp);
        if( feof(fp)) {
         break;
        }
        newChar = charRead;
        if(newChar == '\n') {
             if(fileSpacingCheck == 1)
		{
		}     
             else
             if(fileFormatCheck > 3)
            {
                printf("Error: Too many values on line: %d \n", size + 1);
                exit(0);
            }else if(fileFormatCheck < 3 && fileFormatCheck > 0)
            {
                printf("Error: Not enough values on line: %d \n", size + 1);
                exit(0);
            }else{
	
                fileFormatCheck = 0;
                size++;
                fileSpacingCheck = 1;}
        }
           //comma is read
           if(newChar == ',') {
            fileSpacingCheck = 2;
            commaCount++;
 	    fileFormatCheck++;
	   
        }
        //is not valid character
        if(isalpha(newChar)) {
            fileSpacingCheck = 2;
         badSymbolFlag = 1;
        }
        fileData[i] = newChar;
        i++;
        fileSpacingCheck;
        count++;
       }while(1);
       fclose(fp);
      }
    //if no car data is found
    if(count == 0) {
     printf("Error: data file is empty!\n");
     exit(0);
    }
    //if the txt file is not formatted properly
    if(commaCount > 3 && size < 2) {
     printf("Error: input file error\n");
     exit(0);
    } 
    //errors AR *car, int i, int neighbor)

    if(commaCount < 3 || count < 1 || badSymbolFlag != 0) {
     printf("Error: input file error\n");
     exit(0);
    }
    //if there are too many cars
    if(size > 50) {
        printf("Error: Too many cars!\n");
        exit(0);
    }   
    //set size for car structs
    CAR car[size];

    //sets all arrays to null (cleans them)
    for(i = 0; i < 10; i++) {
     xCoord[i] = '\0';
     yCoord[i] = '\0';
     speed[i] = '\0';
     theta[i] = '\0';
    }

    //gets the values
    while(1) {
     if(size != 1){
     if(currentCar == size - 1) {
      break;
      }
     }
     if(currentValue > 3){
      if(size == 1) {
       break;
      }
      currentCar++;
      currentValue = 0;
     }
     //xCoord
     if(currentValue == 0){
         xCoordStart = 0;

         for(j = whereWasI; j < count; j++) {
          if(fileData[j] == ',') {
           currentValue++;
           whereWasI++;
	       break;
          }
          else {
	        xCoord[xCoordStart] = fileData[j];
            xCoordStart++;
            whereWasI++;
          }
         }
        car[currentCar].xloc = atof(xCoord);
        for(i = 0; i < 10; i++) {
            xCoord[i] = '\0';
        }
     }
     //yCoord
     if(currentValue == 1){
         yCoordStart = 0;
         for(j = whereWasI; j < count; j++) {
          if(fileData[j] == ',') {
           currentValue++;
           whereWasI++;
           break;
          }
          else {
           yCoord[yCoordStart] = fileData[j];
           yCoordStart++;
           whereWasI++;
          }
         }
        car[currentCar].yloc = atof(yCoord);
        for(i = 0; i < 10; i++) {
         yCoord[i] = '\0';
        }
     }
     //speed
     if(currentValue == 2){
      speedStart = 0;
         for(j = whereWasI; j < count; j++) {
          if(fileData[j] == ',') {
           currentValue++;
           whereWasI++;
           break;
          }
          else {
           speed[speedStart] = fileData[j];
           speedStart++;
           whereWasI++;
          }
         }
        car[currentCar].speed = atof(speed);
        for(i = 0; i < 10; i++) {
         speed[i] = '\0';
        }
     }
      if(currentValue == 3){
      thetaStart = 0;
         for(j = whereWasI; j < count; j++) {
          if(fileData[j] == '\n') {
           currentValue++;
           whereWasI++;
           break;
          }
          else {
           theta[thetaStart] = fileData[j];
           thetaStart++;
           whereWasI++;
          }
         }
        car[currentCar].theta = atof(theta);
        for(i = 0; i < 10; i++) {
         theta[i] = '\0';
        }
        //sets the cars ID
        car[currentCar].pid = currentCar + 1;
     }
    }
    
    //starts the linked lists for the cars
    for(i = 0; i < size; i++) {
     car[i].head = NULL;
    }

  
    //while loop for cars
    FILE *fs;
    fs = fopen(args->fNameWrite, "w+");
    
    while(1) {
        sleep(args->N);
        getNeighbors(car, size);
        for (i = 0; i < size; i++) {
	    print(car, i, fs);
            LLIST *ptr = car[i].head;
            while (ptr != NULL) {
                print1(ptr->neighbor, fs);
                ptr = ptr->next;
            }
        }
        printf("\n");
        cleanList(car, size);
        updateLocation(car, size, args->N);
    }    
}

	void print(CAR *car, int i, FILE *fs)
	{ 
	   struct userArguments *args = getArgs();
           fs = fopen(args->fNameWrite, "a");

          if(args->sFlag == 0){  printf("\nVehicle %d at location %.2f, %.2f ", car[i].pid, car[i].xloc, car[i].yloc);
            printf("moving with a velocity %.2f", car[i].speed);
            printf(", it's neighbors are: ");}
            fprintf(fs, "\nVehicle %d at location %.2f, %.2f ", car[i].pid, car[i].xloc, car[i].yloc);
            fprintf(fs, "moving with a velocity %.2f", car[i].speed);
            fprintf(fs, ", it's neighbors are: "); 
            fclose(fs);
        }
       
        void print1(int neighbor, FILE *fs)
	{
	  struct userArguments *args = getArgs();
          fs = fopen(args->fNameWrite, "a");
          if(args->sFlag == 0){  printf("Vehicle %d, ", neighbor);}
          fprintf(fs, "Vehicle %d, ",neighbor);
	  fclose(fs);
        }



        



