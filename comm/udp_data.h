#pragma once

#include"my_json.h"

class udp_data{
	public:
		udp_data();
		~udp_data();
		void to_string(std::string &out);
		void to_value(std::string &in);

	public:
		std::string nick_name;
  		std::string school;
		std::string msg;
		std::string type;
};
