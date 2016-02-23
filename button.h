#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <string>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <map>
#include "scriptwrap.h"
#include "typedefs.h"

class textbox;
TextureNode* LoadTexture(const char *file, SDL_Renderer& ren);


class Button: public textbox
{
private:
    std::map<std::string, TextureNode*> textures;

public:
    Button(std::string msg, const char *file, SDL_Renderer& ren, int blitOrderI);
    ~Button();
    void ProcessMouseLoc(size_t x, size_t y);
    void SetTexture(const std::string& name);
    void ChangeMsg(const std::string& msg);
};


#endif // BUTTON_H_INCLUDED
