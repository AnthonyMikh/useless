#include "shared.h"

size_t countlines(FILE* file);
void allocate_arr(entry** arr, size_t countline);
void readentries(FILE* file, entry* arr, size_t countline);
void sortentries(entry* arr, size_t countline);
void execute(char* progname);
int min (int a, int b);
