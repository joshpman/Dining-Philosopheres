#include "thread.h"
#include <iostream>
#include <ThreadClass.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
Mutex *Chopsticks[philosopherCount];
philosopher::philosopher(int cycles, int num, int flag) : rounds(cycles), threadNum(num), isWeirdo(flag) {};

void philosopher::ThreadFunc()
{

    Thread::ThreadFunc();
    char writeBuffer[128];
    sprintf(writeBuffer, "I'm thread #%d\n", threadNum);
    write(1, writeBuffer, strlen(writeBuffer));

    if (!isWeirdo)
    {
        for (int i = 0; i < rounds; i++)
        {
            srand(time(NULL));
            unsigned int delay = (rand() % 5) + 1;
            sprintf(writeBuffer, "Philosopher %d is thinking\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));
            Delay(delay);

            Chopsticks[threadNum]->Lock();
            sprintf(writeBuffer, "Philosopher %d grabs left chopstick\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));
            Chopsticks[(threadNum + 1) % philosopherCount]->Lock();
            sprintf(writeBuffer, "Philosopher %d grabs right chopstick\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));

            sprintf(writeBuffer, "Philosopher %d is eating\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));
            Delay(delay);

            Chopsticks[threadNum]->Unlock();
            Chopsticks[(threadNum + 1) % philosopherCount]->Unlock();
        }
    }
    else
    {
        sprintf(writeBuffer, "Thread #%d is a weirdo\n", threadNum);
        write(1, writeBuffer, strlen(writeBuffer));
        for (int i = 0; i < rounds; i++)
        {
            srand(time(NULL));
            unsigned int delay = (rand() % 5) + 1;
            sprintf(writeBuffer, "Philosopher %d is thinking\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));
            Delay(delay);

            Chopsticks[(threadNum + 1) % philosopherCount]->Lock();
            sprintf(writeBuffer, "Philosopher %d grabs right chopstick\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));

            Chopsticks[threadNum]->Lock();
            sprintf(writeBuffer, "Philosopher %d grabs left chopstick\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));

            sprintf(writeBuffer, "Philosopher %d is eating\n", threadNum);
            write(1, writeBuffer, strlen(writeBuffer));
            Delay(delay);

            Chopsticks[(threadNum + 1) % philosopherCount]->Unlock();
            Chopsticks[threadNum]->Unlock();
        }
    }
    Exit();
}