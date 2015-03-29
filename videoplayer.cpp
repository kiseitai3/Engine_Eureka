#include "videoplayer.h"
#include "eureka.h"
extern "C"
{
#include <libavutil/common.h>
#include <libavutil/opt.h>
#include <libavformat/avformat.h>
}


VideoFrame::VideoFrame(Game* owner, int h, int w)
{
    pts = 0;
    repeats = 0;
    pYUV420PText = SDL_CreateTexture(&owner->GetRenderer(), SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, w, h);
}

SubFrame::SubFrame()
{
    pts = 0;
    repeats = 0;
    subtitle = NULL;
}

VideoPlayer::VideoPlayer(Game* owner)
{
    owner_ref = owner;
    mutex_vid_id = owner->SpawnMutex();
    timer_id = owner->CreateTimer();
}

void VideoPlayer::InitVideoSystem()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    av_register_all();//init libformat
    avcodec_register_all(); //init libavcodec
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);
}

void VideoPlayer::LoadVideoFile(cstr file)
{
    StopVideo();
    ResetVariables();
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    //open the file
    if(avformat_open_input(&pFormatCtx, file, NULL, 0)!=0)
        std::clog << "Error opening video file! :( Gotta go fast! Gotta go fast! Gotta go faster faster!" << std::endl;
    if(avformat_find_stream_info(pFormatCtx, NULL)<0)
        std::clog << "Error could not extract video info!" << std::endl;
    av_dump_format(pFormatCtx, 0, file, 0);

    //Get streams
    //Video
    videoStream = -1;
    for(size_t i=0; i<pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
        {
            videoStream=i;
            break;
        }
    }

    if(videoStream==-1)
        std::cout << "No video streams to play!" << std::endl; // Didn't find a video stream

    //Sound
    soundStream = -1;
    for(size_t i=0; i<pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
        {
            soundStream=i;
            break;
        }
    }

    if(soundStream==-1)
        std::cout << "No sound streams to play!" << std::endl; // Didn't find a video stream

    //subtitles
    subtitleStream = -1;
    for(size_t i=0; i<pFormatCtx->nb_streams; i++)
    {
        if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_SUBTITLE)
        {
            subtitleStream=i;
            break;
        }
    }

    if(subtitleStream==-1)
        std::cout << "No subtitle streams to show!" << std::endl; // Didn't find a video stream

    //Load codecs
    LoadCodecs();
    //Software scaling
    if(pVidCtx)
        sws_ctx = sws_getContext(pVidCtx->width,
                                 pVidCtx->height,
                                 pVidCtx->pix_fmt,
                                 pVidCtx->width,
                                 pVidCtx->height,
                                 AV_PIX_FMT_YUV420P,
                                 SWS_BILINEAR,
                                 NULL,
                                 NULL,
                                 NULL
                                );
    //Prepare frame buffer
    if(pVidCtx)
    {
        frame = av_frame_alloc();
        pframeYUV420P = av_frame_alloc();
        size_t numBytes = avpicture_get_size(AV_PIX_FMT_YUV420P, pVidCtx->width, pVidCtx->height);
        pixelBuffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));
        avpicture_fill((AVPicture*)pframeYUV420P, pixelBuffer, AV_PIX_FMT_YUV420P, pVidCtx->width, pVidCtx->height);
    }

    if(pSubtitleCtx)
    {
        sFrame = new AVSubtitle;
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);
}

