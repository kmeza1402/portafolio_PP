#include <stdio.h>
#include <pthread.h>

int shared_var = 5;

void *modify_variable(void *arg) {
    shared_var += 10;
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, modify_variable, NULL);
    printf("shared_var: %d\n", shared_var);
    return 0;
}