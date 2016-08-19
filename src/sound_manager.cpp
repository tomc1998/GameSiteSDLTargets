#include "sound_manager.hpp"
#include <SDL/SDL_mixer.h>
#include <stdio.h>

Mix_Chunk* pop;
void initSounds() {
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
  pop = Mix_LoadWAV("res/pipe.wav");
}
