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
SDL_Texture* LoadTexture(const char *file, SDL_Renderer& ren);


class Button: public textbox
{
private:
    ScriptWrap *script;
    std::map<std::string, SDL_Texture*> textures;
    bool buttonPressedBefore;
    bool selected;

public:
    Button(std::string msg, const char *file, SDL_Renderer& ren, int blitOrderI);
    ~Button();
    void ProcessMouseLoc(int x, int y);
    void MouseClick(unsigned int button, int x, int y, bool down);


};


#endif // BUTTON_H_INCLUDED
