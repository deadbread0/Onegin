#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>

#include "Onegin.h"

int main(const int argc, const char *argv[])
{
    int amount_of_str = 0;
    const char* filee_name = argv[1]; 
    int size = GetSizeOfInputFile(filee_name);

    FILE* filee = fopen(filee_name, "rb");
    FILE* output_filee = fopen("output_filee.txt", "w");
    assert(output_filee != nullptr);

    char text[size + 1] = {0}; 
    int amount_of_symb = ReadText(filee, text, size);

    if (!CheckFile(filee, amount_of_symb, size))
        return 0;

    char *array_of_ptr[size] = {0};

    InfAboutText StructText = {text, size, &amount_of_str, array_of_ptr, output_filee};

    PutsArrayOfPointersToStrings(&StructText);
    BubbleSort(&StructText, CompareStrings);
    OutputInFile(&StructText);

    BubbleSort(&StructText, CompareStringsFromEnd);
    OutputInFile(&StructText);
    OutputFirstTextInFile(&StructText);
    printf("Texts in file\n");

    return 0;
}

int GetSizeOfInputFile(const char* filee_name)
{
    assert(filee_name != nullptr);

    struct stat StructStat;
    stat(filee_name, &StructStat);
    return StructStat.st_size;
}

bool CheckFile(FILE* filee, int amount_of_symb, int size)
{
    if (filee == nullptr)
    {
        printf("File didn't open((\n");
        return false;
    }
    if (amount_of_symb < size)
    {
        printf("Reading text from file wasn't succesful\n");
        return false;
    }
    return true;
}

int ReadText(FILE* filee, char* text, int size)
{
    assert(text != nullptr);
    assert(filee != nullptr);
 
    int amount_of_symb = fread(text, sizeof(char), size, filee);
    text[size] = '\0';
    return amount_of_symb;
}

void PutsArrayOfPointersToStrings(InfAboutText* StructText)
{
    assert(StructText->text != nullptr);
    assert(StructText->amount_of_str != nullptr);

    int count_ptrm = 0;
    for (int i = 0; i < StructText->size; i++)
    {
        int len = 0;
        StructText->array_of_ptr[count_ptrm] = MyOwnStrdup(StructText->text + i);
        while (StructText->text[i] != '\n' && StructText->text[i] != '\0')
        {
            i++;
            len++;
        }
        len++;
        *(StructText->array_of_ptr[count_ptrm] + len - 1) = '\0';
        count_ptrm++;
    }
    *StructText->amount_of_str = count_ptrm;
}

int CompareStrings(int amount_of_str, char **array_of_ptr, int i)//сравнивает строки слева направо
{
    assert(*array_of_ptr != nullptr);
    assert(array_of_ptr != nullptr);

            int k1 = 0, k2 = 0;
            while (1)
            {
                if ((int)(array_of_ptr[i][k1]) == 0 || (int)(array_of_ptr[i + 1][k2]) == 0)
                    return 1;
                if (!isalpha(array_of_ptr[i][k1]))
                    k1++;
                else if (!isalpha(array_of_ptr[i + 1][k2]))
                    k2++;
                else if (isalpha(array_of_ptr[i][k1]) && isalpha(array_of_ptr[i + 1][k2]) && 
                         (int)tolower(array_of_ptr[i][k1]) > (int)tolower(array_of_ptr[i + 1][k2]))
                    return 0;
                else if ((int)tolower(array_of_ptr[i][k1]) == (int)tolower(array_of_ptr[i + 1][k2]))
                {
                    k1++;
                    k2++;
                }
                else
                    return -1;
            }

}

void BubbleSort(InfAboutText* StructText, int (*pt)(int, char**, int))
{
    for (int j = 0; j < *StructText->amount_of_str - 1; j++)
    {
        for (int i = 0; i < *StructText->amount_of_str - 2; i++)
        {
            if (pt(*StructText->amount_of_str, StructText->array_of_ptr, i) == 0)
            {
                char* copy = StructText->array_of_ptr[i]; 
                StructText->array_of_ptr[i] = StructText->array_of_ptr[i + 1];
                StructText->array_of_ptr[i + 1] = copy;
            }
        }
    }

}

void OutputInFile(InfAboutText* StructText)
{
    assert(StructText->output_filee != nullptr);
    assert(*StructText->array_of_ptr != nullptr);

    for (int i = 0; i < *StructText->amount_of_str; i++)
        fprintf(StructText->output_filee, "%s", StructText->array_of_ptr[i]);
    fprintf(StructText->output_filee, "%c", '\n');
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

int CompareStringsFromEnd(int amount_of_str, char **array_of_ptr, int i)//сравнивает строки справа налево
{
    assert(*array_of_ptr != nullptr);
    assert(array_of_ptr != nullptr);

            int k1 = 1, k2 = 1;
            int len1 = strlen(array_of_ptr[i]), len2 = strlen(array_of_ptr[i + 1]);
            while (1)
            {
                if ((int)(array_of_ptr[i][len1 - k1]) == 0 || (int)(array_of_ptr[i + 1][len2 - k2]) == 0)
                    return 1;
                if (!isalpha(array_of_ptr[i][len1 - k1]))
                    k1++;
                else if (!isalpha(array_of_ptr[i + 1][len2 - k2]))
                    k2++;
                else if (isalpha(array_of_ptr[i][len1 - k1]) && isalpha(array_of_ptr[i + 1][len2 - k2]) && 
                         (int)tolower(array_of_ptr[i][len1 - k1]) > (int)tolower(array_of_ptr[i + 1][len2 - k2]))
                {
                    return 0;
                }
                else if ((int)tolower(array_of_ptr[i][len1 - k1]) == (int)tolower(array_of_ptr[i + 1][len2 - k2]))
                {
                    k1++;
                    k2++;
                }
                else
                    return -1;
            }

}

void OutputFirstTextInFile(InfAboutText* StructText)
{
    int i = 0;
    while (StructText->text[i] != '\0')
    {
        if (StructText->text[i] != '\n')
            fputc(StructText->text[i], StructText->output_filee);
        i++;
    }
    
}