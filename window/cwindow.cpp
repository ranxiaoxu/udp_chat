#include"cwindow.h"

cwindow::cwindow()
{
	initscr();
}
cwindow::~cwindow()
{
	delwin(header);
	delwin(output);
	delwin(flist);
	delwin(input);
	endwin();
}
void cwindow::draw_header()
{
	int _y = 0;
	int _x = 0;
	int _h = LINES/5;
	int _w = COLS;
	header = newwin(_h,_w,_y,_x);
	wfresh(header);
}
void cwindow::draw_output()
{
	int _y = LINES/5;
	int _x = 0;
	int _h = (LINES*3)/5;
	int _w = (COLS*3)/4;
	output = newwin(_h,_w,_y,_x);
	wfresh(output);
}
void cwindow::draw_flist()
{
	int _y = LINES/5;
	int _x = (COLS*3)/4;
	int _h = (LINES*3)/5;
	int _w = COLS/4;
	flist = newwin(_h,_w,_y,_x);
	wfresh(flist);
}
void cwindow::draw_input()
{
	int _y = (LINES*4)/5;
	int _x = 0;
	int _h = LINES/5;
	int _w = COLS;
	input = newwin(_h,_w,_y,_x);
	wfresh(input);
}
void cwindow::wfresh(WINDOW *_win)
{
	if(_win){
		box(_win,0,0);
		wrefresh(_win);
	}
}
void cwindow::put_str_to_window(WINDOW *_w,int _y,int _x,std::string &_msg)
{
	mvwaddstr(_w,_y,_x,_msg.c_str());
}
void cwindow::delete_str_from_window(WINDOW *_w,int _begin,int _num)
{
	while(_num-- > 0){
		wmove(_w,_begin++,0);
		wclrtoeol(_w);
	}
}
void cwindow::get_msg_from_window(WINDOW *_w,std::string &_out)
{
	char msg[1024];
	memset(msg,'\0',sizeof(msg));
	wgetnstr(_w,msg,sizeof(msg));
	_out = msg;
}
//int main()
//{
//	cwindow *winp = new cwindow;
//	winp->draw_header();
//	winp->draw_output();
//	winp->draw_flist();
//	winp->draw_input();
//	sleep(5);
//	delete winp;
//	winp = NULL;
//}
