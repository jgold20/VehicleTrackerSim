// Name of Author(s): Joshua Gold
// Course Number and Name: CSE 220, Programming for Computer Engineering
// Semester: Spring 2015
// Lab Project Number: 1
// Time Spent: 10 hours

#include <stdio.h>
#include <string.h>
#include "parseArgs.h"

//Global variables
int timeFlag;
int inputFlag;
int outputFlag;
int verboseFlag;
int silentFlag;
int inputFlagError;
int outputFlagError;
int timeInt = 0;
int inputFlagNoName;
int totalFlag = 0;
int inputErrorNoOpen;
char *stpcpy (char *__dest, const char *__src);
char fileNameRead[60];
char fileNameWrite[60];

//parse user args
void parseCmdLine(int argc, char*argv[])
{
    int badArgs = 0;
    int i;
    char fileCheck[] = "-o";

    //loop to get cmd line args
    for(i = 0; i < argc; i++) {
     if (argv[i][0] == '-') {
      if (argv[i][1] == 'q'){
       badArgs = 1;
     }
      if (argv[i][1] == 'w'){
      badArgs = 1;
     }
   if (argv[i][1] == 'e'){
       badArgs = 1;
     }
   if (argv[i][1] == 'r'){
       badArgs = 1;
     }
   if (argv[i][1] == 'y'){
       badArgs = 1;
     }
   if (argv[i][1] == 'u'){
       badArgs = 1;
     }
   if (argv[i][1] == 'i'){
       badArgs = 1;
     }
   if (argv[i][1] == 'p'){
       badArgs = 1;
     }
  if (argv[i][1] == 'a'){
       badArgs = 1;
     }
  if (argv[i][1] == 'd'){
       badArgs = 1;
     }
  if (argv[i][1] == 'g'){
       badArgs = 1;
     }
if (argv[i][1] == 'h'){
       badArgs = 1;
     }
if (argv[i][1] == 'j'){
       badArgs = 1;
     }
if (argv[i][1] == 'k'){
       badArgs = 1;
     }
if (argv[i][1] == 'l'){
       badArgs = 1;
     }
if (argv[i][1] == 'z'){
       badArgs = 1;
     }
if (argv[i][1] == 'x'){
       badArgs = 1;
     }
if (argv[i][1] == 'c'){
       badArgs = 1;
     }
if (argv[i][1] == 'n'){
       badArgs = 1;
     }
if (argv[i][1] == 'm'){
       badArgs = 1;
     }






      //verbose flag 'b'
      if (argv[i][1] == 'b') {
         verboseFlag = 1;
      }
       //silent flag
       if (argv[i][1] == 's') {
          silentFlag = 1;
       }
       //checks to see if user wants to read from a file
       if (argv[i][1] == 'f') {
        FILE *fp;
        fp = fopen(argv[i + 1], "r");
        //null error checker
        if (argv[i + 1] == '\0') {
         inputFlagError = 1;
         printf("expecting argument following -f \n");
         exit(0);
        }
         else {
          strcpy(fileNameRead, argv[i + 1]);
          if (strcmp(fileNameRead, fileCheck) == 0) {
           inputFlagNoName = 1;
          }//if the file can not be opened
           else if (!fp) {
              inputErrorNoOpen = 1;
           }//if opened close and flag input
            else {
             fclose(fp);
             inputFlag = 1;
            }
         }
       }
       //checks for time flag
       if (argv[i][1] == 't') {
           if(argv[i+1] == '\0') {
           printf("Error: Expecting argument following -t\n");
           exit(0);
           }
           //time from user
           timeInt = atoi(argv[i+1]);

           if(timeInt <= 0) {
               printf("Error: Expecting argument following -t\n");
               exit(0);
           }
           timeFlag = 1;
       }
       //checks to see if user wants to write to a file
       if (argv[i][1] == 'o') {
                FILE *fr;
                fr = fopen(argv[i + 1], "w");
                //null checker
                if (argv[i + 1] == '\0') {
                    if (inputFlagError == 0) {
                        printf("Error: Expecting argument following -o\n");
                        exit(0);
                    }
                    outputFlagError = 1;
                }//write to file
                else {
                    strcpy(fileNameWrite, argv[i + 1]);
                    if (!fr) {
                        printf("could not open %s\n", fileNameWrite);
                        outputFlagError = 1;
                    }//close file
                    else {
                        fclose(fr);
                        outputFlag = 1;
                    }
                }
            }
        }
    }
    totalFlag = inputFlag + outputFlag + timeFlag + verboseFlag + silentFlag + inputFlagError;
    if(badArgs == 1) {
     printf("Incorrect argument(s): Arguments allowed are -t seconds, -f filename, -o filename and -b/-s\n");
     exit(0);
    }
    if(timeFlag == 0) {
        printf("Error: Expecting argument -t\n");
        exit(0);
    }
    if(inputFlag == 0) {
        if(inputFlagNoName == 1) {
         printf("Error: expecting argument following -f\n");
        }
        else if(inputErrorNoOpen == 1)
  	{
          printf("could not open %s\n", fileNameRead);
        }
        else{
        printf("Error: Expecting argument -f\n");
       }
    }
    if(silentFlag == 1 && verboseFlag == 1) {
        printf("Error: Expecting argument either -b OR -s\n");
        exit(0);
    }
    if(outputFlag == 0)
    {
        strcpy(fileNameWrite, "results.txt");
    }
}

struct userArguments * getArgs() {
    struct userArguments* args = malloc(sizeof(*args));
    args->bFlag = verboseFlag;
    args->sFlag = silentFlag;
    args->fFlag = inputFlag;
    args->oFlag = outputFlag;
    args->tFlag = timeFlag;
    args->N = timeInt;
    stpcpy(args->fNameRead, fileNameRead);
    strcpy(args->fNameWrite, fileNameWrite);
    return(args);
}

