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


Button::Button(std::string msg, const char *file, SDL_Renderer& ren, int blitOrderI): textbox(msg, data_base(file).GetStrFromData("textbox_file").c_str(), ren, blitOrderI)
{
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
    }
}

Button::~Button()
{
    //Clean up the heap before losing the pointers! :)
    draw_base::textures.DeleteUniqueTexture(textures["enter"]);
    draw_base::textures.DeleteUniqueTexture(textures["clicking"]);
    draw_base::textures.DeleteUniqueTexture(textures["idle"]);
    draw_base::textures.DeleteUniqueTexture(textures["selected"]);
    draw_base::textures.DeleteUniqueTexture(textures["down"]);

}

void Button::ProcessMouseLoc(size_t x, size_t y)
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

void Button::SetTexture(const std::string& name)
{
    GetDrawObject()->SetTextureFromPointer(textures[name]);
}

void Button::ChangeMsg(const std::string& msg)
{
    changeMsg(msg, GetOwner()->GetRenderer());
}

//End of namespace macro
//ENGINE_NAMESPACE_END
