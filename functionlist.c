#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <sys/time.h>
//#include <sys/stat.h>
#include <locale.h>
#include <math.h>
#include "cs402.h"
#include "my402list.h"
#include "functionlist.h"

#define tooLarge "?,???,???.??"


double balance = 0;
int num_line = 0;

void AddNewNode(char *buf, My402List *List);

/*********exit**********/
void ExitAll(char * message,int num_line)
{
    if(num_line == 0)
        fprintf(stderr, "%s\n", message);
    else
        fprintf(stderr, "%s line: %d\n", message, num_line);
    getchar();
    exit(0);
}

/*************createlist**************/
void CreateList(FILE *fp, My402List *List)
{
    char buf[1027];

    while(fgets(buf, sizeof(buf), fp) != NULL)
     {
        //printf("%d\n",num_line);
        /* buf may contain '\n' */
        //check length
        if(strlen(buf) > 1024)
            ExitAll(" format err: the line is too long",0);//exit
        //create new node~(success not sure)

        AddNewNode(buf, List);

        //My402ListElem *test;
        //test = My402ListLast(List);

        //printf("%s%d%s%s\n", ((My402ListElemObj*)test->obj)->TSign,((My402ListElemObj*)test->obj)->TTime,((My402ListElemObj*)test->obj)->TAm,((My402ListElemObj*)test->obj)->TDesc);

        //printf("the length of my402list is %d\n", My402ListLength(List));
        //printf("it is empty? %d\n", My402ListEmpty(List));
        //printf("%s", buf);
    }
}

void AddNewNode(char *buf, My402List *List){
    num_line++;
    My402ListElemObj *NewObj;
    NewObj = (My402ListElemObj*)malloc(sizeof(My402ListElemObj));
   /*parse & judge the context of buf*/
   //parsing text input
   char *start_ptr=buf;
   //char *ptr_addr[4];
   char *tab_ptr = strchr(start_ptr, '\t');
   //int countT=0;
   //ptr_addr[countT] = buf;
   char *toomanyfield;

   if(tab_ptr!=NULL)
   {
        *tab_ptr++= '\0';
        //countT++;
        //if(countT>3)
        //    ExitAll("format of this line is incorrect",0);//exit
        //ptr_addr[countT] = tab_ptr;
        NewObj->TSign = (char *)malloc(sizeof(char)*2);
        strncpy(NewObj->TSign,start_ptr,1);

        if(*(NewObj->TSign) !='-' && *(NewObj->TSign) !='+')
            ExitAll(" cannot caculate with wrong symbol ",num_line);

        //printf("%s",NewObj->TSign);

        start_ptr=tab_ptr;//can delete
        tab_ptr = strchr(start_ptr, '\t');
    }
    else
    {
        ExitAll(" the format is wrong ",num_line);
    }
    if(tab_ptr!=NULL)
    {
        *tab_ptr++= '\0';
        //countT++;
        //if(countT>3)
        //    ExitAll("format of this line is incorrect",0);//exit
        //ptr_addr[countT] = tab_ptr;
        NewObj->TTime = atol(start_ptr);

        if(NewObj->TTime > time(NULL))
            ExitAll(" time is over the current time ",num_line);
        //printf("%d\n",NewObj->TTime);

        start_ptr=tab_ptr;//can delete
        tab_ptr = strchr(start_ptr, '\t');
    }
    else
    {
        ExitAll(" the format is wrong ",num_line);
    }
    if(tab_ptr!=NULL)
    {
        *tab_ptr++= '\0';
        //countT++;
        //if(countT>3)
        //    ExitAll("format of this line is incorrect",0);//exit
        //ptr_addr[countT] = tab_ptr;
        char *toomanydecimal = strchr(start_ptr,'.');
        if(strlen(toomanydecimal)>3)
        {
            ExitAll(" too many decimal ",num_line);
        }
        NewObj->TAm =(char *)malloc(sizeof(char)*11);
        strncpy(NewObj->TAm,start_ptr,10);

        //printf("%s\n",NewObj->TAm);

        start_ptr=tab_ptr;//can delete
        tab_ptr = strchr(start_ptr, '\n');
        toomanyfield=strchr(start_ptr, '\t');
    }
    else
    {
        ExitAll(" the format is wrong ",num_line);
    }
    if(toomanyfield!=NULL)
    {
        ExitAll(" too many field ",num_line);
    }
    if(tab_ptr!=NULL)
    {
        *tab_ptr= '\0';
        while(*start_ptr == ' ')
        {
            start_ptr++;
        }
        //countT++;
        //if(countT>3)
        //    ExitAll("format of this line is incorrect",0);//exit
        //ptr_addr[countT] = tab_ptr;
        NewObj->TDesc = (char *)malloc(sizeof(char)*25);
        strncpy(NewObj->TDesc,start_ptr,24);

        //printf("%s\n", NewObj->TDesc);

        //start_ptr=tab_ptr;//can delete
        //tab_ptr = strchr(start_ptr, '\t');
    }
    else
    {
        ExitAll(" the format is wrong ",num_line);
    }

    /*check every part*/

   /*add new obj*/
   //malloc & initial new node
   //NewObj = (My402ListElemObj*)malloc(sizeof(My402ListElemObj));
   //strcpy(NewObj->TSign,ptr_addr[0]);
   //NewObj->TTime = atol(ptr_addr[1]);
   //strcpy(NewObj->TAm,ptr_addr[2]);
   //strcpy(NewObj->TDesc,ptr_addr[3]);
   //add new node to list
   int ToF;
   ToF = My402ListAppend(List, NewObj); //void* with My402ListElemObj*
   if(ToF == 0)
    ExitAll("A node cannot be added when initial the list",0);//exit~
}
/*********************************************/

