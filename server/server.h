#pragma once
#include<iostream>
#include<stdlib.h>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<map>
#include<pthread.h>
#include"../data_pool/data_pool.h"

class udp_server{
	public:
		udp_server(const std::string _ip="127.0.0.1",int _port=8080 );
		~udp_server();
		int init();
        int recv_data(std::string &out);
		int broadcast_data();
	private:
		
        int send_data(struct sockaddr_in &client,socklen_t &len,std::string &in);
		void add_user(std::string &ip,struct sockaddr_in &sk);
		void del_user(std::string key);
		bool is_user_exist(std::string key);
		
	private:
		int sock;
		std::string ip;
		int port;
		std::map<std::string,struct sockaddr_in> online_user;
		data_pool pool;
};
