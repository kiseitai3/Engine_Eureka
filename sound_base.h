#ifndef SOUND_BASE_H_INCLUDED
#define SOUND_BASE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL_mixer.h>
#include "physics.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


class sound_base
{
public:
    /*Somewhat depracated section. My physics professor told me that all random data buffers will yield noise.
    Thus, use this feature only if you need to generate a noise effect!
    */
    void writeEndianSpecificBytes(void *data2write,int size,void *data);
    int  writeWavHeader(FILE *inFile);
    void wavReadnDisplayHeader(void);

    int wavReadnDisplayHeader(char *fileName);
    int wav_create_header(FILE *file);

    void PutNum2(long num,int endianness,int bytes);
    void WriteWav(FILE *f, long int bytes);
    unsigned char WriteWav(unsigned char* buffer, long int bytes);
    typedef struct  wavHeaderInfo
    {
        char                RIFF[4];        /* RIFF Header      */ //Magic header
        unsigned long       ChunkSize;      /* RIFF Chunk Size  */
        char                WAVE[4];        /* WAVE Header      */
        char                fmt[4];         /* FMT header       */
        unsigned long       Subchunk1Size;  /* Size of the fmt chunk                                */
        unsigned short      AudioFormat;    /* Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM */
        unsigned short      NumOfChannels;      /* Number of channels 1=Mono 2=Sterio                   */
        unsigned long       SamplesPerSec;  /* Sampling Frequency in Hz                             */
        unsigned long       bytesPerSec;    /* bytes per second */
        unsigned short      blockAlign;     /* 2=16-bit mono, 4=16-bit stereo */
        unsigned short      bitsPerSample;  /* Number of bits per sample      */
        char                Subchunk2ID[4]; /* "data"  string   */
        unsigned long       Subchunk2Size;  /* Sampled data length    */
    } wavHeader;
    /*End of depracated section.*/
    //Beginning of functions and types related to normal audio systems in games
    /*The previous code is an experiment. As a result, I don't want to rely on it for all my audio needs.
    This compells me to allow the program to load normal audio files. I also have to include some SDL components.*/
    void Load_Sound (const char* source);
    bool Load_Sound(unsigned char* buffer);
    void Play(int loops = 0);
    void Pause();
    void Stop();
    bool isPlaying() const;
    bool PlayEffect(int soundLoops);
    bool isLoopingEffect() const;
    void FadeOut(int ms);
    void SetVol(int volume);
    const char SoundType();
    void SetPoint();// This point is to create the fading effect of an ambient sound as you move away from a place.
    void Update_Sound_Distance(math_point target, int range=0);// default minimum is 126
    void Update_Sound_Position(int x, int y);
    ~sound_base();
    sound_base(bool random_blob = false);

private:

    unsigned char headerBuffer[44];// I will first create a header buffer and then I will attempt to merge it with the sound buffer
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
static void PutNum(long num,FILE *f,int endianness,int bytes);

//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // SOUND_BASE_H_INCLUDED
