#include <stdio.h>

// func to get stack pointer
void *getsp() {
    void *sp;
    asm("mov %%rsp, %0" : " =r"(sp)); // using assembley to fetch the current value of 
    return sp;
}

// nested func
void func3() {
    int local3[100]; // Allocate 400 bytes (assuming 4 bytes per int)
    printf("In func3: Stack pointer = %p\n", getsp()); // getsp() is a function to retrieve the current value of the stack pointer register.
    printf("Size of local3 = %lu bytes\n", sizeof(local3));
}

// nested func2
void func2() {
    double local2[50]; // Allocate 400 bytes (assuming 8 bytes per double)
    printf("In func2: Stack pointer = %p\n", getsp());
    printf("Size of local2 = %lu bytes\n", sizeof(local2));
    func3();
}

// nested func3
void func1() {
    char local1[20]; // Allocate 20 bytes
    printf("In func1: Stack pointer = %p\n", getsp());
    printf("Size of local1 = %lu bytes\n", sizeof(local1));
    func2();
}

// main func
int main() {
    printf("In main: Stack pointer = %p\n", getsp());
    func1();
    return 0;
}
