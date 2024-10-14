#include <ThreadClass.h>
#define philosopherCount 5
extern Mutex *Chopsticks[philosopherCount];
class philosopher: public Thread{
    public:
    philosopher();
        philosopher(int eatCount, int threadNum, int flag);
    private:
        void ThreadFunc();
        int rounds;
        int threadNum;
        int isWeirdo;
};