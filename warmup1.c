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
#include "functionlist.h"


    int main(int argc, char *argv[])
    {
        //initial list
        My402List *List;
        List = (My402List *)malloc(sizeof(My402List));
        (void)My402ListInit(List);
        //
	/*
        printf("the length of my402list is %d\n", My402ListLength(List));
        printf("it is empty? %d\n", My402ListEmpty(List));
        */
        int reading_from_file=0;

        if (argc == 3) {
            reading_from_file = 1;
        }
        FILE *fp=NULL;

        if (reading_from_file) {
            if(strcmp(argv[1],"sort"))
            {
                fprintf(stderr," the second input should be sort\n");
                return 0;
            }
            fp = fopen(argv[2], "r");
            if (fp == NULL) {
                fprintf(stderr, "Cannot open %s for reading.\n", argv[2]);
                return 0;
            }
            CreateList(fp, List);
            SortMyList(List);
            PrintAll(List);
            fclose(fp);
        } else if(argc == 2){
            if(strcmp(argv[1],"sort"))
            {
                fprintf(stderr," the second input should be sort\n");
                return 0;
            }
            fp = stdin;
            CreateList(fp,List);
            SortMyList(List);
            PrintAll(List);
            //printf("%s","wrong file\n");
        }
        else
        {
            fprintf(stderr," num of input is wrong\n");
        }
        return 0;
    }
