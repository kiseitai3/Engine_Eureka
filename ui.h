#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
#include <list>
#include <map>
#include <string>
#include <SDL.h>
#include "textbox.h"
#include "typedefs.h"

class textbox;
class Button;
class ProgressBar;

class UI
{
private:
    std::list<textbox*> texts;
    std::list<Button*> buttons;
    std::list<ProgressBar*> pBars;
    std::map<std::string, int> pBNums;//Storage location for numbers related to ProgressBars
    std::string msg; //Used for temporary storage of text to be sent to a textbox. It must be cleared as soon as another textbox is clicked on!
    Button *exit;
    textbox *selectedText;
    draw_base *background;
    data_base *uiDOM;
    math_point loc;
    SDL_Renderer* screen;
    bool keyDown;
    bool visibility;


public:
    UI(cstr file, SDL_Renderer& ren);
    ~UI();

    //Getters and setters
    bool isVisible() const;
    void toggleVisibility();
    //Updaters
    void Update();
    void ProcessEvents(SDL_Event *event);
    void AddNumToPBar(int num, std::string name); //This is a very obscure function I added so you can input values that are going to be used by the ProgressBars

    //Draw
    void Draw();
};


#endif // UI_H_INCLUDED
