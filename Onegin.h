#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

char* MyOwnStrdup(const char*);

void PutsArrayOfPointersToStrings(char*, int, char**, int*);
void CompareStrings(int, char**);
void CompareStringsFromEnd(int, char **);
void OutputInFile(FILE*, int, char**);