/*****************sort***************************************/
void SortMyList(My402List *List)
{
    /*test the list
    My402ListElem *test;
    test = My402ListFirst(List);
    if(test == List->anchor.next)
    printf("%s\n","good1");
    while(test != NULL)
    {
        if(test->next==My402ListNext(List,test))
        {
            printf("%s\n","good2");

        }
        printf("%d\n",((My402ListElemObj*)test->obj)->TTime);
        //if(test == NULL)
        //printf("%s","good3");
        test = My402ListNext(List,test);

    }
    if(List->anchor.prev == My402ListLast(List))
    printf("%s","good");
    */

    My402ListElemObj *temp1, *temp2;
    My402ListElem *elem1, *elem2;
    //if(My402ListEmpty(List))
        //exit~
    elem1=My402ListFirst(List);
    while(elem1 != NULL)
    {
        elem2 = My402ListNext(List, elem1);
        while(elem2 != NULL)
        {
            temp1 = (My402ListElemObj*)elem1->obj;
            temp2 = (My402ListElemObj*)elem2->obj;
            if(temp1->TTime > temp2->TTime)
            {
                elem1->obj = temp2;
                elem2->obj = temp1;
            }
            if(temp1->TTime == temp2->TTime)
                ExitAll(" there are 2 time with the same value ",0);
            //exit~
            elem2 = My402ListNext(List, elem2);
            //if(elem2 != NULL)
            //printf("%d\n", ((My402ListElemObj*)elem2->obj)->TTime);
        }
        elem1 = My402ListNext(List, elem1);
    }

    /*//test
    My402ListElem *test = My402ListFirst(List);
    while(test != NULL)
    {
        printf("%d\n", ((My402ListElemObj*)test->obj)->TTime);
        test=My402ListNext(List,test);
    }
    */

}
/***************************************************************/
/***************************print**********************************/

char *read_num(char *amount);
void print_TTime(time_t *timep);
void print_TAm(char * amonut, char *sgn);
void print_bal(char *amonut, char *AoM);

