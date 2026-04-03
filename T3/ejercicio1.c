#include <stdio.h>

int global_var = 10;

void func () {
    int local_var = 20;
    static int static_var = 30;
    local_var ++;
    static_var ++;
    printf("local_var: %d, static_var: %d\n", local_var, static_var);
}

int main() {
    func();
    func();
    return 0;
}