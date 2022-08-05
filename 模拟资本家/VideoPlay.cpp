#include<vlc/vlc.h>
#include<windows.h>
#include"Media.h"
int Video_Play(HWND hwnd,const char* videopath)
{
	libvlc_instance_t* inst = libvlc_new(0, NULL);
	libvlc_media_t* m = libvlc_media_new_path(inst, videopath);
	libvlc_media_list_t* ml = libvlc_media_list_new(inst);
	libvlc_media_player_t* mp = libvlc_media_player_new_from_media(m);
	libvlc_media_list_player_t* mlp = libvlc_media_list_player_new(inst);
	libvlc_media_parse(m);
	libvlc_time_t t = libvlc_media_get_duration(m);


	libvlc_media_list_add_media(ml, m);
	libvlc_media_release(m);

	libvlc_media_list_player_set_media_list(mlp, ml);
	libvlc_media_list_player_set_media_player(mlp, mp);
	libvlc_media_list_player_set_playback_mode(mlp, libvlc_playback_mode_default);
	libvlc_media_player_set_hwnd(mp, hwnd);
	libvlc_media_list_player_play(mlp);
	Sleep(t);
	libvlc_media_player_release(mp);
	libvlc_media_list_player_release(mlp);
	return TRUE;
}