void PrintAll(My402List *List)
{
    printf("+-----------------+--------------------------+----------------+----------------+\n");
    printf("|       Date      | Description              |         Amount |        Balance |\n");
    printf("+-----------------+--------------------------+----------------+----------------+\n");
    My402ListElem *toPrint = My402ListFirst(List);
    while(toPrint != NULL)
    {
        My402ListElemObj *Pnt = (My402ListElemObj*)toPrint->obj;
        printf("|");
        time_t *timep = &(Pnt->TTime);
        print_TTime(timep);
        printf("|");

        printf(" %-24s ", Pnt->TDesc);
        printf("|");

        print_TAm(Pnt->TAm, Pnt->TSign);
        printf("|");

        print_bal(Pnt->TAm,Pnt->TSign);

        printf("|\n");
        //nextone;

        toPrint = My402ListNext(List,toPrint);

    }
    printf("+-----------------+--------------------------+----------------+----------------+\n");
}


char *read_num(char *amount)
{
    int numLength =strlen(amount);
    int numoutlen;
    if(numLength <= 6)
        //numoutlen = numLength;
        return amount;
    else if (numLength <= 9)
        numoutlen = numLength+1;
    else
        numoutlen = numLength+2;
    char *outnum= (char *)malloc(numoutlen+1);
    char *last = amount+(numLength-1);
    char *outLast = outnum+(numoutlen-1);
        *(outLast+1)='\0';
    int i=0;
    for(i=0;i < numLength;i++)
    {
        if(i>3 && (i-3)%3 == 0)
        {
            *outLast=',';
            outLast--;
        }
        *outLast=*last;
        last--;
        outLast--;
        //printf("%s\n",last);

    }
    return outnum;

}
void print_TTime(time_t *timep)
{
    char * timestring = ctime(timep);
    //divide timestring
    char day[4],mon[4],date[3],year[5];
    sscanf(timestring,"%[^ ] %[^ ] %[^ ] %*[^ ] %s",day,mon,date,year);
    if(atoi(date)<10)
        printf("%s%s%s%s%s%s%s%s%s"," ",day," ",mon,"  ",date," ",year," ");
    else
        printf("%s%s%s%s%s%s%s%s%s"," ",day," ",mon," ",date," ",year," ");
    //char outtime[3+3+2+4+3+1];
}
void print_TAm(char *amount, char *sgn)
{
    char *print_amount = read_num(amount);
    if(*sgn == '-')
        printf(" (%12s) ", print_amount);
    else
        printf("  %12s  ", print_amount);

}

void print_bal(char *amount, char *AoM)
{
    //printf("%s\n",amount);
    //double a=atof(amount)*100;
    double a=atof(amount);
    //printf("%f\n",a);
    //long long amounttobal =(long long) (a/1);
    //printf("%llu\n",amounttobal);
    if(*AoM == '-')
        //balance=balance - amounttobal;
        balance=balance - a;
    else
        //balance=balance + amounttobal;
        balance=balance + a;

    if(balance > 1000000000)
    {
        char *Large = tooLarge;
        //if(balance < 0)
        //    printf(" (%s) ", Large);
        if(balance > 0)
            printf("  %s  ", Large);
    }
    else if(balance < -1000000000)
    {
        char *Large = tooLarge;
        printf(" (%s) ", Large);
    }
    else
    {
        //double printBalance = (double)balance/100;
        char tochange[14];
        char *toprint;
        //char printsign;
        if(balance <0)
        {
            //printBalance=balance*(-1);
            //printsign = '-';
            //sprintf(tochange,"%llu.%02llu",(balance*(-1))/100,(balance*(-1))%100);
            sprintf(tochange,"%.2f",balance*(-1));
            toprint=read_num(tochange);
            printf(" (%12s) ", toprint);
        }
        else
        {
            //printsign = '+';
            //sprintf(tochange,"%llu.%02llu",balance/100,balance%100);
            sprintf(tochange,"%.2f",balance);
            toprint=read_num(tochange);
            printf("  %12s  ", toprint);
        }
    }

}

