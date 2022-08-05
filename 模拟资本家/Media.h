#ifndef TEST
#define TEST
#include<vlc/vlc.h>
#include<windows.h>

int MediaPlay_bkMusic(const char* operation, int Volume=40, const char* media_path = '\0');
int Video_Play(HWND hwnd,const char* videopath);


#endif
