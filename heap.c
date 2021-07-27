// Gowtham Gorrepati

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BT19CSE033_ASSIGNMENT_3_Heap.h"

List *makeAllocatedNode(int start, int end, char name[])
{
    List *nptr;
	nptr = (List*)malloc(sizeof(List));
    if(nptr!=NULL) {
        nptr->start = start;
    	nptr->end = end;
    	strcpy(nptr->vName, name);
        nptr->isFree = 0;
    	nptr->next = NULL;
        nptr->prev = NULL;
    }
	return nptr;
}

List *makeFreeNode(int start, int end)
{
    List *nptr;
    nptr = (List*)malloc(sizeof(List));
    if(nptr!=NULL) {
        nptr->start = start;
        nptr->end = end;
        nptr->isFree = 1;
        nptr->next = NULL;
        nptr->prev = NULL;
    }
    return nptr;
}

int isListFull(heap *hp)
{
    int retVal = 1;
    List *lptr = hp->lptr;
    while(lptr!=NULL && !(lptr->isFree)) {
        lptr = lptr->next;
    }
    if(lptr!=NULL)
        retVal=0;
    return retVal;
}

int isListEmpty(heap *hp)
{
    int retVal = 1;
    List *lptr = hp->lptr;
    while(lptr!=NULL && lptr->isFree) {
        lptr = lptr->next;
    }
    if(lptr!=NULL)
        retVal=0;
    return retVal;
}

int isNamePresent(heap *hp, char name[])
{
    List *lptr = hp->lptr;
    int retVal = 0;
    while(lptr!=NULL) {
        if(!(lptr->isFree) && strcmp(name, lptr->vName)==0)
            retVal = 1;
        lptr = lptr->next;
    }
    return retVal;
}

void allocateFirstFit(heap *hp, int siz, char name[])
{
    List *lptr = hp->lptr;
    if(lptr == NULL) {
        printf(">>> FAILURE : No free space is created.\n");
    }
    else {
        List *nptr = lptr, *ptr = NULL;
        int done = 0;
        while(nptr!=NULL && !done) {
            if(nptr->isFree && (nptr->end - nptr->start + 1) >= siz) {
                ptr = nptr;
                done = 1;
            }
            nptr = nptr->next;
        }
        int index;
        if(ptr!=NULL) index = ptr->start + siz -1;
        if(ptr == NULL || ( ptr->next==NULL && (index > MAX_END) ) ) {
            printf(">>> FAILURE : No free space is available.\n");
        }
        else {
            List *aptr = makeAllocatedNode(ptr->start, index, name);
            if(aptr==NULL) {
                printf(">>> FAILURE : Heap is full.\n");
            }
            else {
                if(index == ptr->end) {
                    lptr = aptr;
                    if(ptr->prev!=NULL) {
                        ptr->prev->next = lptr;
                        lptr->prev = ptr->prev;
                    }
                    if(ptr->next!=NULL) {
                        ptr->next->prev = lptr;
                        lptr->next = ptr->next;
                    }
                    free(ptr);
                }
                else {
                    ptr->start = index+1;
                    lptr = aptr;
                    if(ptr->prev!=NULL) {
                        ptr->prev->next = lptr;
                        lptr->prev = ptr->prev;
                    }
                    lptr->next = ptr;
                    ptr->prev = lptr;
                }
                printf(">>> SUCCESS : Space is allocated.\n");
                while(lptr->prev != NULL) {
                    lptr = lptr->prev;
                }
                hp->lptr = lptr;
            }
        }
    }
}

void freeSpace(heap *hp, char name[])
{
    List *lptr = hp->lptr, *aptr = NULL;
    if(isListEmpty(hp)) {
        printf(">>> FAILURE : No space is allocated.\n");
    }
    else {
        int done = 0;
        while (lptr!=NULL && !done) {
            if(!(lptr->isFree) && strcmp(name,lptr->vName)==0) {
                aptr = lptr;
                done = 1;
            }
            lptr = lptr->next;
        }
        if(aptr==NULL) {
            printf(">>> FAILURE : There is no element with the given variable name.\n");
        }
        else {
            List *ptr;
            aptr->isFree = 1;
            if(aptr->prev!=NULL && aptr->prev->isFree) {
                ptr = aptr->prev;
                aptr->start = ptr->start;
                if(ptr->prev != NULL) ptr->prev->next = aptr;
                aptr->prev = ptr->prev;
                free(ptr);
            }
            if(aptr->next!=NULL && aptr->next->isFree) {
                ptr = aptr->next;
                aptr->end = ptr->end;
                if(ptr->next != NULL) ptr->next->prev = aptr;
                aptr->next = ptr->next;
                free(ptr);
            }
            lptr = aptr;
            while(lptr->prev != NULL) {
                lptr = lptr->prev;
            }
            printf(">>> SUCCESS : Space is freed.\n");
            hp->lptr = lptr;
        }
    }
}

void printAllocList(heap *hp)
{
    if(isListEmpty(hp)) {
        printf("No allocated space.\n");
    }
    else {
        List *ptr = hp->lptr;
        printf("Start\t\tEnd\t\tSize\t\tVariableName\n");
		while(ptr!=NULL) {
			if(!(ptr->isFree))
				printf("%d\t\t%d\t\t%d\t\t%s\n", ptr->start, ptr->end, ptr->end-ptr->start+1, ptr->vName);
			ptr = ptr->next;
		}
    }
}

void printFreeList(heap *hp)
{
    if(isListFull(hp)) {
        printf("No free space.\n");
    }
    else {
        List *ptr = hp->lptr;
        printf("Start\t\tEnd\t\tSize\n");
		while(ptr!=NULL) {
			if(ptr->isFree)
				printf("%d\t\t%d\t\t%d\n", ptr->start, ptr->end, ptr->end-ptr->start+1);
			ptr = ptr->next;
		}
    }
}

void printLists(heap *hp)
{
    printf("\n>>> SUCCESS :\n");
    printf("---------------------------------------------------------------");
    printf("\nAllocated list is : \n");
    printAllocList(hp);
    printf("---------------------------------------------------------------");
    printf("\nFree list is : \n");
    printFreeList(hp);
    printf("---------------------------------------------------------------");
    printf("\n");
}

void deleteList(heap *hp)
{
    List *ptr;
    ptr = hp->lptr;
    while(hp->lptr!=NULL) {
        ptr = hp->lptr;
        hp->lptr = hp->lptr->next;
        free(ptr);
    }
    hp->lptr = NULL;
}
