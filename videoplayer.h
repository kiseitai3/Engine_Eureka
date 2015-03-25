#ifndef VIDEOPLAYER_H_INCLUDED
#define VIDEOPLAYER_H_INCLUDED

//Apparently, the FFmpeg libraries were not wrapped around with a set of macros that tag the code with extern C
//for compatibility with C++. If you don't add the extern C, C++ will try to link with C++ name mangling!
//However, the libs are compiled in C so the symbols are not mangled! Be careful with this!
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <SDL.h>
#include <queue>


#include "typedefs.h"

class Game;

struct SynchData
{
    size_t pts;
    size_t repeats;
    SynchData()
    {
        pts = 0;
        repeats = 0;
    }
};

struct VideoFrame : public SynchData
{
    SDL_Texture* pYUV420PText;
    VideoFrame(Game* owner, int h, int w);
};

struct SubFrame : public SynchData
{
    SDL_Texture* subtitle;
    SDL_Rect rect;
    size_t beg_time;
    SubFrame();
};

struct SoundChunk : public SynchData
{
    size_t size;
    byte* chunk;
    SoundChunk()
    {
        size = 0;
    }
};

class VideoPlayer
{
public:
    //Ctors and dtor
    VideoPlayer(Game* owner);
    ~VideoPlayer();

    //Media
    void LoadVideoFile(cstr file);
    void PlayVideo();
    void StopVideo();
    void UpdateVideo();
    void DrawVideo();
    //Getters
    size_t GetVideoT() const;
    bool isSubtitled() const;
    bool isPlayingVideo() const;

    //Init/ Uninit
    void InitVideoSystem();

private:
    Game* owner_ref;
    SDL_Rect vidScreen;
    byte* pixelBuffer;
    //FFmpeg struts
    AVFormatContext *pFormatCtx;
    AVCodecContext *pVidCtx, *pSoundCtx, *pSubtitleCtx;
    AVCodecContext *pCodecCtx;
    AVCodec* vid, *sound, *sub;
    AVFrame* frame, *pframeYUV420P;
    AVSubtitle* sFrame;
	AVPacket avpacket;
	AVPicture  picture;
	SwsContext *sws_ctx, *sws_sub_ctx;
	//Queues
	std::queue<byte> soundData;
	std::queue<VideoFrame> frames;
	std::queue<SubFrame> subtitles;
	//mutex
    size_t mutex_vid_id;
    size_t timer_id;
    int videoStream;
    int soundStream;
    int subtitleStream;
    bool vidPlaying;
    bool hasSubtitles;

    //Methods
    //size_t convertFrameFormat(size_t SDL_Format);
    void LoadCodecs();
    void put_sound_queue(const byte* src, size_t size);
    void DeployChunk();
    //void ClearTemporaryBuffers();
    void ResetVariables();
};


#endif // VIDEOPLAYER_H_INCLUDED
