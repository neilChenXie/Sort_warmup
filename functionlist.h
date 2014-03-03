#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include <sys/time.h>
//#include <sys/stat.h>
#include <locale.h>
#include <math.h>
#include "cs402.h"
#include "my402list.h"

void CreateList(FILE *fp, My402List *List);
void SortMyList(My402List *List);
void PrintAll(My402List *List);
void ExitAll(char * message,int num_line);

typedef struct tagMy402ListElemObj{
    char *TSign;//why [2]
    long int TTime;//necessary?
    char *TAm;
    char *TDesc;
}My402ListElemObj;
