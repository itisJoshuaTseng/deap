//
// Created by Hding49 on 2025/1/3.
//


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<limits.h>


#define MAX_ELEMENTS 50

typedef struct element {
    int key;
} element;

element heap[MAX_ELEMENTS];

#define ELE_EMPTY (element) {INT_MIN}

int n = 0;


void swap(void * a, void * b, size_t size) {
    void * temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}


element createData(int key) {
    element e;
    e.key = key;
    return e;
}


int isMinLevel(int i) {
    return (int) (floor(log2(i))) % 2 == 0;
}


void verifyMinMax(int p, element e, bool is_min) {
    int gp = p / 4;
    while (gp != 0) {
        bool condition = is_min ? e.key < heap[gp].key : e.key > heap[gp].key;
        if (condition) {
            heap[p] = heap[gp];
            p = gp;
            gp /= 4;
        } else {
            gp = 0;
        }
    }
    heap[p] = e;
}


void insert(element e) {
    int p;
    if (n == MAX_ELEMENTS - 1) return;

    n++;
    p = n / 2;

    if (p == 0) heap[1] = e;
    else {
        if (isMinLevel(p)) {
            if (e.key < heap[p].key) {
                heap[n] = heap[p];
                verifyMinMax(p, e, true);
            } else verifyMinMax(n, e, false);
        } else {
            if (e.key > heap[p].key) {
                heap[n] = heap[p];
                verifyMinMax(p, e, false);
            } else verifyMinMax(n, e, true);
        }
    }
}


int findChildGrandChild(int i, bool is_min) {
    int k = i * 2;
    if (k > n) return -1;
    if (k + 1 <= n) {
        bool condition = is_min ? heap[k].key > heap[k + 1].key : heap[k].key < heap[k + 1].key;
        k = condition ? k + 1 : k;
    }
    if (i * 4 <= n) {
        for (int j = i * 4; j <= n && j < i * 8; j++) {
            bool condition = is_min ? heap[k].key > heap[j].key : heap[k].key < heap[j].key;
            k = condition ? j : k;
        }
    }
    return k;
}


void delete(element * e, bool is_min) {
    int i, j, k, p;
    element x, t;
    bool not_done;
    if (n == 0) return;

    *e = heap[1];
    x = heap[n];
    n--;
    not_done = true;
    i = 1;
    j = n / 2;

    while (not_done && i <= j) {
        if ((k = findChildGrandChild(i, is_min)) == -1) break;
        if (x.key <= heap[k].key) not_done = false;
        else {
            heap[i] = heap[k];
            if (k <= 2 * i + 1) {
                not_done = false;
            } else {
                p = k / 2;
                if (x.key > heap[p].key) {
                    t = heap[p];
                    heap[p] = x;
                    x = t;
                }
            }
            i = k;
        }
    }
    heap[i] = x;
}


void printHeap() {
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
}



int main() {
//    int array[] = {7, 70, 40, 30, 9, 10, 15, 45, 50, 30, 20, 12};

    int array[] = {5, 30, 26, 10, 16, 20, 28, 12, 14, 25, 21, 22};

    for (int i = 0; i < 12; i++) {
        heap[++n].key = array[i];
    }

    printHeap();

    element e;
    delete(&e, true);

    printHeap();

}