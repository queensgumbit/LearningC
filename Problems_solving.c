#include <stdio.h>
#include <stdlib.h>
//local stuck allocation




int main(){
    //pointer 
   int age;
   int *ptr;
   ptr = &age;
   age = 70;
   printf("%d \n", *ptr);
   printf("%d \n", age);
   age++;
   printf("%d \n", *ptr);
   *ptr = 60;
   printf("%d \n", age);

   //
    int x = 10;    
    int *ptr = &x; // pointer that has the memory of x 

    printf("ptr = %p\n", ptr);   // shows the memory of x
    printf("*ptr = %d\n", *ptr); // shows the value of X 
    printf("&ptr = %p\n", &ptr); // shows the memory location of the pointer itself


    //malloc and free

    
    int N, i, sum = 0;
    int *a; //pointer to the array
    float average;

    int *ptr = (int *)malloc(5 * sizeof(int)); // Allocates memory for 5 integers
    ptr = (int *)realloc(ptr, 10 * sizeof(int)); // Resizes to hold 10 integers, copies allexisting data to a new memory block
    


 
    printf("Enter the number of elements: ");
    scanf("%d", &N);


    
    a = (int *)malloc(N * sizeof(int));
    if (a == NULL) { //check if we got enough memory
        printf("Memory allocation failed.\n");
        return 1;
    }

    
    printf("Enter the numbers:\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    average = (float)sum / N;
    printf("Average: %.2f\n", average);

    printf("Numbers greater than the average:\n");
    for (i = 0; i < N; i++) {
        if (a[i] > average) {
            printf("%d\n", a[i]);
        }
    }

    //free memory
    free(a);

    return 0;
}



void q1(){
    int n;
    printf("enter factorial num: ");
    scanf("%d",&n);
    for(int i=n;i>=1;i++){
        int result = n * factorial(n - 1);
        printf("the result is %s",result);
       
    }
void example() {
    int a = 10; // Local stack allocation
    printf("Value of a: %d\n", a);
}
//Write a function to calculate the factorial of a number using recursion. Track how local variables are stored during each recursive call.
}

void Heap(){


    //Used for dynamic memory allocation (via malloc, calloc, realloc)
    //The programmer must manage this memory (allocate and free it)
    //Slower but can grow as needed (within system limits)


    int *p = (int *)malloc(sizeof(int)); // Stored in the heap !

}

void LocalStack(){


    //Used for variables with local scope (e.g., inside functions).
    //Memory is automatically allocated and deallocated when the function is called and exited.
    //Fast but limited in size.
    int x = 10; // Stored in the stack


}


void GlobalData(){

    //Advantages of Global Data:Easy to access across different parts of the program.
    // Useful for storing configuration settings or state information shared across functions.
 int GlobalVar = 34;
 //if this global var was outside the function it is a global variable 


}







