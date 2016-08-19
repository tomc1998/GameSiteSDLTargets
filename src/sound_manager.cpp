#include "sound_manager.hpp"
#ifdef WIN32
#include <windows.h>
#endif
#include <SDL/SDL_mixer.h>
#include <stdio.h>

Mix_Chunk* pop;
Mix_Music* soundtrack;
void initSounds() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  pop = Mix_LoadWAV("res/pipe.wav");
  soundtrack = Mix_LoadMUS("res/hall_of_the_mountain_king.mp3");
}
