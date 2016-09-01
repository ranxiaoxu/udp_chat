#include"server.h"

static void Usage(const char *proc)
{
	std::cout<<"Usage:"<<proc<<"[ip]:[port]"<<std::endl;
}

//static void *recv_and_product(void *arg)
//{
//	udp_server *ser = (udp_server *)arg;
//	std::string out;
//	while(1){
//		ser->recv_data(out);
//		std::cout<<out<<std::endl;
//	}
struct my_arg{
	int listen_sock;
	udp_server *ser;
};
static void *broadcast_and_consume(void *arg)
{
	udp_server *ser = (udp_server *)arg; 
	while(1)
		ser->broadcast_data();
}
static void *run_epoll(void *arg)
{
	struct my_arg *parg;
	parg = (struct my_arg *)arg;
	int listen_sock = parg->listen_sock;
	udp_server *ser = parg->ser;

    int epfd = epoll_create(256);

	struct epoll_event _ev;
	_ev.events = EPOLLIN;
	_ev.data.fd = listen_sock;
	epoll_ctl(epfd,EPOLL_CTL_ADD,listen_sock,&_ev);

	struct epoll_event _ready_ev[128];
	int _ready_evs = 128;
	int _timeout = -1;
    int nums = 0;

	int done = 0;
	while(!done){
		switch(nums = epoll_wait(epfd,_ready_ev,_ready_evs,_timeout)){
			case 0:
				std::cout<<"timeout...\n";
	    		break;
			case -1:
				std::cout<<"epoll_wait"<<std::endl;
				break;
			default:
			{
				int i = 0;
				for(;i < nums;++i){
					int _fd = _ready_ev[i].data.fd;
				    if(_fd == listen_sock && _ready_ev[i].events & EPOLLIN){
						struct sockaddr_in peer;
						socklen_t len = sizeof(peer);
						int new_sock = accept(listen_sock,(struct sockaddr *)&peer,&len);
						if(new_sock > 0){
						   
							_ev.events = EPOLLIN;
							_ev.data.fd = new_sock;
							epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&_ev);
						}
					}else{
						if(_ready_ev[i].events & EPOLLIN){
								
							std::string out;
							ser->recv_data(_fd,out);							
							std::cout<<out<<std::endl;	
							//	printf("client close...");
							//	epoll_ctl(epfd,EPOLL_CTL_DEL,_fd,NULL);
							 //   close(_fd);
						}	
					}
				}
			}
	    	break;
		}
	}   
}

int main(int argc,char *argv[])
{
	if(argc != 3){
		Usage(argv[0]);
		return 1;
	}

	udp_server *ser = new udp_server(argv[1],atoi(argv[2]));
	
	int listen_sock = ser->init();

	struct my_arg arg;
	arg.listen_sock = listen_sock;
	arg.ser = ser;

	pthread_t id1,id2;
	pthread_create(&id1,NULL,run_epoll,(void *)&arg);
	pthread_create(&id2,NULL,broadcast_and_consume,(void *)ser);
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);

//	int done = 0;
//	while(!done){
//		ser->recv_data(out);
//		std::cout<<out<<std::endl;
//	}
//	delete ser;
//	ser = NULL;
	return 0;
}
