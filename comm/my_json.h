#pragma once

#include<iostream>
#include<string>
#include"../lib/include/json/json.h"

class my_json{
	public:
		static void serialize(Json::Value &_v,std::string &_out);
		static void unserialize(std::string &_in,Json::Value &_v);
};
