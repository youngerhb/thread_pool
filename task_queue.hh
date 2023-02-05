#ifndef TASK_QUEUE
#define TASK_QUEUE

#include<queue>
#include<mutex>
#include<functional>
#include<condition_variable>
#include<future>

class task_queue
{
private:
    /* data */
    std::queue<std::function<void()> > queue;
    std::mutex m;
public:
    void push(std::function<void()> f);
    std::function<void()> pop();
    bool empty();
    unsigned size();

    task_queue();
    ~task_queue();
};
#endif