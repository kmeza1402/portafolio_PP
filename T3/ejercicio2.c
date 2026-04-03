#include <stdio.h>
#include <stdlib.h>

void allocate_memory() {
    int *arr = (int *)malloc(5*sizeof(int));
    for (int i = 0; i < 5; i++) {
    arr[i] = i * 2;
    }   
    printf("arr[2]: %d\n", arr[2]);
}

int main() {
    allocate_memory();
    return 0;
}