void VideoPlayer::LoadCodecs()
{
    //Video
    if(videoStream != -1)
    {
        //Get context
        pCodecCtx = pFormatCtx->streams[videoStream]->codec;
        //Find codec
        vid = avcodec_find_decoder(pCodecCtx->codec_id);

        if(!vid)
            std::cout << "Unsupported codec!" << std::endl;
        //Copy context
        pVidCtx = avcodec_alloc_context3(vid);

        if(!avcodec_copy_context(pVidCtx, pCodecCtx))
            std::cout << "Couldn't copy video context!" << std::endl;

        //Open the codec
        if(avcodec_open2(pVidCtx, vid, 0) < 0)
            std::cout << "Failed to open codec!" << std::endl;
    }

    if(soundStream != -1)
    {
        //Get context
        pCodecCtx = pFormatCtx->streams[soundStream]->codec;
        //Find codec
        sound = avcodec_find_decoder(pCodecCtx->codec_id);

        if(!sound)
            std::cout << "Unsupported codec!" << std::endl;
        //Copy context
        pSoundCtx = avcodec_alloc_context3(sound);

        if(!avcodec_copy_context(pSoundCtx, pCodecCtx))
            std::cout << "Couldn't copy sound context!" << std::endl;

        //Open the codec
        if(avcodec_open2(pSoundCtx, sound, 0) < 0)
            std::cout << "Failed to open codec!" << std::endl;
    }

    if(subtitleStream != -1)
    {
        //Get context
        pCodecCtx = pFormatCtx->streams[subtitleStream]->codec;
        //Find codec
        sub = avcodec_find_decoder(pCodecCtx->codec_id);

        if(!sub)
            std::cout << "Unsupported codec!" << std::endl;
        //Copy context
        pSubtitleCtx = avcodec_alloc_context3(sub);

        if(!avcodec_copy_context(pSubtitleCtx, pCodecCtx))
            std::cout << "Couldn't copy video context!" << std::endl;

        //Open the codec
        if(avcodec_open2(pSubtitleCtx, sub, 0) < 0)
            std::cout << "Failed to open codec!" << std::endl;
    }
}

void VideoPlayer::PlayVideo()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    //Let's prep the sound queue
    owner_ref->ClearQueue();
    //Prep the sound
    Mix_CloseAudio();
    SDL_Delay(20);
    Mix_OpenAudio(pSoundCtx->sample_rate, MIX_DEFAULT_FORMAT, pSoundCtx->channels, owner_ref->GetSoundChunkSize());
    vidPlaying = true;
    if(owner_ref->isTimerPaused(timer_id))
        owner_ref->UnpauseTimer(timer_id);
    else
        owner_ref->StartTimer(timer_id);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);
}

