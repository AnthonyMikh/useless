#include <stdio.h>
#include <stdlib.h>
//--------------------------------------------------------------------------
//USELESS stands for "Unix system extremely late execution software system".
//This program reads the file specified via launch from command line and
//launch programs described in file with specified delay.
//File format is plain text with lines like
//<delay in seconds> <program to launch>
//Lines don't have to be ordered by delay.
//
//This version of program was designed by Anthony Mikhailov aka Hedgehog1024
//You can contact him by e-mail hedgehog1024@yandex.ru
//Feel free to examine, copy, modify and redistribute this program and it's
//source code in any way.
//
//USELESS program v1.0 by Hedgehog1024
//--------------------------------------------------------------------------
#define maxchardelay 4
#define maxcharprog 79

typedef struct {
    int delay;
    char* progname;
} entry;

size_t countlines(FILE* file);
void allocate_arr(entry* arr, size_t countline);
void readentries(FILE file, entry* arr, size_t countline);
void sortentries(entry* arr);

int main (int argc, char** argv)
{
    if (argc == 1) //launched with no arguments
    {
        puts("Usage: useless <filename>\n");
        return 0;
    }

    FILE *file = fopen(argv[1],"r");
    if (file == 0)
    {
        fprintf(stderr, "Error occured trying to open file.\n");
        return -1;
    }

    size_t countline = countlines(file);
    if (countline == 0) //file is empty
        return 0;

    rewind(file); //set file cursor at the beginning
    allocate_arr(arr, countline);
    readentries(file, arr, countline);
    return 0;
}

size_t countlines(FILE* file)
{
    char ch; size_t countline = 0;
    do {
        ch = fgetc(file);
        if (ch == '\n')
             ++countline;
    } while (ch != EOF)
    if (ch != '\n' && countline != 0)
        ++countline;
    return countline;
}

void allocate_arr(entry* arr, size_t countline)
{
    arr = malloc(sizeof(entry)*countline);
    if (arr == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(-1);
    }
    int i;
    for (i = 0; i < countline; ++i)
    {
        arr[i].progname = malloc(sizeof(char)*maxcharprog+1);
    }
    return;
}

void readentries(FILE file, entry* arr, size_t countline)
{
    int i;
    for (i = 0; i < countline; ++i)
    {
        fscanf(file, "%d %79s", &(arr[i].delay), &(arr[i].progname));
    }
    return;
}

int compare_entries(const void* a, const void* b)
{
    entry entry_a = (entry*)a;
    entry entry_b = (entry*)b;
    return entry_a->delay - entry_b->delay;
}

void sortentries(entry* arr, size_t countline)
{
    qsort(arr, countline, sizeof(entry), compare_entries);
    return;
}
