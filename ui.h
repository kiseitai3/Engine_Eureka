#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
#include <list>
#include <map>
#include <string>
#include <SDL.h>
#include "textbox.h"
#include "typedefs.h"

//Engine name space macro
//ENGINE_NAMESPACE


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
    std::string uiName;
    size_t ui_id;
    Button *exit;
    draw_base *background;
    math_point loc;
    SDL_Renderer* screen;
    bool visibility;


public:
    UI(cstr file, SDL_Renderer& ren);
    ~UI();

    //Getters and setters
    bool isVisible() const;
    bool isInside(size_t x, size_t y);
    void toggleVisibility();
    std::string GetName() const;
    size_t GetID() const;
    Button* GetButtonByLoc(size_t x, size_t y);
    textbox* GetTextboxByLoc(size_t x, size_t y);
    SDL_Renderer* GetRenderer();

    //Setters
    void SetID(size_t id);

    //Updaters
    void Update();
    void ProcessEvents(size_t x, size_t y);
    void AddNumToPBar(int num, const std::string& name); //This is a very obscure function I added so you can input values that are going to be used by the ProgressBars

    //Draw
    void Draw();
};


//End of namespace macro
//ENGINE_NAMESPACE_END
#endif // UI_H_INCLUDED
