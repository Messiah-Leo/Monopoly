#include<vlc/vlc.h>
#include"Media.h"

static libvlc_instance_t* inst = libvlc_new(0, NULL);
static libvlc_media_t* md_bk;
static libvlc_media_player_t* mp_bk = libvlc_media_player_new(inst);
static libvlc_media_list_t* ml_bk = libvlc_media_list_new(inst);
static libvlc_media_list_player_t* mlp_bk =libvlc_media_list_player_new(inst);

int MediaPlay_bkMusic(const char* operation,int Volume,const char* media_path)
{
	if (operation == "add")
	{
		md_bk = libvlc_media_new_path(inst, media_path);

		libvlc_media_list_add_media(ml_bk, md_bk);
		libvlc_media_release(md_bk);

		libvlc_media_list_player_set_media_list(mlp_bk, ml_bk);
		libvlc_media_list_player_set_media_player(mlp_bk, mp_bk);
		libvlc_media_list_player_set_playback_mode(mlp_bk, libvlc_playback_mode_loop);
		return 0;
	}
	if (operation == "set_v")
	{
		libvlc_audio_set_volume(mp_bk, Volume);
	}
	else if (operation == "play")
	{
		libvlc_media_list_player_play(mlp_bk);
	}
	else if (operation == "play_next")
	{
		libvlc_media_list_player_next(mlp_bk);
		libvlc_media_list_player_play(mlp_bk);
	}
	else if (operation == "play_pervious")
	{
		libvlc_media_list_player_previous(mlp_bk);
		libvlc_media_list_player_play(mlp_bk);
	}
}