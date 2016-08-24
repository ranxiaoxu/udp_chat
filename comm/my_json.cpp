#include"my_json.h"

void my_json::serialize(Json::Value &_v,std::string &_out)
{
	
	//Json::FastWriter _w;
	Json::StyledWriter _w;
	_out = _w.write(_v);
}

void my_json::unserialize(std::string &_in,Json::Value &_v)
{
	Json::Reader _r;
	_r.parse(_in,_v,false);
}
