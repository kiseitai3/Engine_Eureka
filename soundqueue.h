#ifndef SOUNDQUEUE_H_INCLUDED
#define SOUNDQUEUE_H_INCLUDED
#include <iostream>
#include "Queue.h"
#include "typedefs.h"

class Game;
class sound_base;
class Unit;

class SoundQueue
{
public:
    //Constructors and dtor
    SoundQueue(Game* owner);
    ~SoundQueue();
    void initSoundSys();

    //Setter
    void AddSoundToQueue(cstr soundFile, bool music = false);
    void AddSoundBufferToQueue(cstr soundBuffer, size_t size, bool isHeaderlessWav = true, bool music = false);
    void FlipMusic();
    void SetFadeInTime(size_t ms);
    void SetRangeOfEffects(int range);

    //Manipulation
    void PlayNextSound();
    void UpdateMusicAroundHero(Unit* hero);
    void PlayMusicSound();
    void StopMusicSound();

    //Maintenance
    void GCSounds();
    void ClearQueue();


private:
    Queue<sound_base*> sounds;
    Queue<sound_base*> trash;
    sound_base* playingSound;
    sound_base* musicSound;
    sound_base* backBuffer;
    size_t mutex_sound_id;
    size_t fadeInT;
    int rangeEffects;
    Game* owner_ref;

    //Methods
    bool channelsBusy() const;
    void waitForEmptyQueue() const;
};

#endif // SOUNDQUEUE_H_INCLUDED
