#ifndef PARSEARGS_H
#define PARSEARGS_H
#include <stdio.h>
#include <stdlib.h>

//function to scan command line arguments and set options
void parseCmdLine(int argc, char*argv[]);

struct userArguments {
    int tFlag;
    int fFlag;
    int oFlag;
    int sFlag;
    int bFlag;
    int N;
    char fNameRead[60];
    char fNameWrite[60];
};

struct userArguments * getArgs();
#endif
