#include <stdio.h>

int main() {

    char characterName[] = "John"; //use [] to show that we want to styore more than 1 char
    const characterAge  = 35; //theres int and double/float. const sais that cannot modify thge varible
    printf("his name is %s \n", characterName); //%s its place holder for string
    printf("he was %d years old",characterAge);//%d place holder for int
    printf("\n %d",16); //to print a number need to use %d
    printf("\n my fav character %s he is %f ", "sherlock",34.3); //%f to enter float num
    printf("you can use math operators %f",4.5+5.8 /3 *23 );
    int age;
    printf("enter your fav characters age: ");
    scanf("%d", &age); //storing the input inside the variable age
    char name[20];
    printf("enter your name: "); //scanf gets only the text till the space
    fgets(name,20, stdin); //alternative to scanf-takes all the line
    printf("your name is %s", name);


    //array
    int numbers[] = {4,8,15,24};
    printf("%d", numbers[3]); // [] index in an array

    int numbers2[10]; //tell that till array has 10 elements
    numbers2[3] = 45;
    printf("%d",numbers2[3]); //43
    hello("yasmin",14); //calling teh fuinction this way 

    //switch

    char grade = 'A';
    switch (grade){
    case 'A':
        printf("you did great!");
        break;
    case 'B':
        printf("you did ok");
        break;
    case 'C':
        printf("you did poorly! ");
        break;
    default:
        printf("invalid grade");
        
    //structs - similar to a dictionary

    struct student{
        char name[50];
        char major[50];
        int age;
        double gpa;
    };

    struct student student1;
    student1.age = 22;
    student1.gpa = 3.8;
    strcpy(student1.name, "ella"); //strcpy used to store strings inside structs
    
    //while loops

    int index =1;
    while(index<=5){
        printf("the index is %d",index);
    }

    //for loops
    int i = 1;
    for(i =1; i<=5;i++){
        printf("the num is %d /n", i);
    }

    // memory addresses and pointers

    int Age = 30;
    double gpa = 3.4;
    printf("age: %p/n gpa: %p", &Age,&gpa); //this will print out the memory adress of age. -> p stands for pointer - point where the data is stored

    int * pAge = &age; //this is how to create a pointer variable - storing the memory adress of age

    // dereferance a pointer

    printf("%d", *pAge); //output: 30
    //to get the memory adress
    printf("%d", &Age);



    return 0;
}

//function
//void sais that the function is not returning any value
void hello(char name[], int age)
{
    printf("hello %s, you are %d years old", name, age);
    //if statements
    if(name =="yasmin" && age == 16){
        printf("yesssss");
    }
    else if(name=="jon" || name=="karin"){
        printf("nice");
    }
    else{
        printf("ok");
    }
    
}

}

