#include "thread_pool.hh"

template<typename F,typename... Args>
    auto thread_pool::submit(F f, Args&&... args) -> std::future<decltype(f(args...))>{
        std::function<decltype(f(args...))> fuc = std::bind(f,std::forward(args)...);
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(fuc);
        std::function<void()> wrap_fuc = [task_ptr](){
            (*task_ptr)();
        };

        std::future<decltype(f(args...))> fu = task_ptr->get_future();
        queue.push(std::move(wrap_fuc));

        cond.notify_one();

        return  fu.get();       
    }

void thread_pool::work(){
    std::cout<<"thread " << std::this_thread::get_id <<" is fucking initing!"<<std::endl;
    while (!end)
    {
        /* code */
        std::unique_lock<std::mutex> lock(m);

        if(queue.empty())
        cond.wait(lock);

        auto func = queue.pop();
        func();
    }
    
}

void thread_pool::end_threads(){
    end = true;
    cond.notify_all();
    for(unsigned i = 0;i<threads_num;i++){
        if (threads.at(i).joinable()) // 判断线程是否在等待
            {
                threads.at(i).join(); // 将线程加入到等待队列
            }
    }
}
void thread_pool::init_threads(){
    for(unsigned i = 0;i<threads_num;i++){
        std::thread th(std::move(work));
        threads.push_back(std::move(th));
    }
}

thread_pool::thread_pool(unsigned num):threads_num(num), end(false){}
