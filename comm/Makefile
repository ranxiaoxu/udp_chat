ROOT_PATH=$(shell pwd)

udp_data:udp_data.cpp my_json.cpp
	g++ -o $@ $^ -I$(ROOT_PATH)/../lib/include -L$(ROOT_PATH)/../lib/lib -ljsonlib

