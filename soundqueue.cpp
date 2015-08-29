#include "eureka.h"
#include "game.h"
#include "unit.h"
#include "physics.h"
#include "sound_base.h"

SoundQueue::SoundQueue(Game* owner)
{
    owner_ref = owner;
    musicSound = NULL;
    backBuffer = NULL;
    playingSound = NULL;
    fadeInT = 5000;
}

void SoundQueue::initSoundSys()
{
    mutex_sound_id = owner_ref->SpawnMutex();
    //Set up the queues
    size_t queue_size = owner_ref->GetSoundChunkSize(); //Choosing this number will gives us a nice buffer space to work with

    //Reserve arrays
    sounds.reserve(queue_size);
    trash.reserve(queue_size);//Here, we are allocating the same amount of memory for a potential trash to be sent to GC.
                            //I believe that we may never need this much memory, but it should be enough for most cases!
}

SoundQueue::~SoundQueue()
{
    ClearQueue();
    owner_ref->DeleteMutex(mutex_sound_id);
}

void SoundQueue::AddSoundToQueue(cstr soundFile, bool music)
{
    //Let's block this call if the queue is not quite ready to accept a new item
    waitForEmptyQueue();
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
        sounds.enqueue(tmp);
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

void SoundQueue::AddSoundBufferToQueue(cstr soundBuffer, size_t size, bool isHeaderlessWav, bool music)
{
    //Let's block this call if the queue is not quite ready to accept a new item
    waitForEmptyQueue();
    //Make sure we keep the backBuffer object ready
    FlipMusic();
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Allocate new object
    sound_base* tmp = new sound_base;
    tmp->Load_SoundFromBuffer((byte*)soundBuffer, size, isHeaderlessWav);
    //Check the type of sound
    if(music)
        backBuffer = tmp;
    else
        sounds.enqueue(tmp);
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
    //If all the channels are full, there's not point
    if(channelsBusy())
        return;
    //Send previous sound to trash bin so it gets GCed when it finishes
    if(playingSound)
        trash.enqueue(playingSound);
    //Grab new sound
    playingSound = sounds.front();
    //Pop sound from the queue
    sounds.dequeue();
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

void SoundQueue::GCSounds()
{
    sound_base* tmp = NULL;
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    tmp = trash.front();
    if(tmp && !tmp->isEffectPlaying())
    {
        delete tmp;
        trash.dequeue();
    }
    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}

bool SoundQueue::channelsBusy() const
{
    //Now, we iterate through each channel in the Mix/SDL libraries and report false as soon as we find an empty channel!
    for(size_t i = 0; i < MIX_CHANNELS; i++)
    {
        if(!Mix_Playing(i))//If the channel is ready/free
            return false;
    }
    //If we get here, it means no channels are free!
    return true;
}

void SoundQueue::waitForEmptyQueue() const
{
    while(sounds.full())
    {
        SDL_Delay(1);
    }
}

void SoundQueue::ClearQueue()
{
    //Lock internal mutex
    owner_ref->LockMutex(mutex_sound_id);
    //Wait for sound to finish
    while(playingSound->isPlaying() && !owner_ref->isEngineClosing())
    {
        sleep(5000);
    }

    if(playingSound)
    {
        playingSound->Stop();
        delete playingSound;
    }

    if(backBuffer)
    {
        delete backBuffer;
    }

    //Delete all sounds
    sound_base* tmp;
    while(!sounds.empty())
    {
        tmp = sounds.front();
        sounds.dequeue();
        if(tmp)
            delete tmp;
    }

    //Delete music
    if(musicSound)
    {
        musicSound->Stop();
        delete musicSound;
    }

    //Unlock internal mutex
    owner_ref->UnlockMutex(mutex_sound_id);
}
