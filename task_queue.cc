#include"task_queue.hh"

std::function<void()> task_queue::pop(){
    std::unique_lock<std::mutex> g(m);
    std::function<void()> callback = queue.front();
    queue.pop();
    return callback;
}

void task_queue::push(std::function<void()> f){
    std::unique_lock<std::mutex> g(m);
    queue.push(f);
}

bool task_queue::empty(){
    std::unique_lock<std::mutex> g(m);
    return queue.empty();
}

unsigned task_queue::size(){
    std::unique_lock<std::mutex> g(m);
    return queue.size();
}