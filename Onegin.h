#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

struct InfAboutText {
    char* text;
    int size;
    int* amount_of_str;
    char **array_of_ptr;
    FILE* output_filee;
};

char* MyOwnStrdup(const char*);

void PutsArrayOfPointersToStrings(InfAboutText*);
int CompareStrings(int, char**, int);
int CompareStringsFromEnd(int, char**, int);
void OutputInFile(InfAboutText*);
int GetSizeOfInputFile(const char*);
int ReadText(FILE*, char*, int);
void OutputFirstTextInFile(InfAboutText*);
bool CheckFile(FILE*, int, int);
int compare(const void*, const void*);
void BubbleSort(InfAboutText*, int (*pt)(int, char**, int));
