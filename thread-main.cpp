#include <iostream>
#include <ThreadClass.h>
#include <unistd.h>
#include <stdlib.h>
#include "thread.h"
using namespace std;
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        write(1, "Usage: ./phil <cycle count>\n", 29);
        return -1;
    }
    int eatCount = atoi(argv[1]);
    philosopher *members[5];
    for (int i = 0; i < 5; i++)
    {
        int myCount = i;
        Chopsticks[i] = new Mutex();
        members[i] = new philosopher(eatCount, myCount, i!=4?0:1);
    }
    for (int i = 0; i < 5; i++)
    {
        members[i]->Begin();
    }
    for (int i = 0; i < 5; i++)
    {
        members[i]->Join();
    }
    Exit();
}