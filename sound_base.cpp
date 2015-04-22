#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <cmath>
#include "data_base.h"
#include <SDL_mixer.h>
#include "physics.h"
#include "sound_base.h"


//Engine name space macro
//ENGINE_NAMESPACE


  //Beginning of types related to usage of random streams as audio inputs
  /* The idea is to take a chunk of memory from the game and create a buffer that can be mistakenly
  interpreted by the SDL audio player as a sound stream. Thus, the objective is to use the games own
  code/data as a source of music for the environment*/

int sound_base::wavReadnDisplayHeader(char *fileName)
{
    wavHeader wavHeader;
    FILE *wavFile;
    int headerSize = sizeof(wavHeader),filelength = 0;
    wavFile = fopen(fileName,"r");
    if(wavFile == NULL)
    {
        printf("Can not able to open wave file\n");
        return 0;
    }
    fread(&wavHeader,headerSize,1,wavFile);
    fclose(wavFile);

    printf("RIFF header                           :%c%c%c%c\n",wavHeader.RIFF[0],wavHeader.RIFF[1],wavHeader.RIFF[2],wavHeader.RIFF[3]);
    printf("WAVE header                           :%c%c%c%c\n",wavHeader.WAVE[0],wavHeader.WAVE[1],wavHeader.WAVE[2],wavHeader.WAVE[3]);
    printf("FMT                                   :%c%c%c%c\n",wavHeader.fmt[0],wavHeader.fmt[1],wavHeader.fmt[2],wavHeader.fmt[3]);
    printf("Data size (based on bits used)        :%ld\n",wavHeader.ChunkSize);

    // Display the sampling Rate form the header
    printf("Sampling Rate                         :%ld\n",wavHeader.SamplesPerSec); //Sampling frequency of the wav file
    printf("Number of bits used                   :%d\n",wavHeader.bitsPerSample); //Number of bits used per sample
    printf("Number of channels                    :%d\n",wavHeader.bitsPerSample);     //Number of channels (mono=1/sterio=2)
    printf("Number of bytes per second            :%ld\n",wavHeader.bytesPerSec);   //Number of bytes per second
    printf("data length                           :%ld\n",wavHeader.Subchunk2Size);
    return 1;
}



static void PutNum(long num,FILE *f,int endianness,int bytes)
{
    int i;
    unsigned char c;

    if(!endianness)
        i=0;
    else
        i=bytes-1;
    while(bytes--)
    {
        c=(num>>(i<<3))&0xff;
        if(fwrite(&c,sizeof(char),1,f)==-1)
        {
            perror("Could not write to output.");
            exit(1);
        }
        if(endianness)
            i--;
        else
            i++;
    }
}
void sound_base::PutNum2(long num,int endianness,int bytes)
{
        int i;
    unsigned char c;

    if(!endianness)
        i=0;
    else
        i=bytes-1;
    while(bytes--)
    {
        c=(num>>(i<<3))&0xff;
        headerBuffer[indexCount] = c;
        indexCount++;
        if(endianness)
            i--;
        else
            i++;
    }
}


/** Writes WAV headers */
void sound_base::WriteWav(FILE *f, long int bytes)//I may use this to stick a header into a temprorary binary blob
{
    /* quick and dirty */

    fwrite("RIFF",sizeof(char),4,f);               /*  0-3 */
    PutNum(bytes+44-8,f,1,4);        /*  4-7 */
    fwrite("WAVEfmt ",sizeof(char),8,f);           /*  8-15 */
    PutNum(16,f,1,4);                /* 16-19 */
    PutNum(1,f,1,2);                 /* 20-21 */
    PutNum(2,f,1,2);                 /* 22-23 */
    PutNum(44100,f,1,4);             /* 24-27 */
    PutNum(44100*2*2,f,1,4);         /* 28-31 */
    PutNum(4,f,1,2);                 /* 32-33 */
    PutNum(16,f,1,2);                /* 34-35 */
    fwrite("data",sizeof(char),4,f); /* 36-39 */
    PutNum(bytes,f,1,4);             /* 40-43 */
}
unsigned char* sound_base::WriteWav(unsigned char* buffer, size_t bytes)
{
    indexCount = 0;
    /* quick and dirty */                   //index table
    addBuff_String("RIFF",0);               /*  0-3 */
    PutNum2(bytes+44-8,1,4);                /*  4-7 */
    addBuff_String("WAVEfmt ",8);           /*  8-15 */
    PutNum2(16,1,4);                        /* 16-19 */
    PutNum2(1,1,2);                         /* 20-21 */
    PutNum2(2,1,2);                         /* 22-23 */
    PutNum2(22050,1,4);                     /* 24-27 */
    PutNum2(22050*2*2,1,4);                 /* 28-31 */
    PutNum2(4,1,2);                         /* 32-33 */
    PutNum2(16,1,2);                        /* 34-35 */
    addBuff_String("data",36);              /* 36-39 */
    PutNum2(bytes,1,4);                     /* 40-43 */
    unsigned char *buff = new unsigned char[43 + bytes];
    strcpyn((char*)buff, (const char*)headerBuffer, 43);
    strcpyn((char*)buff, (const char*)buffer, bytes, 43);
    return buff;
}
//End of random stream input

sound_base::sound_base(bool random_blob)
{
    indexCount = 0;
    blob_obj = random_blob;
    channel = -3;
    loopingEffect = false;
    type = 'a';
    effect = NULL;
    music = NULL;
}

void sound_base::clearSounds()
{
    if(effect)
        Mix_FreeChunk(effect);
    if(music)
        Mix_FreeMusic(music);

    effect = NULL;
    music = NULL;
}

