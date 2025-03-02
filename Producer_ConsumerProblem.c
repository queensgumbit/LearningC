/*
Heres a small project that deals with the Producer-Consumer Problem,
Producer(s) – These threads generate data (messages, numbers, or tasks) and insert them into a shared queue (or buffer).
Consumer(s) – These threads remove data from the queue and process it.
Because multiple threads are accessing a shared resource (the queue), we need proper synchronization mechanisms to avoid race conditions and ensure data consistency.
      */
#include <Windows.h> //for the use of CRITICAL_SECTION
//Here we should have CRITICAL_SECTION functions
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // Maximum ice cream scoops in the freezer- unchangeble

char* buffer[BUFFER_SIZE];  // the freezer 
int count = 0;  //numbers of ice cream scoops in the freezer
int in = 0, out = 0;  // Buffer index for producer and consumer

CRITICAL_SECTION lock;  // Mutex(Mutual Exclusion) for locking freezer access
HANDLE not_empty, not_full;  //HANDLE- identifier (like a pointer) that represents a resource controlled by the Windows operating system 

// Producer func (Ice Cream Maker)
DWORD WINAPI Producer(LPVOID param) {       /*->Double Word, in windows threading the program needs to return a dword typically 0 for succesion.WINAPI- a macro that tells the compiler how the arguments are passed.
                                              Requaired when using windows threads.LPVOID param ->long pointer to void is like - *void, lets you any data(struct'char etc)     */
    while (1) {
        //locking the freezer
        EnterCriticalSection(&lock);

        // waiting to the freezer to get full
        while (count == BUFFER_SIZE) {
            LeaveCriticalSection(&lock);  /* Unlock before waiting ,Since it cannot add more ice cream, it unlocks the mutex to allow the consumer to take a scoop.
                                            If it did not unlock, the consumer thread would be blocked (deadlock situation).*/
            WaitForSingleObject(not_full, INFINITE);  /* Wait for space, not_full is an event (Windows condition variable equivalent) that signals when the buffer has space available.
                                                      INFINITE means the producer will wait forever until a customer eats a scoop.*/
            EnterCriticalSection(&lock);  //relocking when the customer eats a scoop basiclly the producer wakes up and now can create more ice cream
        }

        // Produce ice cream 
        buffer[in]="Chocolate"; //producing one scoop!
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Ice cream maker: added one scoop (Total: %d)\n", count);

        //Signal consumers that freezer is NOT EMPTY
        SetEvent(not_empty);

        // Unlock freezer
        LeaveCriticalSection(&lock);

        Sleep(1000);  // Simulate production time
    }
}

//Consumer function (Customer)
DWORD WINAPI Consumer(LPVOID param) {
    while (1) {
        // Lock the freezer
        EnterCriticalSection(&lock);

        // Wait if the freezer is EMPTY
        while (count == 0) {
            LeaveCriticalSection(&lock);  // Unlock before waiting
            WaitForSingleObject(not_empty, INFINITE);  // Wait for ice cream
            EnterCriticalSection(&lock);  // Re-lock after waking up -just like with the production
        }

        // Consume ice cream (You will complete this part)
        buffer[out]="Chocolate";
        printf(" Customer ate %s!\n", buffer[out]); 
        out = (out + 1) % BUFFER_SIZE;/*why we do modulu? -make the buffer circular, when we reach the end of the buffer, 
        we wrap around to the beginning instead of going out of bounds.*/
        count--;

        printf("Customer: Ate a scoop (Remaining: %d)\n", count);

        // Signal producer that freezer is NOT FULL
        SetEvent(not_full);

        // Unlock freezer
        LeaveCriticalSection(&lock);

        Sleep(1500);  // Simulate eating time
    }

 //Main Function: Sets up everything
int main() {
    InitializeCriticalSection(&lock);  // Initialize mutex
    not_empty = CreateEvent(NULL, FALSE, FALSE, NULL);  // Condition variable
    not_full = CreateEvent(NULL, FALSE, TRUE, NULL);  // Condition variable

    // create threads
    HANDLE producerThread = CreateThread(NULL, 0, Producer, NULL, 0, NULL);
    HANDLE consumerThread = CreateThread(NULL, 0, Consumer, NULL, 0, NULL);

    // wait for threads (infinite loop)
    WaitForMultipleObjects(2, (HANDLE[]){producerThread, consumerThread}, TRUE, INFINITE);

//cleanup
    CloseHandle(producerThread);
    CloseHandle(consumerThread);
    CloseHandle(not_empty);
    CloseHandle(not_full);
    DeleteCriticalSection(&lock);

    return 0;
}
