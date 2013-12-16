#ifndef SOUND_BASE_H_INCLUDED
#define SOUND_BASE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_mixer.h>

class sound_base
{
  public:
  
//Beginning of functions and types related to normal audio systems in games
/*The previous code is an experiment. As a result, I don't want to rely on it for all my audio needs.
This compells me to allow the program to load normal audio files. I also have to include some SDL components.*/
void Load_Sound (const char* source);
bool Load_Sound(unsigned char* buffer);
void Play(int loops = 0);
void Pause();
void Stop();
bool isPlaying();
bool PlayEffect(int soundLoops);
bool isLoopingEffect();
void FadeOut(int ms);
void SetVol(int volume);
const char SoundType();
void SetPoint();// This point is to create the fading effect of an ambient sound as you move away from a place.
void Update_Sound_Distance(math_point target, int range=0);// default minimum is 126
void Update_Sound_Position(int x, int y);
~sound_base();
sound_base(bool random_blob = false);
private:
//unsigned char headerBuffer[44];// I will first create a header buffer and then I will attempt to merge it with the sound buffer
int indexCount, channel;
bool blob_obj;// This flag will let me know if I should load regular audio files or the experimental audio buffer (see top functions).
bool loopingEffect;
char type;
data_base *AudioDOM;
math_point Location;
Mix_Music *music;
Mix_Chunk *effect;

//Private functions
void addBuff_String(std::string input, int index);
};

#endif // SOUND_BASE_H_INCLUDED
