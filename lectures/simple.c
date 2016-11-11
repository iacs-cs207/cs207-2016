#include <stdlib.h>
#include <stdio.h>

int* just_a_func(){
    int *heapintlist;
    int i;
    int stackintlist[3]; /*Allocate in this functions frame on stack*/
    heapintlist = (int *) malloc(3*sizeof(int)); /*Allocate on heap*/
    for (i = 0; i < 3; i++) {
        stackintlist[i] = i;
        heapintlist[i] =i;
    }
    for (i = 0; i < 3; i++) {
        printf("stackintlist %d\n",stackintlist[i]);
        printf("heapintlist %d :  %d\n", i, heapintlist[i]);
    }
    return heapintlist; /*stackintlist unallocated here */
}
int main() {
    int* heapintlist;
    int i;
    
    heapintlist=just_a_func();
    for (i = 0; i < 3; i++) {
        heapintlist[i] =i+5;
        printf("heapintlist %d :  %d\n", i, heapintlist[i]);
    }
    free(heapintlist);
    /* garbage in &heapinlist[i] after this */
}