#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct _LIST_ENTRY {
  struct _LIST_ENTRY *Flink;
  struct _LIST_ENTRY *Blink;
} LIST_ENTRY, *PLIST_ENTRY, PRLIST_ENTRY;

#define CONTAINING_RECORD(address, type, field) (\
    (type *)((char*)(address) -(unsigned long)(&((type *)0)->field))) 
    //so we need this to calculate the start adress of the struct - the adrees of List_Entry, in order to access a member of the struct


void InitializeListHead( PLIST_ENTRY ListHead)
 {
   ListHead->Flink = ListHead->Blink = ListHead;
 }


 void InsertHeadList( PLIST_ENTRY ListHead, PLIST_ENTRY Entry)
{
    PLIST_ENTRY Flink;

    Flink = ListHead->Flink;
    Entry->Flink = Flink;
    Entry->Blink = ListHead;
    Flink->Blink = Entry;
    ListHead->Flink = Entry;
}

_Must_inspect_result_
bool FORCEINLINE
IsListEmpty(_In_ const LIST_ENTRY * ListHead)          
{
    return (BOOLEAN)(ListHead->Flink == ListHead);
}

FORCEINLINE
BOOLEAN RemoveEntryListUnsafe(_In_ PLIST_ENTRY Entry)
{
    PLIST_ENTRY Blink;
    PLIST_ENTRY Flink;

    Flink = Entry->Flink;
    Blink = Entry->Blink;
    Blink->Flink = Flink;
    Flink->Blink = Blink;
    return (BOOLEAN)(Flink == Blink);
}

typedef struct Cow {
    LIST_ENTRY ListEntry;   
    char name[50];
    int liters_produced;
    int gr_eaten;
   
} Cow;

typedef struct Chicken {
    LIST_ENTRY ListEntry;   
    char name[50];
    int eggs_layed;
    int gr_eaten;
    
} Chicken;

typedef struct {
    LIST_ENTRY CowList;     
    LIST_ENTRY ChickenList;
    char name[50];
    int cow_count;
    int chicken_count;
    float income;
    
} Farm;







Cow* add_cow(Farm *farm, const char *name);
Chicken* add_chicken(Farm *farm, const char *name);
void remove_cow(Farm *farm, const char *name);
void remove_chicken(Farm *farm, const char *name);
void milk_cow(Cow *cow, int liters);
void collect_eggs(Chicken *chicken, int eggs);
void display_farm(Farm *farm);

// add cow to a farm
Cow* add_cow(Farm *farm, const char *name) {
    Cow *new_cow = (Cow *)malloc(sizeof(Cow));
    if (!new_cow) {
        printf("Memory allocation failed for cow.\n");
        return NULL;
    }

    strcpy(new_cow->name, name);
    new_cow->liters_produced = 0;
    new_cow->gr_eaten = 0;
    new_cow->ListEntry.Flink = farm->CowList.Flink;
    new_cow->ListEntry.Blink = &farm->CowList;

    if (farm->CowList) {
        farm->CowList->ListEntry.Blink = new_cow;
    }
    
    InsertHeadList(&farm->CowList, &new_cow->ListEntry);

    farm->CowList = new_cow;
    farm->cow_count++;
    return new_cow;
}

//add a chicken to the farm
Chicken* add_chicken(Farm *farm, const char *name) {
    Chicken *new_chicken = (Chicken *)malloc(sizeof(Chicken));
    if (!new_chicken) {
        printf("Memory allocation failed for chicken.\n");
        return NULL;
    }

    strcpy(new_chicken->name, name);
    new_chicken->eggs_layed = 0;
    new_chicken->gr_eaten = 0;
    new_chicken->ListEntry.Flink = farm->ChickenList.Flink;
    new_chicken->ListEntry.Blink = &farm->ChickenList.Blink;

    if (farm->ChickenList) {
        farm->ChickenList->ListEntry.Blink = new_chicken;
    }
    
    InsertHeadList(&farm->ChickenList, &new_chicken->ListEntry);
   
    farm->ChickenList = new_chicken;
    farm->chicken_count++;
    return new_chicken;
}

//remove a cow from the farm(by name)
void remove_cow(Farm *farm, const char *name) {
    Cow *current = farm->CowList;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (current->ListEntry.Blink) {
                current->ListEntry.Blink->Flink = current->ListEntry.Flink;
            } else {
                farm->CowList = current->ListEntry.Flink; //update head if its the first node
            }

            if (current->ListEntry.Flink) {
                current->ListEntry.Flink->Blink = current->ListEntry.Blink;
            }

            free(current);
            farm->cow_count--;
            printf("Cow '%s' removed from the farm.\n", name);
            return;
        }
        current = current->ListEntry.Flink;
    }
    printf("Cow '%s' not found.\n", name);
}

// Remove a chicken from the farm by name
void remove_chicken(Farm *farm, const char *name) {
    Chicken *current = farm->ChickenList;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (current->ListEntry.Blink) {
                current->ListEntry.Blink->ListEntry.Flink = current->ListEntry.Flink;
            } else {
                farm->ChickenList = current->ListEntry.Flink; 
            }

            if (current->ListEntry.Flink) {
                current->ListEntry.Flink->Blink = current->ListEntry.Blink;
            }

            free(current);
            farm->chicken_count--;
            printf("Chicken '%s' removed from the farm.\n", name);
            return;
        }
        current = current->ListEntry.Flink;
    }
    printf("Chicken '%s' not found.\n", name);
}

void milk_cow(Cow *cow, int liters) {
    if (cow) {
        cow->liters_produced += liters;
        printf("Cow '%s' milked for %d liters.\n", cow->name, liters);
    }
}

void collect_eggs(Chicken *chicken, int eggs) {
    if (chicken) {
        chicken->eggs_layed += eggs;
        printf("Chicken '%s' laid %d eggs.\n", chicken->name, eggs);
    }
}

void display_farm(Farm *farm) {
    printf("\nFarm: %s\n", farm->name);
    printf("Cows (%d):\n", farm->cow_count);
    Cow *current_cow = farm->CowList;
    while (current_cow != NULL) {
        printf("  - %s: %d liters produced, %d grams eaten\n", current_cow->name, current_cow->liters_produced, current_cow->gr_eaten);
        current_cow = current_cow->ListEntry.Flink;
    }

    printf("Chickens (%d):\n", farm->chicken_count);
    Chicken *current_chicken = farm->ChickenList;
    while (current_chicken != NULL) {
        printf("  - %s: %d eggs laid, %d grams eaten\n", current_chicken->name, current_chicken->eggs_layed, current_chicken->gr_eaten);
        current_chicken = current_chicken->ListEntry.Flink;
    }

    printf("Income: $%.2f\n", farm->income);
}

int main() {
    Farm testFarm;
    strcpy(testFarm.name, "Test Farm");
    testFarm.cow_count = 0;
    testFarm.chicken_count = 0;
    testFarm.income = 0.0;

    InitializeListHead(&testFarm.CowList);
    InitializeListHead(&testFarm.ChickenList);
    add_cow(&testFarm, "Sharon");
    add_cow(&testFarm, "Karin");

    add_chicken(&testFarm, "Ella");
    add_chicken(&testFarm, "Yasmin");

    milk_cow(&testFarm.CowList, 5);
    milk_cow(&testFarm.CowList->Flink, 3);

    collect_eggs(&testFarm.ChickenList, 6);
    collect_eggs(&testFarm.ChickenList->Flink, 4);

    display_farm(&testFarm);

    remove_cow(&testFarm, "Sharon");
    remove_chicken(&testFarm, "Yasmin");

    display_farm(&testFarm);

    return 0;
}
