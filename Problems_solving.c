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













