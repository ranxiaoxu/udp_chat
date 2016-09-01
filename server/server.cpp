#include"server.h"

const int SIZE = 1024;

static void print_log(const char* err,const char *fun,int line)
{
	std::cerr<<"["<<err<<"]"<<fun<<":"<<line<<std::endl;
}
udp_server::udp_server(const std::string _ip,const int _port)
	:ip(_ip)
	,port(_port)
{
	//init();
	std::cout<<"server start!"<<std::endl;
}
int udp_server::init()
{
	listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0){
		print_log("socket",__FUNCTION__,__LINE__);
		return 1;
	}
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip.c_str());
	if(bind(listen_sock,(struct sockaddr *)&local,sizeof(local)) < 0){
		print_log("bind",__FUNCTION__,__LINE__);
		return 2;
	}
	if(listen(listen_sock,5) < 0){
		std::cout<<"listen"<<std::endl;
		return 4;
	}

	std::cout<<"AAAAAAAAAAAAAAAAAAAAAAAA"<<std::endl;
	return listen_sock;
}
int udp_server::recv_data(int sock,std::string &out)
{
	char buf[SIZE]; 
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
	ssize_t _s = recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
	if(_s > 0){
		buf[_s] = '\0';
		out = buf;
		std::string ip = inet_ntoa(peer.sin_addr);
		add_user(sock,ip,peer);
		pool.put_data(out);
	}else if(_s == 0){
		std::cout<<"client quit"<<std::endl;
	}else
		print_log("recvfrom",__FUNCTION__,__LINE__);
	return _s;
}
int udp_server::send_data(int sock,struct sockaddr_in &client,socklen_t &len,std::string &in)
{
	ssize_t _s = sendto(sock,in.c_str(),in.size(),0,(struct sockaddr*)&client,len);
	if(_s < 0)
		print_log("send_data",__FUNCTION__,__LINE__);
	return _s;

}
int udp_server::broadcast_data()
{
	std::string msg;
	pool.get_data(msg);
	std::map<std::string,struct sockaddr_in>::iterator it = online_user.begin();
	std::map<std::string,int>::iterator it_sock = user_sock.begin(); 
	for(;it != online_user.end();++it){
		socklen_t len = sizeof(it->second);
		send_data(it_sock->second,it->second,len,msg);
	}
}
udp_server::~udp_server()
{
	if(listen_sock > 0)
		close(listen_sock);
}
void udp_server::add_user(int sock,std::string &ip,struct sockaddr_in &sk)
{
	if(!is_user_exist(ip)){
		online_user.insert(std::pair<std::string,struct sockaddr_in>(ip,sk));
		user_sock.insert(std::pair<std::string,int>(ip,sock));
	}
}
void udp_server::del_user(std::string key)
{
	if(is_user_exist(key)){
		online_user.erase(key);
		user_sock.erase(key);
	}
}
bool udp_server::is_user_exist(std::string key)
{
	std::map<std::string,struct sockaddr_in>::iterator it = online_user.find(key);
	return it == online_user.end() ? false : true;
}
