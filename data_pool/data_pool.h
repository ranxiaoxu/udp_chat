#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<semaphore.h>

class data_pool{
	public:
		data_pool(int _cap = 64);
		~data_pool();
		void get_data(std::string &out);
		void put_data(std::string &in);
	private:
		std::vector<std::string> pool;
		int capacity;
		sem_t sem_space;
		sem_t sem_data;
		int put_step;
		int get_step;
};
