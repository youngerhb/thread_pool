#ifndef THREAD_POOL
#define THREAD_POOL

#include<iostream>
#include<mutex>
#include<thread>
#include<functional>
#include<condition_variable>
#include<future>

#include "task_queue.hh"

class thread_pool
{
private:
    /* data */
    task_queue queue;
    std::condition_variable cond;
    std::vector<std::thread> threads;
    std::mutex m;
    unsigned threads_num;
    bool end;
public:
    void init_threads();
    void end_threads();
    void work();
    template<typename F,typename... Args>
    auto submit(F f, Args&&... args) -> std::future<decltype(f(args...))>;
    thread_pool(unsigned num);
    ~thread_pool();
};
#endif