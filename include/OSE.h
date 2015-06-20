/*
 * Seven Kingdoms: Ancient Adversaries
 *
 * Copyright 1997,1998 Enlight Software Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Filename   : OSE.H
// Description: Header file of Sound Effect Controller
// Owner      : Gilbert

#ifndef __OSE_H
#define __OSE_H

#include <ORESX.h>
#include <OVOLUME.h>

// ------ Define sound effect no. ------//
// note : wave file should be less than 64k in size, otherwise
// the offset generated by LIBxxx.EXE is not correct
//

// ------ Define constant -------//
#define MAX_SE_CACHED 32
// a no. of sound effect is taken care for those are requested
// this cycle or last cycle

// ------ Define Struct SERequest ------//

#define MAX_SE_STORE 4

struct SERequest
{
	char	*wave_ptr;
	short	resx_id;

	short	req_used;
	RelVolume play_vol[MAX_SE_STORE];

	void	add_request(RelVolume);
	int	max_entry();
	void	remove_request(int slot);
	void	clear_request();
};

// ------ Define Class SECtrl -------//

class Audio;

class SECtrl
{
private:
	int	biased_se;
	SERequest *req_pool;
	char	*last_cycle;

	int	cached_size;
	short	cached_index[MAX_SE_CACHED];

public:
	int	init_flag;
	int	audio_flag;					// set if audio.wav_init_flag is set during init
	int	max_sound_effect;
	int	max_supp_effect;
	int	total_effect;
	Audio *audio_ptr;
	ResourceIdx	res_wave;
	ResourceIdx &res_supp;

public:
	SECtrl(Audio *);
	~SECtrl();
	void	init();
	void	deinit();

	void	request( int soundEffect, RelVolume );
	void	request( char *soundName, RelVolume );
		// volume between 0 to 100; pan between -10,000=left, 10,000=right
	void	flush();	// output sound effect to volume
	void	clear();
	char	*get_effect_name(int);
	int	search_effect_id(char *);
	int	search_effect_id(char *, int len);

	int	immediate_sound( char *soundName, RelVolume=DEF_REL_VOLUME);	// mainly for button sound, interface

//	static long sound_volume(short locX, short locY);
//	static long sound_volume(short locX, short locY, short limit, short drop);
//	static long sound_pan(short locX, short locY);
//	static long sound_pan(short locX, short locY, short drop);

private:
	void	load_info();
};

extern SECtrl se_ctrl;

#endif