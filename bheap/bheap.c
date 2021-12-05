#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_SIZE 20
#define IS_ODD(val) ((val) & 0x1)

#define SWAP(a, b) ({   \
    if ((a) != (b)) {   \
        (a) = (a)^(b);  \
        (b) = (a)^(b);  \
        (a) = (a)^(b);  \
    }                   \
})

typedef struct __bheap {
    int arr[MAX_SIZE];
    int len;
} Bheap;

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
            if ((1<<i)+j-1 < bheap->len) {
                printf("%d, ", bheap->arr[(1<<i)+j-1]);
            } else {
                break;
            }
        }
        printf("\n");
    }
}

/**
 * bubble the tail up to the right place
 */
static void bheap_bottomup(Bheap *bheap)
{
    if (!bheap || bheap->len < 2) return;

    int curr_idx = bheap->len-1;
    int parent_idx;
    do {
        if (IS_ODD(curr_idx)) {
            parent_idx = (curr_idx-1) >> 1;
        } else {
            parent_idx = (curr_idx-2) >> 1;
        }

        if (bheap->arr[parent_idx] < bheap->arr[curr_idx]) {
            SWAP(bheap->arr[parent_idx], bheap->arr[curr_idx]);
        }

        curr_idx = parent_idx;
    } while (curr_idx != 0);
}

/**
 * append the new value and bubble it up
 */
void bheap_add(Bheap *bheap, int val)
{
    bheap->arr[bheap->len++] = val;
    bheap_bottomup(bheap);
}

/**
 * compare parent with children
 * exchange if one of the children is larger
 */
static void bheap_topdown(Bheap *bheap)
{
    if (!bheap || !bheap->len) return;

    int curr_idx = 0;
    int child1_idx, child2_idx;
    child1_idx = (curr_idx << 1) + 1;
    child2_idx = (curr_idx << 1) + 2;

    while (child1_idx < bheap->len || child2_idx < bheap->len) {
        if (child2_idx < bheap->len && bheap->arr[child2_idx] > bheap->arr[child1_idx]) {
            // child2 is max
            SWAP(bheap->arr[curr_idx], bheap->arr[child2_idx]);
            curr_idx = child2_idx;
            child1_idx = (curr_idx << 1) + 1;
            child2_idx = (curr_idx << 1) + 2;

        } else if (bheap->arr[child1_idx] > bheap->arr[curr_idx]) {
            // child1 is max
            SWAP(bheap->arr[curr_idx], bheap->arr[child1_idx]);
            curr_idx = child1_idx;
            child1_idx = (curr_idx << 1) + 1;
            child2_idx = (curr_idx << 1) + 2;

        } else {
            // curr is not smaller than children
            break;
        }
    }
}

/**
 * move the tail to the top and do beheap topdown
 */
int bheap_pop(Bheap *bheap)
{
    if (!bheap || !bheap->len) return -1;

    int ret = bheap->arr[0];
    bheap->arr[0] = bheap->arr[bheap->len-1];
    bheap->len --;

    bheap_topdown(bheap);
    return ret;
}

int main (int argc, char *argv[])
{
    srand(time(NULL));
    
    int len = MAX_SIZE;
    if (argc == 2) {
        len = strtol(argv[1], NULL, 10);
        if (len > MAX_SIZE) {
            len = MAX_SIZE;
        }
    }

    /* arr to show the number before/after sorting */
    int *arr_pre = (int*) malloc(sizeof(int)*len);
    int *arr_post = (int*) malloc(sizeof(int)*len);

    Bheap *bheap = (Bheap*) malloc(sizeof(Bheap));
    bheap->len = 0;

    /* init bheap and store to arr_pre */
    for (int i=0; i<len; i++) {
        arr_pre[i] = (rand() % 100 + 1);
        bheap_add(bheap, arr_pre[i]);
    }
    bheap_show(bheap);

    /* pop the bheap and store to arr_post */
    for (int i=0; bheap->len; i++) {
        printf("=================\n");
        arr_post[i] = bheap_pop(bheap);
        printf("pop: %d\n", arr_post[i]);
        bheap_show(bheap);
    }

    /* show array */
    printf("arr_pre = [ %d", arr_pre[0]);
    for (int i=1; i<len; i++) {
        printf(", %d", arr_pre[i]);
    }
    printf("]\n");

    printf("arr_pos = [ %d", arr_post[0]);
    for (int i=1; i<len; i++) {
        printf(", %d", arr_post[i]);
    }
    printf("]\n");
}
