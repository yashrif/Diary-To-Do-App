#include <chrono>
#include <windows.h>
#include <iostream>
#include<string>

HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);

void get_console_cursor(COORD *cordinator)
{
    CONSOLE_SCREEN_BUFFER_INFO console_cursor;
    GetConsoleScreenBufferInfo(out_handle, &console_cursor);
    cordinator->X = console_cursor.dwCursorPosition.X;
    cordinator->Y = console_cursor.dwCursorPosition.Y;
}

void set_console_cursor(const COORD &cordinator)
{
    SetConsoleCursorPosition(out_handle, cordinator);
}

void console_cursor_status(bool status)
{
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(out_handle, &cursor_info);
    cursor_info.bVisible = status;
    SetConsoleCursorInfo(out_handle, &cursor_info);
}

void console_size(int *x, int *y)
{
    CONSOLE_SCREEN_BUFFER_INFO cursor_buffer;
    GetConsoleScreenBufferInfo(out_handle, &cursor_buffer);
    // cout << csbiInfo.dwSize.X << endl;
    *x = cursor_buffer.srWindow.Right - cursor_buffer.srWindow.Left + 1;
    *y = cursor_buffer.srWindow.Bottom - cursor_buffer.srWindow.Top + 1;
}

void delay_print(std::string title, int time_milliseconds)
{
    for (size_t i{0}; i < title.length(); i++)
    {
        std::cout << title[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(time_milliseconds / title.length()));
    }
}

void get_local_time(struct tm *ltm){
    time_t now = time(0);
	localtime_s(ltm, &now);
}
void get_date_now(std::string& returnval) {
	struct tm ltm;
    get_local_time(&ltm);
    std::string months[]={"nanimo","January","February",
        "March","April","May","June","July","August",
        "September","October","November","December"};
	// print various components of tm structure.
	returnval = "";std::string tm;
	tm +=std::to_string(ltm.tm_mday);
	if (tm.size() < 2) tm = "0" + tm;
	returnval += tm + " "+months[ltm.tm_mon+1]+" ";
    returnval += std::to_string(1900 + ltm.tm_year);
}

void get_time_now(std::string &returnval){
    struct tm ltm;
    get_local_time(&ltm);
    int hour_now=ltm.tm_hour;
    std::string pm_am=" AM";
    if(hour_now>=12){
        pm_am=" PM",hour_now-=12;
        if(!hour_now) hour_now=12;}
    else if(!hour_now) hour_now=12;
    returnval =std::to_string(hour_now)+':'+std::to_string(ltm.tm_min)+pm_am;
}