// Gowtham Gorrepati, BT19CSE033, CPL, Assignment 3, 16-03-2021

////////////// ASSUMPTIONS MADE /////////////
/*
    > The following program is just the simulation of heap management, but not the actual allocation.
    > Two variables with the same name are not allowed. (Appropriate user message is printed)
    > Each byte of the whole list is represented with an index (starting with 0 and ending with MAX_END).
    > Start and End are the inclusive edge indices of each block (free or allocated).
    > An Explicit list is maintained.
    > The metadata for the heap block is assumed to be in the allocated memory itself, and won't be specified explicitly.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BT19CSE033_ASSIGNMENT_3_Heap.h"

int main()
{
    heap myHeap;
    heap *myPtr = &myHeap;
	List *nptr = makeFreeNode(0,MAX_END);
    if(nptr == NULL) {
        printf(">>> FAILURE : MAX_END value is too large, no space in Heap.\n");
    }
    else {
        myPtr->lptr = nptr;
    	int flag=0, choose=4, siz=0; // size (in bytes)
    	char vname[NAME_SIZE];
        printf("The total heap space is %d\n", nptr->end-nptr->start+1);
        printf("Please note the following syntax to allocate space and free space respectively,\n");
        printf("Allocate : 2 <variable name> <size (in bytes) you want to allocate>\nFree : 3 <variable name>\n\n");
    	while(flag==0) {
    		printf("\nEnter the respective number as below\n0 - Exit\n1 - Print Lists\n2 - Allocate Space (using first fit method)\n3 - Free Space :\n");
    		scanf("%d", &choose);
            switch(choose) {
                case 0 : flag=1;
                         printf(">>> SUCCESS : Exited!!\n");
                         break;
                case 1 : printLists(myPtr);
                         break;
                case 2 : scanf("%s", vname);
                         scanf("%d", &siz);
                         printf("\n");
                         if(isNamePresent(myPtr, vname))
                             printf(">>> FAILURE : Variable name already exists.\n");
                         else
                            allocateFirstFit(myPtr, siz, vname);
                         break;
                case 3 : scanf("%s", vname);
                    	 printf("\n");
                		 freeSpace(myPtr, vname);
                         break;
                default : printf(">>> FAILURE : Please enter a proper choice\n");
                          break;
            }
    	}
        deleteList(myPtr); // to free space at the end
    }
    return 0;
}
