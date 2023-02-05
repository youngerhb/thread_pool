#include<iostream>
#include<mutex>
#include<thread>
#include<functional>
#include<condition_variable>
#include<future>

#include "thread_pool.hh"

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
    thread_pool pool(4);
    pool.init_threads();
    pool.submit(print1,0);
    pool.end_threads();
}