#ifndef TEXTBOX_H_INCLUDED
#define TEXTBOX_H_INCLUDED
#include <iostream>
#include <string>
#include "draw_base.h"
#include "physics.h"
#include <SDL.h>
#include <SDL_ttf.h>

class UI;

class textbox
{
private:
    SDL_Texture *message;
	SDL_Renderer *screen;
    data_base *data;
    draw_base *background;
    math_point loc;
    SDL_Color color;
    TTF_Font *font;
    UI *owner;
    int fontSize;
    int blitOrder;
    std::string type;
    std::string text;
    bool dead, writable;

public:
    textbox(std::string msg, const char *textboxFile, SDL_Renderer *ren, int blitOrderI = 10);//the I is so it doesn't overshadow the internal variable
    ~textbox();
    void Draw(SDL_Renderer *ren);
    //Getters and setters
    void SetLoc(int x, int y);
    std::string GetType();
    bool GetDeath();
    int GetBlitOrder();//Gets the blit order assigned to this object. This number tells the renderer to draw this object only when it reaches the blit number in blitOrder.
    void ToggleDeath();
    void SetOwner(UI *ui);
    UI *GetOwner();
    std::string GetText();
    math_point GetLoc();
    data_base *GetDOM();//Document object model
    draw_base *GetDrawObject();
	SDL_Renderer *GetRenderer();
    bool isInside(unsigned int x, unsigned int y);
    void changeMsg(std::string msg, SDL_Renderer *ren);
    void changeFont(const char* fontFile);
    void changeColor(int r, int g, int b);
    void changeFontSize(int val);
    bool isWritable();
};

//Global functions
void grabText(textbox *pTextbox, SDL_Event *e);

#endif // TEXTBOX_H_INCLUDED