sound_base::~sound_base()
{
    clearSounds();
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> origin/TheIllusiveMan
    if(AudioDOM > 0)
    {
        delete(AudioDOM);
    }
>>>>>>> origin/TheIllusiveMan
}
//Beginning of functions and types related to normal audio systems in games
/*The previous code is an experiment. As a result, I don't want to rely on it for all my audio needs.
This compells me to allow the program to load normal audio files. I also have to include some SDL components.*/
void sound_base::Load_Sound (const char* source)
{
    clearSounds();
<<<<<<< HEAD
<<<<<<< HEAD
    data_base AudioDOM(source);

    type = AudioDOM.GetStrFromData("sound_type").c_str()[0];
    if(type == 'm')
    {
        music = Mix_LoadMUS(AudioDOM.GetStrFromData("music_loc").c_str());
=======
=======
>>>>>>> origin/TheIllusiveMan
    if (!AudioDOM)
    {
        AudioDOM = new data_base(source);
        if(AudioDOM)
        {
            type = char(AudioDOM->GetStrFromData("sound_type").c_str()[0]);
            if(type == 'm')
            {
                music = Mix_LoadMUS(AudioDOM->GetStrFromData("music_loc").c_str());
            }
            if(type == 'e' || type == 'a')
            {
                effect = Mix_LoadWAV(AudioDOM->GetStrFromData("effect_loc").c_str());
            }
            SetPoint();
        }
        else
        {
            std::cout<<"ERROR:Failed to load this sound_base object's Document Object Model\n\r";
        }
>>>>>>> origin/TheIllusiveMan
    }
    if(type == 'e' || type == 'a')
    {
        effect = Mix_LoadWAV(AudioDOM.GetStrFromData("effect_loc").c_str());
    }
    // This point is to create the fading effect of an ambient sound as you move away from a place.
    Location.X = AudioDOM.GetIntFromData("sound_x");
    Location.Y = AudioDOM.GetIntFromData("sound_y");
}

void sound_base::Load_SoundFromBuffer(unsigned char* buffer, size_t size, bool headerlessWav)
{
    clearSounds();
    if(headerlessWav)
    {
        unsigned char* buff2  = new unsigned char[size + 43];
        buff2 = WriteWav(buffer, size);
        effect = Mix_QuickLoad_WAV(buff2);
        delete[] buff2;
        return;
    }
    effect = Mix_QuickLoad_RAW(buffer, size);
}

void sound_base::Play(int loops)//if loops = -1, the loop is infinite!
{
    if(music)
        Mix_PlayMusic(music,loops); // Start playing the sound.
    else
        PlayEffect(loops);
}

void sound_base::Stop()
{
    Mix_HaltMusic();
}

void sound_base::FadeOut(int ms)
{
    while(!Mix_FadeOutMusic(ms) && isPlaying())
    {
        SDL_Delay(100);
    }
}

void sound_base::FadeIn(int ms)
{
    if(Mix_FadeInMusic(music, -1, ms) < 0)
        std::clog << "Music FadeIn Failed: " << Mix_GetError() << std::endl;
}

void sound_base::Pause()
{
    Mix_PauseMusic();
}

void sound_base::SetVol(int volume)
{
    Mix_VolumeMusic(volume);
}

bool sound_base::isPlaying() const
{
    return Mix_PlayingMusic();
}

bool sound_base::PlayEffect(int soundLoops)
{
    if(music && !effect)
    {
        Play(soundLoops);
        return true;
    }
    if(loopingEffect == false && soundLoops == -1)
    {
        channel = Mix_PlayChannel(-1, effect, soundLoops);
        if(channel == -1)
        {
            return false;
        }
        loopingEffect = true;
    }
    if(!loopingEffect)
    {
        channel = Mix_PlayChannel(-1, effect, soundLoops);
        if(channel == -1)
        {
            return false;
        }
    }
    return true;
}

bool sound_base::isLoopingEffect() const
{
    return loopingEffect;
}

bool sound_base::isEffectPlaying() const
{
    return Mix_Playing(channel);
}

const char sound_base::SoundType()
{
    return type;
}

void sound_base::Update_Sound_Position(int x, int y)
{
    /*This method is very useful when keeping the sound together with the texture location.
    This makes sure the player doesn't hear the scream of an NPC that is currently 10 miles away as if
    it was 5 feet away.*/
    Location.X = x;
    Location.Y = y;
}
void sound_base::Update_Sound_Distance(math_point target, int range)// default minimum is 126
{
    int distance = 0;
    int multiplier = 0; // Basically, I will use the multiplier if a bigger range is especified. I know 126 pixels may be awkward since it will be in range of the display, but I was doing it for lazyness.
    distance = int (sqrt(((Location.X - target.X)^2)-((Location.Y-target.Y)^2)));
    if(range <= 126)
    {
    if(distance > 126)
    {
        SetVol(0);
    }
    if(distance < 0)
    {
        SetVol(126);
    }
    if((distance > 0)&&(distance < 126))
    {
        SetVol(distance);
    }
    }
    else
    {
        multiplier = range/126;
        if(range !=0&&range>126)
        {
            SetVol(distance/multiplier);
        }
    }
}

//Private functions
void sound_base::addBuff_String(std::string input, int index)
{
    char *in = (char*)input.c_str();
    for(int i=index; i<(index+input.size());i++)
    {
        headerBuffer[i] = (unsigned char)in[i-indexCount];
    }
    indexCount = (indexCount + input.size())-1;// there's a -1 offset when you count 0 as one item
}

void strcpyn(char* dest, const char* src, size_t bytes, size_t start)
{
    for(size_t i = 0; i < bytes; i++)
    {
        dest[start + i] = src[i];
    }
}

//End of namespace macro
//ENGINE_NAMESPACE_END
