//#define EUREKA_EXPORT
#include "textbox.h"
#include "button.h"
#include <string>
#include <iostream>
#include "draw_base.h"
#include "physics.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "scriptwrap.h"
#include <map>

#include <SDL_image.h>
#include "eureka.h"

//Engine name space macro
//ENGINE_NAMESPACE


Button::Button(std::string msg, const char *file, SDL_Renderer& ren, int blitOrderI): textbox(msg, file, ren, blitOrderI)
{
    script = 0;
    if(!GetDOM())
    {
        std::cout<<"Error: DOM object for this button is NULL!\n\r";
    }
    else
    {
        textures["enter"] = LoadTexture(GetDOM()->GetStrFromData("button_tex_enter").c_str(), ren);
        textures["clicking"] = LoadTexture(GetDOM()->GetStrFromData("button_tex_clicking").c_str(), ren);
        textures["idle"] = LoadTexture(GetDOM()->GetStrFromData("button_tex_idle").c_str(), ren);
        textures["selected"] = LoadTexture(GetDOM()->GetStrFromData("button_tex_selected").c_str(), ren);
        textures["down"] = LoadTexture(GetDOM()->GetStrFromData("button_tex_down").c_str(), ren);
        script = new ScriptWrap(GetDOM()->GetStrFromData("button_script").c_str());
        if(!script)
        {
            std::cout<<"Error: Failed to load scripts for this button! :( \n\r";
        }
    }
    buttonPressedBefore = false;
}

Button::~Button()
{
    //Clean up the heap before losing the pointers! :)
    SDL_DestroyTexture(textures["enter"]);
    SDL_DestroyTexture(textures["clicking"]);
    SDL_DestroyTexture(textures["idle"]);
    SDL_DestroyTexture(textures["selected"]);
    SDL_DestroyTexture(textures["down"]);
    //Clean up additional heap objects
    if(script > 0)
    {
        delete(script);
    }

}

void Button::ProcessMouseLoc(int x, int y)
{
    if(x >= GetLoc().X && x <= (GetLoc().X + GetDrawObject()->GetWidthOfMainRect()))
    {
        if(y <= GetLoc().Y && y >= (GetLoc().X - GetDrawObject()->GetHeightOfMainRect()))
        {
            GetDrawObject()->SetTextureFromPointer(textures["enter"]);
        }
    }
    else
    {
        GetDrawObject()->SetTextureFromPointer(textures["idle"]);
    }
}

void Button::MouseClick(unsigned int button, int x, int y, bool down)
{
    if(x >= GetLoc().X && x <= (GetLoc().X + GetDrawObject()->GetWidthOfMainRect()))
    {
        if(y <= GetLoc().Y && y >= (GetLoc().X - GetDrawObject()->GetHeightOfMainRect()))
        {
            if(button == SDL_BUTTON_LEFT && down)
            {
                GetDrawObject()->SetTextureFromPointer(textures["down"]);
                buttonPressedBefore = true;
            }
            if(button == SDL_BUTTON_RIGHT && down)
            {
                GetDrawObject()->SetTextureFromPointer(textures["selected"]);
                selected = true;
            }
            if((buttonPressedBefore && !down) || (buttonPressedBefore && !down))
            {
                script->ClearArgs(4);
                script->AddArgument(button);
                script->AddArgument(x);
                script->AddArgument(y);
                script->AddArgument((void_ptr)GetOwner());
                script->executeFunction("MouseClick", script->NO_ARGS);
            }
        }
    }
}

//End of namespace macro
//ENGINE_NAMESPACE_END
