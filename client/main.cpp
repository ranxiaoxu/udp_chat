#include"client.h"
#include<pthread.h>
#include<signal.h>

typedef struct client_info{
	public:
		udp_client *cli;
		cwindow *win;
		std::string nick_name;
		std::string school; 
}cinfo;

cinfo c_info;

//static void quit()
//{
//	udp_client *clip = c_info.cli;
//
//	udp_data data;
//	data.nick_name = c_info.nick_name;
//	data.school = c_info.school;
//	data.msg = "None";
//	data.type = "QUIT";
//
//	std::string str;
//	data.to_string(str);
//
//	clip->send_data(str);
//	cwindow::~cwindow();
//	exit(0);
//}

static void Usage(const char *proc)
{
	std::cout<<"Usage:"<<proc<<" [ip]:[port]"<<std::endl;
}

void *run_header(void *arg)
{
	cinfo *header = (cinfo *)arg;
	cwindow *winp = header->win;
	winp->draw_header();

	int max_y = 0;
	int max_x = 0;
	std::string msg = "Welcome To Chat!";
	int i = 0;
	while(1){
		getmaxyx(winp->header,max_y,max_x);
		winp->put_str_to_window(winp->header,max_y/2,++i,msg);
		winp->wfresh(winp->header);
		winp->delete_str_from_window(winp->header,max_y/2,2);
		i %= max_x;
		usleep(100000);
	}
}
void *run_output_flist(void *arg)
{
	cinfo *output_flist = (cinfo *)arg;
	cwindow *winp = output_flist->win;
	udp_client *clip = output_flist->cli;
	
	winp->draw_output();
	winp->draw_flist();

	std::string in_str;
	udp_data data;

	std::string user;
	std::string friends;

	int max_y,max_x;

	int line = 1;

	while(1){
		getmaxyx(winp->output,max_y,max_x);
		clip->recv_data(in_str);
		data.to_value(in_str);
		user = data.nick_name;
		user += "-";
		user += data.school;

		friends = user;

		if(data.msg != "QUIT")
			clip->add_friend(friends);
		else{ 
			clip->del_friend(friends);
			if(clip->flist.size() == 0)
				 raise(2);
		}
		user += "#";
		user += data.msg;

		//show msg
		if(data.msg != "QUIT")
			winp->put_str_to_window(winp->output,line++,3,user);
		if(line > max_y){
			line = 1;
			winp->delete_str_from_window(winp->output,1,max_y-1);
		}

		//show flist
		int size = clip->flist.size();
		for(int i = 0;i < size;i++){
			winp->put_str_to_window(winp->flist,i+1,2,clip->flist[i]);
		}

		usleep(100000);
		winp->wfresh(winp->output);
		winp->wfresh(winp->flist);
	}
}
void *run_input(void *arg)
{
	cinfo *input = (cinfo *)arg;
	cwindow *winp = input->win;
	udp_client *clip = input->cli;
	winp->draw_input();

	std::string tips = "Please Enter#";

	int max_y = 0;
	int max_x = 0;

	udp_data data;
	std::string smsg;

	while(1){
		data.nick_name = input->nick_name;
		data.school = input->school;
		data.type = "None";

		getmaxyx(winp->input,max_y,max_x);
		winp->put_str_to_window(winp->input,1,2,tips);
		winp->wfresh(winp->input);

		winp->get_msg_from_window(winp->input,data.msg);

		data.to_string(smsg);
		clip->send_data(smsg);

		winp->delete_str_from_window(winp->input,1,max_y-1);

		usleep(100000);
	}
}
int main(int argc,char *argv[])
{
	if(argc != 3){
		Usage(argv[0]);
		return 1;
	}

	std::cout<<"Please enter nick_name:";
	fflush(stdout);
	std::cin>>c_info.nick_name;
	std::cout<<"Please enter shool:";
	fflush(stdout);
	std::cin>>c_info.school;

	udp_client net(argv[1],atoi(argv[2]));
	net.init();
	cwindow win;

	c_info.cli = &net;
	c_info.win = &win;

	pthread_t header,output_flist,input;
	pthread_create(&header,NULL,run_header,(void *)&c_info);
	pthread_create(&output_flist,NULL,run_output_flist,(void *)&c_info);
	pthread_create(&input,NULL,run_input,(void *)&c_info);

	pthread_join(header,NULL);
	pthread_join(output_flist,NULL);
	pthread_join(input,NULL);
//	char buf[1024];
//	udp_client *cli = new udp_client(argv[1],atoi(argv[2]));
//	int done = 0;
//	while(!done){
//		std::string out;
//		std::cout<<"Please Enter:";
//		fflush(stdout);
//		ssize_t _s = read(0,buf,sizeof(buf));
//		if(_s > 0){
//			buf[_s-1] = '\0';
//			std::string in = buf;
//			std::cout<<in<<std::endl;
//			cli->send_data(in);
//		}
//		cli->recv_data(out);
//		std::cout<<"server echo:"<<out<<std::endl;
//	}
//	delete cli;
//	cli = NULL;
//	return 0;
}
