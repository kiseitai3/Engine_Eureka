//#define EUREKA_EXPORT
#include <SDL.h>
#include <SDL_image.h>
#include "data_base.h"
#include <string>
#include <iostream>
#include <cstring>
#include "draw_base.h"
#include "conversion.h"

//Engine name space macro
//ENGINE_NAMESPACE

TextureStore draw_base::textures;

void draw_base::Load_Texture(const char* source, SDL_Renderer& ren, int fps)// animName is the variable that will contain the name of the animation tag name in the xml file containing the animation details of especific objects (i.e. The hero's animation would have an animation name <hero>).
{
    data_base animDOM(source);
    char path[animDOM.GetStrFromData("tex_texture").size()];
    strcpy(path, animDOM.GetStrFromData("tex_texture").c_str());
    spriteFile = path;//Save local copy of the texture location for reference
    SpriteSheet = textures.LoadUniqueTexture(spriteFile.c_str(), ren);
    frames = animDOM.GetIntFromData("tex_frames");
    height = animDOM.GetIntFromData("tex_height");//Size of placeholding rectangle
    width = animDOM.GetIntFromData("tex_width");
    animNum = animDOM.GetIntFromData("tex_anim_num");
    animCounter = animDOM.GetIntFromData("tex_anim_counter");
    noLoop = animDOM.GetIntFromData("tex_noloop");
    timeBetweenFrames = fps / frames;
    if(timeBetweenFrames == 0)
    {
        timeBetweenFrames = (int)(roundDecimal(1.0 / (frames / (double)(fps)), 0)); //get the number of cycles the frame will be visible by targetting the current frame cap
    }
    //Dimensions manipulation
    src.h = height;
    src.w = width;
    target.h = height;
    target.w = width;
    pivot.x = width / 2;
    pivot.y = height / 2;

    //Reset graphics manipulation!
    resetRotation();
    flip();
}

bool draw_base::isNoLoop() const
{
    return noLoop;
}

void draw_base::apply_surface( int x, int y, SDL_Renderer& destination)
{
    //Holds the clip rectangle that will cycle through the spritesheet!
    src.x = width * frame;
    src.y = height * animNum;

    //Get offsets
    target.x = x;
    target.y = y;

    //Blit
    SDL_RenderCopyEx(&destination, getTextureFromNode(SpriteSheet), &src, &target, rotationDeg, &pivot, flipDir);
    if((frame != frames) && !noLoop)
    {
        if(timeSpentOnFrame == timeBetweenFrames)
        {
            frame++;
            timeSpentOnFrame = 0;
        }
        else
        {
            timeSpentOnFrame++;
        }
    }
    else
    {
        frame = 0;
    }
}
int draw_base::GetHeightOfMainRect() const//This function is here in case I need some data for pixel detection in my physics class (coming up next! :))
{
    return height;
}
int draw_base::GetWidthOfMainRect() const//This function is here in case I need some data for pixel detection in my physics class (coming up next! :))
{
    return width;
}

int draw_base::GetAnimCounter() const
{
    return animCounter;
}

SDL_Texture& draw_base::GetTexture() const
{
    return *getTextureFromNode(SpriteSheet);
}

TextureNode* draw_base::GetTextureNode() const
{
    return SpriteSheet;
}

void draw_base::ClearTexture()
{
    if(SpriteSheet)
        textures.DeleteUniqueTexture(SpriteSheet);
    SpriteSheet = 0;
}

void draw_base::SetTextureFromPointer(TextureNode *ptr)
{
    ClearTexture();
    textures.changeTexture(SpriteSheet, ptr);
}

void draw_base::SetTextureFromRef(TextureNode& tex)
{
    ClearTexture();
    textures.changeTexture(SpriteSheet, &tex);
}

void draw_base::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( getTextureFromNode(SpriteSheet), red, green, blue );
}

void draw_base::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( getTextureFromNode(SpriteSheet), blending );
}

void draw_base::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( getTextureFromNode(SpriteSheet), alpha );
}

void draw_base::setRotationPivot(math_point p)
{
    pivot.x = p.X;
    pivot.y = p.Y;
}

void draw_base::copy(const draw_base& obj, bool realloc_texture, SDL_Renderer* ren)
{
    frame = obj.frame;
    frames = obj.frames;
    height = obj.height;
    width = obj.width;
    animCounter = obj.animCounter;
    animNum = obj.animNum;
    timeBetweenFrames = obj.timeBetweenFrames;
    timeSpentOnFrame = obj.timeSpentOnFrame;
    flipDir = obj.flipDir;
    src = obj.src;
    target = obj.target;
    pivot = obj.pivot;
    noLoop = obj.noLoop;
    rotationDeg = rotationDeg;

    //Now we copy the texture
    spriteFile = obj.spriteFile;
    if(realloc_texture)
    {
        ClearTexture();
        SpriteSheet = textures.LoadUniqueTexture(spriteFile.c_str(), *ren);
    }
    else
    {
        ClearTexture();
        SpriteSheet = obj.SpriteSheet;
    }
}

void draw_base::flip(size_t direction)
{
    switch(direction)
    {
    case TextureFlipDirection::NOFLIP:
        flipDir = SDL_FLIP_NONE;
        break;
    case TextureFlipDirection::HORIZONTALLY:
        flipDir = SDL_FLIP_HORIZONTAL;
        break;
    case TextureFlipDirection::VERTICALLY:
        flipDir = SDL_FLIP_VERTICAL;
        break;
    default:
        std::cout << "Wrong flip parameter passed!" << std::endl;
    }
}

void draw_base::rotate(double degrees)
{
    rotationDeg += degrees;
}

void draw_base::resetRotation()
{
    rotationDeg = 0;
}

draw_base::draw_base()
{
    frame =0;
    frames=1;
    height =0;
    width =0;
    noLoop = 0;
    timeSpentOnFrame = 0;
    SpriteSheet = NULL;
}

draw_base::~draw_base()
{
    ClearTexture();
}


void apply_surface( int x, int y, SDL_Renderer& destination, SDL_Texture& SpriteSheet, int height, int width)
{
//Holds the clip rectangle that will cycle through the spritesheet!
    SDL_Rect clip;
    clip.h = height;
    clip.w = width;
    clip.x = 0;
    clip.y = 0;

    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;
    offset.h = height;
    offset.w = width;

    //Blit
    SDL_RenderCopy( &destination, &SpriteSheet, &clip, &offset );

 }

TextureNode *LoadTexture(const char* file, SDL_Renderer& ren)
{
    TextureNode* SpriteSheet;
    SpriteSheet = draw_base::textures.LoadUniqueTexture(file, ren);
    if(!SpriteSheet)
    {
        std::cout<< "Error: Unable to build texture from the surface!" << std::endl;
        return NULL;
    }
    else
    {
        return SpriteSheet;
    }
}


//End of namespace macro
//ENGINE_NAMESPACE_END
