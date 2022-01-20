#ifndef ARR_H
#define ARR_H

#define SIZE_OF_ARR(arr) ((int)(sizeof(arr)/sizeof(arr[0])))

static inline void
arr_show(int *arr, int len)
{
    if (!arr || len < 1) return;

    printf("arr = [ %d", arr[0]);
    for (int i=1; i<len; i++) {
        printf(", %d", arr[i]);
    }
    printf("]\n");
}

#endif
