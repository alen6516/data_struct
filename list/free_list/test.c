#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "list.h"
#include "node.h"

#define P_NUM 10
#define T_NUM 10
#define N_NUM 10

list_t* list;

_Atomic int take_sum = 0;
_Atomic int put_sum = 0;
_Atomic int taken = 0;

_Atomic int _putter_id;
__thread int putter_id;

_Atomic int _taker_id;
__thread int taker_id;

void* putter(void* arg) {
    putter_id = ++ _putter_id;
    printf("putter %d initiated\n", putter_id);
    node_t* node;
    for (int i=0; i<N_NUM; i++) {
        node = node_init();
        node->val = rand() % 10;
        sleep(rand() % 1);
        list_put(list, (void*)node, (void**)&node->next);
        put_sum += node->val;
        printf("putter %d put val %d to list\n", putter_id, node->val);
    }
    printf("putter %d finished\n", putter_id);
    return NULL;
}

void* taker(void* arg) {
    taker_id = ++ _taker_id;
    printf("taker %d initiated\n", taker_id);
    void* out;
    while (taken< P_NUM*N_NUM) {
        sleep(rand() % 1);
        if (taken >= P_NUM * N_NUM) {
            break;
        }
        out = list_take(list, node_get_next, node_link, node_get_ref_of_next);
        if (!out) {
            printf("taker %d take fail\n", taker_id);
            continue;
        }
        printf("taker %d take val = %d\n", taker_id, ((node_t*)out)->val);
        take_sum += ((node_t*)out)->val;
        taken++;
    }

    printf("taker %d finished\n", taker_id);
    return NULL;
}

int main () {

    srand(time(NULL));

    node_t* root = node_init();

    list = list_init((void*)root, node_get_ref_of_next);
    
    pthread_t parr[P_NUM];
    pthread_t tarr[T_NUM];
    for (int i=0; i<P_NUM; i++) {
        pthread_create(&parr[i], NULL, putter, NULL);
    }

    for (int i=0; i<T_NUM; i++) {
        pthread_create(&tarr[i], NULL, taker, NULL);
    }

    for (int i=0; i<T_NUM; i++) {
        pthread_join(tarr[i], NULL);
    }
    printf("sum from taker = %d\n", take_sum);
    printf("sum from putter = %d\n", put_sum);
}

