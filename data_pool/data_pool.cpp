#include"data_pool.h"

data_pool::data_pool(int _cap)
	:capacity(_cap)
	,pool(_cap)
{
	sem_init(&sem_space,0,capacity);
	sem_init(&sem_data,0,0);
	get_step = 0;
	put_step = 0;
}
data_pool::~data_pool()
{
	sem_destroy(&sem_space);
	sem_destroy(&sem_data);
}
void data_pool::get_data(std::string &out)
{
	sem_wait(&sem_data);
	out = pool[get_step];
	sem_post(&sem_space);
	get_step++;
	get_step %= capacity;
}
void data_pool::put_data(std::string &in)
{
	sem_wait(&sem_space);
	pool[put_step] = in;
	sem_post(&sem_data);
	put_step++;
	put_step %= capacity;
}