void VideoPlayer::UpdateVideo()
{
    //Clear all temporary variables
    //ClearTemporaryBuffers();
    int frameFinished = false;
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    //Check if we are playing a video
    if(!vidPlaying)
    {
        //Unlock mutex
        owner_ref->UnlockMutex(mutex_vid_id);
        return;
    }
    //Get packet
    av_read_frame(pFormatCtx, &avpacket);
    //Image
    if(avpacket.stream_index == videoStream)
    {
        avcodec_decode_video2(pVidCtx, frame, &frameFinished, &avpacket);

        if(frameFinished)
        {
            VideoFrame tmp(owner_ref, 0,0);
            //Synchronize video
            tmp.pts = av_frame_get_best_effort_timestamp(frame);
            tmp.repeats = frame->repeat_pict;
            //Convert
            sws_scale(sws_ctx, (const uint8_t* const*)frame->data, frame->linesize, 0, pVidCtx->height, pframeYUV420P->data, pframeYUV420P->linesize);
            SDL_UpdateYUVTexture(tmp.pYUV420PText, &vidScreen, pframeYUV420P->data[0], pframeYUV420P->linesize[0], pframeYUV420P->data[2], pframeYUV420P->linesize[2],
                                 pframeYUV420P->data[1], pframeYUV420P->linesize[1]);
            //Add frame to our queue
            frames.push(tmp);
        }
    }
    //Sound
    if(avpacket.stream_index == soundStream)
    {
        //Decode packet
        avcodec_decode_audio4(pSoundCtx, frame, &frameFinished, &avpacket);
        //Set data into temporary storage
        if(frameFinished)
        {
            size_t size = 0;
            size = av_samples_get_buffer_size(NULL, pSoundCtx->channels, frame->nb_samples, pSoundCtx->sample_fmt, 1);
            put_sound_queue(frame->data[0], size);
        }
        //Attempt to play a chunk
        DeployChunk();
    }
    //Subtitles
    if(avpacket.stream_index == subtitleStream  && isSubtitled())
    {
        //Decode packet
        avcodec_decode_subtitle2(pSubtitleCtx, sFrame, &frameFinished, &avpacket);
        if(frameFinished)
        {
            SubFrame tmpSub;
            //Synchronize subtitles
            tmpSub.pts = sFrame->end_display_time;
            tmpSub.beg_time = sFrame->start_display_time;
            //Prepare some data
            sws_sub_ctx = sws_getContext(sFrame->rects[0]->w,
                                            sFrame->rects[0]->h,
                                            (AVPixelFormat)sFrame->format,
                                            sFrame->rects[0]->w,
                                            sFrame->rects[0]->h,
                                            AV_PIX_FMT_YUV420P,
                                            SWS_BILINEAR,
                                            NULL,
                                            NULL,
                                            NULL
                                            );
            tmpSub.rect.h = sFrame->rects[0]->h;
            tmpSub.rect.w = sFrame->rects[0]->w;
            tmpSub.rect.x = (((double)vidScreen.w - tmpSub.rect.w) / (vidScreen.w)) * vidScreen.w;
            tmpSub.rect.y = vidScreen.h - ((((double)vidScreen.h - tmpSub.rect.h) / (vidScreen.h)) * vidScreen.h);

            //Now we process the subtitle image
            tmpSub.subtitle = SDL_CreateTexture(&owner_ref->GetRenderer(), SDL_PIXELFORMAT_YV12, SDL_TEXTUREACCESS_STREAMING, tmpSub.rect.w, tmpSub.rect.h);
            size_t numBytes = avpicture_get_size(AV_PIX_FMT_YUV420P, tmpSub.rect.w, tmpSub.rect.h);
            pixelBuffer = (uint8_t *)av_malloc(numBytes*sizeof(uint8_t));
            avpicture_fill((AVPicture*)pframeYUV420P, pixelBuffer, AV_PIX_FMT_YUV420P, tmpSub.rect.w, tmpSub.rect.h);
            SDL_UpdateYUVTexture(tmpSub.subtitle, &tmpSub.rect, pframeYUV420P->data[0], pframeYUV420P->linesize[0], pframeYUV420P->data[2], pframeYUV420P->linesize[2],
                                 pframeYUV420P->data[1], pframeYUV420P->linesize[1]);
            //Send subtitle into the queue
            subtitles.push(tmpSub);
        }
    }


    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);
}

void VideoPlayer::DrawVideo()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    //First we draw the actual video frame
    if(pVidCtx)
    {
        VideoFrame* tmp = &frames.front();
        size_t ticks = owner_ref->GetTicks(timer_id);
        if(ticks >= tmp->pts && ticks < (tmp->pts * tmp->repeats))
        {
            //If the timing is within the time indicated by FFmpeg, draw the frame
            SDL_RenderCopy(&owner_ref->GetRenderer(), tmp->pYUV420PText, &vidScreen, &vidScreen);
        }
        else if(ticks > (tmp->pts * tmp->repeats))
        {
            //Otherwise, time to swap to a new frame
            SDL_DestroyTexture(tmp->pYUV420PText);
            frames.pop();
        }
    }

    //Now, we do the same for the subtitles
    if(pSubtitleCtx)
    {
        SubFrame* tmp = &subtitles.front();
        size_t ticks = owner_ref->GetTicks(timer_id);
        if(ticks >= tmp->beg_time && ticks < tmp->pts)
        {
            //If the timing is within the time indicated by FFmpeg, draw the frame
            SDL_RenderCopy(&owner_ref->GetRenderer(), tmp->subtitle, &tmp->rect, &tmp->rect);
        }
        else if(ticks > tmp->pts)
        {
            //Otherwise, time to swap to a new frame
            SDL_DestroyTexture(tmp->subtitle);
            frames.pop();
        }
    }
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);
}

