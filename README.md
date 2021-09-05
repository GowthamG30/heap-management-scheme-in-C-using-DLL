# heap-management-scheme-in-C-using-DLL

Heap simulation - DLL

## Assumptions ##
* Using First Fit Allocation Strategy.
* The following program is just the simulation of heap management, but not the actual allocation.
* Two variables with the same name are not allowed. (Appropriate user message is printed)
* Each byte of the whole list is represented with an index (starting with 0 and ending with MAX_END).
* Start and End are the inclusive edge indices of each block (free or allocated).
* An Explicit list is maintained.
* The metadata for the heap block is assumed to be in the allocated memory itself, and won't be specified explicitly.

## Usage ##

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
