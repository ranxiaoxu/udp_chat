#include"udp_data.h"

udp_data::udp_data()
{}

udp_data::~udp_data()
{}

void udp_data::to_string(std::string &out)
{
	Json::Value root;
	root["nick_name"] = nick_name;
	root["school"] = school;
	root["msg"] = msg;
	root["type"] = type;
	my_json::serialize(root,out);
}
void udp_data::to_value(std::string &in)
{
	Json::Value root;
	my_json::unserialize(in,root);
	nick_name = root["nick_name"].asString();
	school = root["school"].asString();
	msg = root["msg"].asString();
	type = root["type"].asString();
}
//int main()
//{
//	std::string out;
//	udp_data data;
//	data.nick_name = "baobao";
//	data.school = "bit";
//	data.msg = "xinliku";
//	data.type = "msg";
//	data.to_string(out);
//	std::cout<<out<<std::endl;
//	return 0;
//}