void VideoPlayer::DeployChunk()
{
    /*Unfortunately, I am not sure how to synch the sound so I will be crossing my fingers so the sound never gets too out of synch!*/
    //Check if we have enough bytes to send to the sound queue!
    if(soundData.size() >= pSoundCtx->sample_rate)
    {
        //If so, we send exactly sample_rate number of bytes to the Engine's sound queue!
        char buff[pSoundCtx->sample_rate];
        for(size_t i = 0; i < pSoundCtx->sample_rate; i++)
        {
            buff[i] = soundData.front();
            soundData.pop();
            owner_ref->AddSoundBufferToQueue(buff, pSoundCtx->sample_rate, true);
        }
    }
    //Otherwise, we do nothing until we have a sample size
}

void VideoPlayer::put_sound_queue(const byte* src, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {
        soundData.push(src[i]);
    }
}

size_t VideoPlayer::GetVideoT() const
{
    return owner_ref->GetTicks(timer_id);
}

bool VideoPlayer::isPlayingVideo() const
{
    return vidPlaying;
}

bool VideoPlayer::isSubtitled() const
{
    return hasSubtitles;
}

void VideoPlayer::ResetVariables()
{
    if(pixelBuffer)
    {
        delete[] pixelBuffer;
        pixelBuffer = NULL;
    }
    if(pFormatCtx)
    {
        // Close the video file
        avformat_close_input(&pFormatCtx);
        pFormatCtx = NULL;
    }
    if(pVidCtx)
    {
        avcodec_close(pVidCtx);
        pVidCtx = NULL;
    }
    if(pSoundCtx)
    {
        avcodec_close(pSoundCtx);
        pSoundCtx = NULL;
    }
    if(pSubtitleCtx)
    {
        avcodec_close(pSubtitleCtx);
        pSubtitleCtx = NULL;
    }
    if(pCodecCtx)
    {
        avcodec_close(pCodecCtx);
        pCodecCtx = NULL;
    }
    if(vid)
    {
        delete vid;
        vid = NULL;
    }
    if(sound)
    {
        delete sound;
        sound = NULL;
    }
    if(sub)
    {
        delete sub;
        sub = NULL;
    }
    if(frame)
    {
        av_frame_free(&frame);
        frame = NULL;
    }
    if(pframeYUV420P)
    {
        av_frame_free(&pframeYUV420P);
        pframeYUV420P = NULL;
    }
    if(sFrame)
    {
        delete sFrame;
        sFrame = NULL;
    }
    if(sws_ctx)
    {
        sws_freeContext(sws_ctx);
        sws_ctx = NULL;
    }
    if(sws_sub_ctx)
    {
        sws_freeContext(sws_sub_ctx);
        sws_sub_ctx = NULL;
    }
    videoStream = 0;
    soundStream = 0;
    subtitleStream = 0;
    owner_ref->DeleteTimer(timer_id);
    timer_id = owner_ref->CreateTimer();
}

void VideoPlayer::StopVideo()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    vidPlaying = false;
    //Restore the sound settings to the game's original
    Mix_CloseAudio();
    SDL_Delay(20);
    Mix_OpenAudio(owner_ref->GetSoundFrequency(), MIX_DEFAULT_FORMAT, owner_ref->GetSoundChannels(), owner_ref->GetSoundChunkSize());
    owner_ref->PauseTimer(timer_id);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);
}

VideoPlayer::~VideoPlayer()
{
    //Lock mutex
    owner_ref->LockMutex(mutex_vid_id);
    ResetVariables();
    owner_ref->DeleteTimer(timer_id);
    //Unlock mutex
    owner_ref->UnlockMutex(mutex_vid_id);

    owner_ref->DeleteMutex(mutex_vid_id);
}
