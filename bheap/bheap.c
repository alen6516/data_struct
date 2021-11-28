#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 20


typedef struct __bheap {
    int arr[MAX_SIZE];
    int len;
} Bheap;


/**
 * append the new value and rotate
 */
void bheap_add(Bheap *bheap, int val)
{
    bheap->arr[bheap->len++] = val;
}

void bheap_show(Bheap *bheap)
{
    int depth = 0;
    int _len = bheap->len;
    while (_len) {
        depth ++;
        _len = _len >> 1;
    }

    printf("bheap len   = %d\n", bheap->len);
    printf("bheap depth = %d\n", depth);
    
    for (int i=0; i<depth; i++) {
        for (int j=0; j<(1<<i); j++) {
            if ((1<<i)+j < bheap->len) {
                printf("%d, ", bheap->arr[(1<<i)+j]);
            } else {
                break;
            }
        }
        printf("\n");
    }
}

int main (int argc, char *argv[])
{
    srand(time(NULL));
    
    Bheap *bheap = (Bheap*) malloc(sizeof(Bheap));
    bheap->len = 0;

    for (int i=0; i<10; i++) {
        bheap_add(bheap, rand() % 100 +1);
    }

    bheap_show(bheap);
}
