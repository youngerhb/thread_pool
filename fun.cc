#include<iostream>
#include<functional>
#include<thread>
#include<future>

template<typename F,typename... Args>
auto func_pack(F f, Args&&... args) ->std::future<decltype(f(args...))> {
    auto callback = std::bind(f,std::forward<Args&&>(args)...);
    std::future<decltype(f(args...))> fu = std::async(callback);
    return fu;
}
int print(int num){
    std::cout<< num<<std::endl;
    return num+1;
}

int print1(int& num1){
    std::cout<< num1<<std::endl;
    num1 = 114514;
    std::cout<< num1<<std::endl;
    return num1;
}

int print3(int num1,int num2,int num3){
    std::cout<< num1 <<" "<<num2<<" "<<num3<<std::endl;
    return 3;
}

int main(){
    /*test1
    std::packaged_task<int(int,int,int)> pt(print3);
    std::future<int> fu = pt.get_future(); 
    std::thread th1(std::move(pt),1,2,3);
    int num = fu.get();
    std::cout<<num<<std::endl;
    th1.join();
    */
   
   /*
   std::packaged_task<int(int &)> pt(print1);
   std::future<int>fu =pt.get_future();
   int num = 0;
   std::thread th1(std::move(pt),std::ref(num));
   int fu_result = fu.get();
   std::cout<<"num: " <<num<<std::endl;
   std::cout<<"fu_result: "<<fu_result<<std::endl;
   th1.join();
   /*

   /*
   std::packaged_task<int(int &)> pt(print1);
   int num = 0;
   pt(num);
   std::cout<<"num: " <<num<<std::endl;
   */


    std::function<int()> func = std::bind(print,0);
    auto task_ptr = std::make_shared<std::packaged_task<int()>>(func);
    std::function<void()> wrap_func = [task_ptr]{
        (*task_ptr)();
    };
    std::future<int> fu = task_ptr->get_future();
    std::thread th1(std::move(wrap_func));
    int num = fu.get();
    

    std::cout<<"num: " <<num<<std::endl;
    th1.join();
}
