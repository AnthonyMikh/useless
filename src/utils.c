#include "../headers/shared.h"
#include "../headers/utils.h"

#define maxcharprog 79

typedef struct {
    int delay;
    char* progname;
} entry;

size_t countlines(FILE* file)
{
    char ch; size_t countline = 0;
    do {
        ch = fgetc(file);
        if (ch == '\n')
             ++countline;
    } while (ch != EOF);
    if (ch != '\n' && countline != 0)
        ++countline;
    return countline;
}

void allocate_arr(entry** arr, size_t countline)
{
    *arr = malloc(sizeof(entry)*countline);
    if (*arr == NULL)
    {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(-1);
    }
    size_t i;
    for (i = 0; i < countline; ++i)
    {
        (*arr)[i].progname = malloc(sizeof(char)*maxcharprog+1);
    }
    return;
}

void readentries(FILE* file, entry* arr, size_t countline)
{
    size_t i;
    for (i = 0; i < countline; ++i)
    {
        fscanf(file, "%d %79s", &(arr[i].delay), arr[i].progname);
    }
    return;
}

int compare_entries(const void* a, const void* b)
{
    entry entry_a = *(entry*)a;
    entry entry_b = *(entry*)b;
    return entry_a.delay - entry_b.delay;
}

void sortentries(entry* arr, size_t countline)
{
    qsort(arr, countline, sizeof(entry), compare_entries);
    return;
}

void execute(char* progname)
{
    system(progname);
}

int max (int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
