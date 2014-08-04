#include <iostream>
#include <string>
#include "draw_base.h"
#include "physics.h"
#include <SDL.h>
#include <SDL_ttf.h>
//#include "globals.h"
#include "textbox.h"
#include "ui.h"

textbox::textbox(std::string msg, const char *textboxFile, SDL_Renderer& ren, int blitOrderI)
{
	screen = NULL;
    data = new data_base(textboxFile);
    if(!data)
    {
        data = 0;
        std::cout<<"Critical Error: The io object failed to initialize on the heap! Invalid pointer in the system!\n\r";
    }
    else
    {
        background = new draw_base();
        if(!background)
        {
            background = 0;
            std::cout<<"Critical Error: The background object failed to initialize on the heap! Invalid pointer in the system!\n\r";
        }
        else
        {
            background->Load_Texture(textboxFile, ren);//load background texture using the filepath in the settings file.
        }
        color = {data->GetIntFromData("textbox_colorbyte1"),//Loading bytes that make up the color for the text
                data->GetIntFromData("textbox_colorbyte2"),
                data->GetIntFromData("textbox_colorbyte3")};
        fontSize = data->GetIntFromData("textbox_font_size");//Get font size
        font = TTF_OpenFont(data->GetStrFromData("textbox_fontloc").c_str(), fontSize);//Load the font!
        if(!font)
        {
            font = 0;
            std::cout<<"Critical Error: The font object failed to initialize on the heap! Invalid pointer in the system!\n\r";
        }
        else
        {
            SDL_Surface *tmp = TTF_RenderText_Solid(font, msg.c_str(), color);
            if(!tmp)
            {
                std::cout<<"Critical Error: The message texture object failed to initialize on the heap! Invalid pointer in the system!\n\r";
            }
            else
            {
               message = SDL_CreateTextureFromSurface(&ren, tmp);
               if(!message)
               {
                   std::cout<< "Error: Could not create texture for textbox object!\n\r";
                   text = "TextureErr";
               }
               else
               {
                   text = msg;
               }
            }
        }
        loc.X = data->GetIntFromData("textbox_x");
        loc.Y = data->GetIntFromData("textbox_y");
        type = data->GetStrFromData("textbox_type");
        writable = bool(data->GetIntFromData("textbox_writemode"));
    }
    dead = false;
    blitOrder = blitOrderI;
	screen = &ren;
}

void textbox::SetLoc(int x, int y)
{
    loc.X = x;
    loc.Y = y;
}

void textbox::Draw(SDL_Renderer& ren)
{
    background->apply_surface(loc.X, loc.Y, ren);
    apply_surface(loc.X - 5, loc.Y - 5, ren, *message, background->GetHeightOfMainRect()- 10, background->GetWidthOfMainRect() - 10);
}

int textbox::GetBlitOrder() const
{
    return blitOrder;
}

std::string textbox::GetType() const
{
    return type;
}

bool textbox::GetDeath() const
{
    return dead;
}

UI *textbox::GetOwner() const
{
    return owner;
}

std::string textbox::GetText() const
{
    return text;
}

math_point textbox::GetLoc() const
{
    return loc;
}

data_base *textbox::GetDOM() const
{
    return data;
}

SDL_Renderer *textbox::GetRenderer() const
{
    return screen;
}

void textbox::ToggleDeath()
{
    if(dead == false)
    {
        dead = true;
    }
    else
    {
        dead = false;
    }
}

void textbox::SetOwner(UI *ui)
{
    owner = ui;
}

bool textbox::isInside(unsigned int x, unsigned int y) const
{
    //Check to see if coordinates are within this object's rectangle
    int h = background->GetHeightOfMainRect();
    int w = background->GetWidthOfMainRect();
    if(x >= loc.X && x <= (loc.X + h))
    {
        if(y <= loc.Y && y >= (loc.Y - w))
        {
            return true;
        }
    }
    return false;
}

bool textbox::isWritable() const
{
    return writable;
}

void textbox::changeMsg(std::string msg, SDL_Renderer *ren)
{
    SDL_DestroyTexture(message);
    message = 0;
    SDL_Surface *tmp;
    tmp = TTF_RenderText_Solid(font, msg.c_str(), color);
    if(!tmp)
    {
        std::cout<<"Error: Failed to change text of this textbox!\n\r";
        tmp = TTF_RenderText_Solid(font, "Cat", color);
        text = "Cat";
    }
    else
    {
        message = SDL_CreateTextureFromSurface(ren, tmp);
        if(!message)
        {
            message = NULL;
            std::cout<<"Error: Could not build texture for this textbox!\n\r";
        }
        text = msg;
    }
}

void textbox::changeColor(int r, int g, int b)
{
    color = {r, g, b};
}

void textbox::changeFont(char* fontFile)
{
    font = TTF_OpenFont(fontFile, fontSize);//Load the font!
}

void textbox::changeFontSize(int val)
{
    fontSize = val;
}

draw_base *textbox::GetDrawObject() const
{
    return background;
}

textbox::~textbox()
{
    SDL_DestroyTexture(message);
    if(background > 0)
    {
        delete(background);
    }
    if(data > 0)
    {
        delete(data);
    }
}

void grabText(textbox *pTextbox, const SDL_Event& e)
{
    if(pTextbox != NULL)
    {
        if(pTextbox->GetType() == "textbox")
        {
            SDL_StartTextInput();
            do
            {
                //Loop until the text input events are done.
                if(SDL_PollEvent((SDL_Event*)&e))
                {
                    //check the input events
                    switch(e.type)
                    {
                        case SDL_TEXTINPUT:
                            if(e.text.text != "")
                            {
                                //If the text is not empty, we want to display it.
                                pTextbox->changeMsg(pTextbox->GetText() + std::string(e.text.text), pTextbox->GetRenderer());
                                pTextbox->Draw(*pTextbox->GetRenderer());
                            }
                    }
                }

            }while(e.key.keysym.scancode != SDL_SCANCODE_RETURN);
            SDL_StopTextInput();
        }
    }
}
