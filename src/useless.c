#include "../headers/utils.h"
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
#define maxcharprog 79

typedef struct {
    int delay;
    char* progname;
} entry;

size_t countlines(FILE* file);
void allocate_arr(entry** arr, size_t countline);
void readentries(FILE* file, entry* arr, size_t countline);
void sortentries(entry* arr, size_t countline);
void execute(char* progname);
int min (ibt a, int b);

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

    entry* arr;
    allocate_arr(&arr, countline);
    readentries(file, arr, countline);
    sortentries(arr, countline);

    int expired = 0; size_t i;
    for (i = 0; i < countline; ++i)
    {
        sleep(max(arr[i].delay - expired, 0));
        execute(arr[i].progname);
        expired = arr[i].delay;
    }
    fprintf(stderr, "Done\n");
    return 0;
}
