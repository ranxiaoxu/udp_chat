#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/epoll.h>
#include<map>
#include<unistd.h>
#include<pthread.h>
#include"../data_pool/data_pool.h"

class udp_server{
	public:
		udp_server(const std::string _ip="127.0.0.1",int _port=8080 );
		~udp_server();
		int init();
        int recv_data(int sock,std::string &out);
		int broadcast_data();
	private:
        int send_data(int sock,struct sockaddr_in &client,socklen_t &len,std::string &in);
		void add_user(int sock,std::string &ip,struct sockaddr_in &sk);
		void del_user(std::string key);
		bool is_user_exist(std::string key);
		
	private:
		int listen_sock;
		std::string ip;
		int port;
		std::map<std::string,struct sockaddr_in> online_user;
		std::map<std::string,int> user_sock;
		data_pool pool;
};
