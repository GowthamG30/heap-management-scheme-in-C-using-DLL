// Gowtham Gorrepati, BT19CSE033, CPL, Assignment 3, Declarations, 16-03-2021

#define MAX_END 999
#define NAME_SIZE 100 // name without spaces

typedef enum{FAILURE, SUCCESS} statusCode;
typedef struct ListTag
{
    int start;
    int end;
    char vName[NAME_SIZE]; // name of variable to allocate memory
    struct ListTag *next;
    struct ListTag *prev;
    int isFree;
} List;
typedef struct heapTag
{
    List *lptr;
} heap;

List *makeAllocatedNode(int start, int end, char name[]);
List *makeFreeNode(int start, int end);

int isListFull(heap *hp);
int isListEmpty(heap *hp);
int isNamePresent(heap *hp, char name[]);

void allocateFirstFit(heap *hp, int siz, char name[]);
void freeSpace(heap *hp, char name[]);

void printAllocList(heap *hp);
void printFreeList(heap *hp);
void printLists(heap *hp);

void deleteList(heap *hp);
