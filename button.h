#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include "scriptwrap.h"
<<<<<<< HEAD

class textbox;
SDL_Texture *LoadTexture(const char *file, SDL_Renderer& ren);
=======
#include "typedefs.h"

class textbox;
TextureNode* LoadTexture(const char *file, SDL_Renderer& ren);
>>>>>>> TheIllusiveMan


class Button: public textbox
{
private:
<<<<<<< HEAD
    ScriptWrap *script;
    std::map<std::string, SDL_Texture*> textures;
    bool buttonPressedBefore;
    bool selected;
=======
    std::map<std::string, TextureNode*> textures;
>>>>>>> TheIllusiveMan

public:
    Button(std::string msg, const char *file, SDL_Renderer& ren, int blitOrderI);
    ~Button();
    void ProcessMouseLoc(size_t x, size_t y);
    void SetTexture(const std::string& name);
    void ChangeMsg(const std::string& msg);
};


#endif // BUTTON_H_INCLUDED
