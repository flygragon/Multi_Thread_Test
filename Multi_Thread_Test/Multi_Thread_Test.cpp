// Multi_Thread_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<thread>
#include<iostream>
#include<mutex>

std::mutex mu_cout;

void func1(std::thread::id t_id) {
	mu_cout.lock();
	for (int i =0;i <10;i ++)
		if (std::this_thread::get_id() == t_id)
			std::cout << "Main Thread" << std::endl;
		else
			std::cout <<"Sub Thread" << std::endl;
	mu_cout.unlock();
}
void func2(std::thread::id id) {
	func1(id);
}
int main()
{
	std::thread::id main_thread_id = std::this_thread::get_id();
	std::thread t1(func2,main_thread_id);
	func1(main_thread_id);
	std::cout << t1.joinable() << std::endl;
	//t1.detach();
	t1.join();

	std::cout <<std::thread::hardware_concurrency() <<std::endl;
    return 0;
}

