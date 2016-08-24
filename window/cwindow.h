#pragma once

#include<iostream>
#include<string.h>
#include<ncurses.h>

class cwindow{
	public:
		cwindow();
		~cwindow();
		void draw_header();
		void draw_output();
		void draw_flist();
		void draw_input();

        void wfresh(WINDOW *_win);
		void put_str_to_window(WINDOW *_w,int _y,int _x,std::string &_msg);
		void delete_str_from_window(WINDOW *_w,int _begin,int _num);
        void get_msg_from_window(WINDOW *_w,std::string &out);
		
	public:
		WINDOW *header;
		WINDOW *output;
		WINDOW *flist;
		WINDOW *input;

};

