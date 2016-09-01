#pragma once
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
#include<vector>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>
#include"../window/cwindow.h"
#include"../comm/udp_data.h"

class udp_client{
	public:
		udp_client(const std::string _ip,int _port );
		~udp_client();
		int init();
        int recv_data(std::string &out);
        int send_data(std::string &in);
	private:
		int sock;
		std::string ip;
		int port;
		struct sockaddr_in server;
	public:
		std::vector<std::string> flist;
		bool is_friend_exist(const std::string &f);
		bool add_friend(std::string &f);
		bool del_friend(std::string &f);
};
