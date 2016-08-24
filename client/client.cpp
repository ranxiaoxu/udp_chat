#include"client.h"

const int SIZE = 1024;

static void print_log(const char* err,const char *fun,int line)
{
	std::cerr<<"["<<err<<"]"<<fun<<":"<<line<<std::endl;
}
udp_client::udp_client(const std::string _ip,const int _port)
	:ip(_ip)
	,port(_port)
{
	init();
}
int udp_client::init()
{
	sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0){
		print_log("socket",__FUNCTION__,__LINE__);
		return 1;
	}
}
int udp_client::recv_data(std::string &out)
{
	char buf[SIZE];
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	ssize_t _s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&remote,&len);
	if(_s > 0){
		buf[_s] = '\0';
		out = buf;
	}else
		print_log("recvfrom",__FUNCTION__,__LINE__);
	return _s;
}
int udp_client::send_data(std::string &in)
{
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr(ip.c_str());

	socklen_t len = sizeof(server);
	ssize_t _s = sendto(sock,in.c_str(),in.size(),0,(struct sockaddr *)&server,len);
	std::cout<<_s<<std::endl;
	if(_s < 0)
		print_log("send_data",__FUNCTION__,__LINE__);
	return _s;

}
udp_client::~udp_client()
{
	if(sock > 0)
		close(sock);
}
bool udp_client::is_friend_exist(const std::string &_key)
{
	std::vector<std::string>::iterator iter = flist.begin();
	for(;iter != flist.end();++iter){
		if(_key == *iter)
			return true;
	}
	return false;
}
bool udp_client::add_friend(std::string &f)
{
	if(!is_friend_exist(f)){
		flist.push_back(f);
	}
}
bool udp_client::del_friend(std::string &f)
{
	if(is_friend_exist(f)){
		std::vector<std::string>::iterator iter = flist.begin();
		for(;iter != flist.end();){
			if(*iter == f){
				iter = flist.erase(iter);
				break;
			}else
				++iter;
		}
	}
}
