#include "eureka.h"
#include "game.h"
#include "unit.h"
#include "physics.h"
#include "sound_base.h"

SoundQueue::SoundQueue(Game* owner)
{
    mutex_sound_id = owner->SpawnMutex();
    owner_ref = owner;
    musicSound = NULL;
    backBuffer = NULL;
    playingSound = NULL;
    fadeInT = 5000;
}

SoundQueue::~SoundQueue()
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Wait for sound to finish
    while(playingSound->isPlaying() && !owner_ref->isEngineClosing())
    {
        sleep(5000);
    }

    if(playingSound)
        delete playingSound;

    if(backBuffer)
        delete backBuffer;

    //Delete all sounds
    sound_base* tmp;
    while(!sounds.empty())
    {
        tmp = sounds.front();
        sounds.pop();
        if(tmp)
            delete tmp;
    }

    //Delete music
    if(musicSound)
        delete musicSound;

    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
    owner_ref->DeleteMutex(mutex_sound_id);
}

void SoundQueue::AddSoundToQueue(cstr soundFile, bool music)
{
    //Make sure we keep the backBuffer object ready
    FlipMusic();
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Allocate new object
    sound_base* tmp = new sound_base;
    tmp->Load_Sound(soundFile);
    //Check the type of sound
    if(music)
        backBuffer = tmp;
    else
        sounds.push(tmp);
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::AddSoundBufferToQueue(cstr soundBuffer, bool music)
{
    //Make sure we keep the backBuffer object ready
    FlipMusic();
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Allocate new object
    sound_base* tmp = new sound_base;
    tmp->Load_SoundFromBuffer((byte*)soundBuffer);
    //Check the type of sound
    if(music)
        backBuffer = tmp;
    else
        sounds.push(tmp);
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::FlipMusic()
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Fade out the file that is playing
    if(musicSound)
        musicSound->FadeOut(fadeInT);
    //Fade in backBuffer
    if(backBuffer)
        backBuffer->FadeIn(fadeInT);
    //Copy pointer and set backBuffer to NULL
    musicSound = backBuffer;
    backBuffer = NULL;
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::SetFadeInTime(size_t ms)
{
    fadeInT = ms;
}

void SoundQueue::SetRangeOfEffects(int range)
{
    rangeEffects = range;
}

void SoundQueue::PlayNextSound()
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Delete previous sound
    if(playingSound)
    {
        playingSound->Stop();
        delete playingSound;
    }
    //Grab new sound
    playingSound = sounds.front();
    //Pop sound from the queue
    sounds.pop();
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::UpdateMusicAroundHero(Unit* hero)
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    musicSound->Update_Sound_Distance(hero->GetPhysics()->GetLoc(), rangeEffects);
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::PlayMusicSound()
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    if(!musicSound->isPlaying())
        musicSound->Play(-1);
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::StopMusicSound()
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    if(musicSound->isPlaying())
        musicSound->Stop();
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}
