#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

extern Mix_Chunk* pop;
extern Mix_Music* soundtrack;
void initSounds();

#endif
