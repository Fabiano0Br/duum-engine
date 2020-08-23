/*
* music/sfx here
*/

Mix_Chunk *music1;
Mix_Chunk *sfxbeep;

void mixerInit(){
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT,2,4096);
	music1 = Mix_LoadWAV("res/audio/ppenho.wav");
	sfxbeep = Mix_LoadWAV("res/audio/beep.wav");
}

void DUUM_SoundTest(){
	Mix_PlayChannel(-1,music1, 0);
}

void DUUM_SoundTest2(){
if (is_in_menu == 1) {
	Mix_PlayChannel(-1,sfxbeep, 0);
}
}
