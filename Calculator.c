#include <stdio.h>

void minus(float first_num, float second_num);
void plus(float first_num, float second_num);
void multiply(float first_num, float second_num);
void divide(float first_num, float second_num);

int main() {
    float first_num;
    float second_num;
    char operator;

    printf("Enter the first number: ");
    scanf("%f", &first_num);

    printf("Enter the second number: ");
    scanf("%f", &second_num);

    printf("Enter the operator (+, -, *, /): ");
    scanf(" %c", &operator);

    if (operator == '-') {
        minus(first_num, second_num);
    } else if (operator == '+') {
        plus(first_num, second_num);
    } else if (operator == '*') {
        multiply(first_num, second_num);
    } else if (operator == '/') {
        divide(first_num, second_num);
    } else {
        printf("Invalid operator\n");
    }




    return 0;
}

void minus(float first_num, float second_num) {
    double result = first_num - second_num;
    printf("Result: %f\n", result);
}

void plus(float first_num, float second_num) {
    double result = first_num + second_num;
    printf("Result: %f\n", result);
}

void multiply(float first_num, float second_num) {
    double result = first_num * second_num;
    printf("Result: %f\n", result);
}

void divide(float first_num, float second_num) {
    if (second_num == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return;
    }
    double result = first_num / second_num;
    printf("Result: %f\n", result);
}



