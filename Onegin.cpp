#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "Onegin.h"

int main()
{
    struct stat StructStat;

    int amount_of_str = 0;
    const char* filee_name = "text.txt"; 
    stat(filee_name, &StructStat);
    int size = StructStat.st_size;


    FILE* filee = fopen("text.txt", "r");
    FILE* newfilee = fopen("newfilee.txt", "w");
    if (filee == nullptr)
        printf("File didn't open((\n");

    char text[size + 1] = {0}; 
    fread(text, sizeof(char), size, filee);
    text[size] = '\0';

    char *mass_of_ptr[size] = {0};
    PutsArrayOfPointersToStrings(text, size, mass_of_ptr, &amount_of_str);
    CompareStrings(amount_of_str, mass_of_ptr);
    OutputInFile(newfilee, amount_of_str, mass_of_ptr);

    CompareStringsFromEnd(amount_of_str, mass_of_ptr);
    OutputInFile(newfilee, amount_of_str, mass_of_ptr);
    fprintf(newfilee, "%s\n", text);
    printf("Texts in file\n");
}

void PutsArrayOfPointersToStrings(char *text, int size, char **mass_of_ptr, int* amount_of_str)
{
    assert(text != nullptr);
    assert(amount_of_str != nullptr);

    int count_ptrm = 0;
    for (int i = 0; i < size; i++)
    {
        int len = 0;
        mass_of_ptr[count_ptrm] = MyOwnStrdup(text + i);
        while (text[i] != '\n' && text[i] != '\0')
        {
            i++;
            len++;
        }
        len++;
        *(mass_of_ptr[count_ptrm] + len - 1) = '\0';
        count_ptrm++;
    }
    *amount_of_str = count_ptrm;
}

void CompareStrings(int amount_of_str, char **mass_of_ptr)//сравнивает строки слева направо
{
    assert(*mass_of_ptr != nullptr);

    for (int j = 0; j < amount_of_str - 1; j++)
    {
        for (int i = 0; i < amount_of_str - 2; i++)
        {
            int k1 = 0, k2 = 0;
            while (1)
            {
                if ((int)(mass_of_ptr[i][k1]) == 0 || (int)(mass_of_ptr[i + 1][k2]) == 0)
                    break;
                if (!isalpha(mass_of_ptr[i][k1]))
                    k1++;
                else if (!isalpha(mass_of_ptr[i + 1][k2]))
                    k2++;
                else if (isalpha(mass_of_ptr[i][k1]) && isalpha(mass_of_ptr[i + 1][k2]) && 
                         (int)tolower(mass_of_ptr[i][k1]) > (int)tolower(mass_of_ptr[i + 1][k2]))
                {
                    char* copy = mass_of_ptr[i]; 
                    mass_of_ptr[i] = mass_of_ptr[i + 1];
                    mass_of_ptr[i + 1] = copy;
                    break;
                }
                else if ((int)tolower(mass_of_ptr[i][k1]) == (int)tolower(mass_of_ptr[i + 1][k2]))
                {
                    k1++;
                    k2++;
                }
                else
                    break;
            }
        }
    }

}

void OutputInFile(FILE* newfilee, int amount_of_str, char **mass_of_ptr)
{
    assert(newfilee != nullptr);
    assert(*mass_of_ptr != nullptr);

    for (int i = 0; i < amount_of_str; i++)
        fprintf(newfilee, "%s\n", mass_of_ptr[i]);
}

char* MyOwnStrdup(const char* str)
{
    assert(str != nullptr);

    char *copystr = 0;
    int len = strlen(str);
    copystr = (char *)calloc(len + 1, sizeof(char));
    if (copystr == nullptr)
        return nullptr;
    for (int i = 0; i < len; i++)
    {
        copystr[i] = str[i];
    }
    copystr[len] = '\0';
    return copystr;
}

void CompareStringsFromEnd(int amount_of_str, char **mass_of_ptr)//сравнивает строки справа налево
{
    assert(*mass_of_ptr != nullptr);

    for (int j = 0; j < amount_of_str - 1; j++)
    {
        for (int i = amount_of_str - 2; i >= 0; i--)
        {
            int k1 = 1, k2 = 1;
            int len1 = strlen(mass_of_ptr[i]), len2 = strlen(mass_of_ptr[i + 1]);
            while (1)
            {
                if ((int)(mass_of_ptr[i][len1 - k1]) == 0 || (int)(mass_of_ptr[i + 1][len2 - k2]) == 0)
                    break;
                if (!isalpha(mass_of_ptr[i][len1 - k1]))
                    k1++;
                else if (!isalpha(mass_of_ptr[i + 1][len2 - k2]))
                    k2++;
                else if (isalpha(mass_of_ptr[i][len1 - k1]) && isalpha(mass_of_ptr[i + 1][len2 - k2]) && 
                         (int)tolower(mass_of_ptr[i][len1 - k1]) > (int)tolower(mass_of_ptr[i + 1][len2 - k2]))
                {
                    char* copy = mass_of_ptr[i]; 
                    mass_of_ptr[i] = mass_of_ptr[i + 1];
                    mass_of_ptr[i + 1] = copy;
                    break;
                }
                else if ((int)tolower(mass_of_ptr[i][len1 - k1]) == (int)tolower(mass_of_ptr[i + 1][len2 - k2]))
                {
                    k1++;
                    k2++;
                }
                else
                    break;
            }
        }
    }

}//