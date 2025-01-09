//
// Created by Hding49 on 2024/12/27.
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

element heap[MAX_ELEMENTS + 1];

#define ELE_EMPTY (element) {INT_MIN}

int last = 1;
int arrayLength = 0;


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


int maxPartner(int i) {
    int j = i + (1 << (int) (floor(log2(i)) - 1));
    if (j > arrayLength) j /= 2;
    return j;
}


int minPartner(int j) {
    return j - (1 << (int) (floor(log2(j)) - 1));
}


bool isMinNode(int i) {
    return i + 1 < 3 * (1 << (int) (floor(log2(i + 1)) - 1));
}


void swim(int i, bool is_min) {
    int item = heap[i].key;

    while (true) {
        if (is_min) {
            if ((i != 1) && item < heap[(i + 1) / 2 - 1].key) {
                heap[i] = heap[(i + 1) / 2 - 1];
                i = (i + 1) / 2 - 1;
            } else {
                break;
            }
        } else {
            if ((i != 2) && item > heap[(i + 1) / 2 - 1].key) {
                heap[i] = heap[(i + 1) / 2 - 1];
                i = (i + 1) / 2 - 1;
            } else {
                break;
            }
        }
    }
    heap[i].key = item;
}


void insert(element data) {
    if (arrayLength == MAX_ELEMENTS) return;

    heap[last] = data;

    if (arrayLength != 0) {
        bool is_min = isMinNode(last);
        int k = is_min ? maxPartner(last + 1) - 1 : minPartner(last + 1) - 1;
        bool condition = is_min ? heap[last].key > heap[k].key : heap[last].key < heap[k].key;
        if (condition) {
            swap(&heap[last], &heap[k], sizeof(heap[last]));
            swim(k, !is_min);
        } else swim(last, is_min);
    }

    last++;
    arrayLength++;
}


element delete(bool is_min) {
    int target;
    if (is_min) {
        if (arrayLength == 0) return ELE_EMPTY;
        target = 1;
    } else {
        if (arrayLength < 2) return ELE_EMPTY;
        target = 2;
    }
    element item = heap[target];
    int child = (target + 1) * 2 - 1;
    while (child <= arrayLength) {
        if (child < arrayLength) {
            bool condition = is_min ? (heap[child].key > heap[child + 1].key) : (heap[child].key < heap[child + 1].key);
            child = condition ? child + 1 : child;
        }

        heap[target] = heap[child];
        target = child;
        child = (child + 1) * 2 - 1;
    }

    heap[target] = heap[arrayLength];
    last--;
    arrayLength--;
    int k = is_min ? maxPartner(target + 1) - 1 : minPartner(target + 1) - 1;
    bool condition = is_min ? heap[target].key > heap[k].key : heap[target].key < heap[k].key;
    if (condition) {
        swap(&heap[target], &heap[k], sizeof(heap[target]));
        swim(k, !is_min);
    } else swim(target, is_min);
    return item;
}


element deleteMin() {
    return delete(true);
}


element deleteMax() {
    return delete(false);
}



void printLevelOrder() {
    if (arrayLength == 0) return;
    for (int i = 1; i <= arrayLength; i++) {
        printf("%d ", heap[i].key);
    }
    printf("\n");
}
int main() {
    char command[20];
    printf("Commands:\n");
    printf("insert <key>: Insert a key into the heap\n");
    printf("deleteMin: Delete the minimum element\n");
    printf("deleteMax: Delete the maximum element\n");
    printf("print: Print the heap in level order\n");
    printf("exit: Exit the program\n");

    while (true) {
        printf("Enter command: ");
        scanf("%s", command);

        if (strcmp(command, "insert") == 0) {
            int key;
            scanf("%d", &key);
            insert(createData(key));
            printf("Inserted %d into the heap.\n", key);
        } else if (strcmp(command, "deleteMin") == 0) {
            element minElement = deleteMin();
            if (minElement.key == INT_MIN) {
                printf("Heap is empty. Cannot delete min.\n");
            } else {
                printf("Deleted Min: %d\n", minElement.key);
            }
        } else if (strcmp(command, "deleteMax") == 0) {
            element maxElement = deleteMax();
            if (maxElement.key == INT_MIN) {
                printf("Heap is empty. Cannot delete max.\n");
            } else {
                printf("Deleted Max: %d\n", maxElement.key);
            }
        } else if (strcmp(command, "print") == 0) {
            printf("Heap in Level Order: ");
            printLevelOrder();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting program.\n");
            return 0;
        } else {
            printf("Invalid command. Please try again.\n");
        }
    }

    return 0;
}
