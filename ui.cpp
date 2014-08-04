#include <list>
#include <string>
#include <SDL.h>
#include "textbox.h"
#include "button.h"
#include "data_base.h"
#include "physics.h"
#include "conversion.h"
#include "progressbar.h"
#include <iostream>
#include <string>
#include "ui.h"

//Constructor and destructor
UI::UI(const char *file, SDL_Renderer& ren)
{
    screen = &ren;
    background = new draw_base();
    if(!background)
    {
        std::cout<<"Error: Could not load background texture for this UI instance!\n\r";
    }
    else
    {
        //Send settings to background
        background->Load_Texture(file, *screen);
        //Recycle the background's DOM object as it contains the settings for the UI in general.
        //This prevents duplication of the same piece of memory! In other words, we save ourselves a couple of bytes.
        uiDOM = background->GetDOM();

        //copy location on screen
        loc.X = uiDOM->GetIntFromData("ui_x");
        loc.Y = uiDOM->GetIntFromData("ui_y");

        //Build exit button
        exit = new Button("X", uiDOM->GetStrFromData("ui_exit_file").c_str(), *screen, 10);
        if(!exit)
        {
            std::cout<<"Error: Could not build Exit button for this UI!\n\r";
        }
        else
        {
            exit->SetLoc(loc.X + background->GetWidthOfMainRect(), loc.Y);
        }

        //Build textboxes
        std::string name;
        texts.resize(uiDOM->GetIntFromData("ui_text_num"));
        for(int i = 0; i < uiDOM->GetIntFromData("ui_text_num"); i++)
        {
            name = "ui_text_" + intToStr(i);
            textbox *tmp = new textbox(uiDOM->GetStrFromData(name + "_msg"), uiDOM->GetStrFromData(name + "_file").c_str(), *screen, 1);
            tmp->SetLoc(loc.X + tmp->GetLoc().Y, loc.Y + tmp->GetLoc().Y);
            tmp->SetOwner(this);
            texts.push_back(tmp);
        }

        //Build Buttons
        buttons.resize(uiDOM->GetIntFromData("ui_button_num"));
        for(int i = 0; i < uiDOM->GetIntFromData("ui_button_num"); i++)
        {
            name = "ui_button_" + intToStr(i);
            Button *tmp = new Button(uiDOM->GetStrFromData(name + "_msg"), uiDOM->GetStrFromData(name + "_file").c_str(), *screen, 1);
            tmp->SetLoc(loc.X + tmp->GetLoc().Y, loc.Y + tmp->GetLoc().Y);
            tmp->SetOwner(this);
            buttons.push_back(tmp);
        }

        //Build ProgressBars
        math_point tempPoint;
        pBars.resize(uiDOM->GetIntFromData("ui_pb_num"));
        for(int i = 0; i < uiDOM->GetIntFromData("ui_pb_num"); i++)
        {
            name = "ui_pb_" + intToStr(i);
            pBNums[uiDOM->GetStrFromData(name + "name")] = 0;
            tempPoint.X = uiDOM->GetIntFromData(name + "_x");
            tempPoint.Y = uiDOM->GetIntFromData(name + "_y");
            int tmpPB = pBNums[uiDOM->GetStrFromData(name + "name")];
            ProgressBar *tmp = new ProgressBar(uiDOM->GetStrFromData(name + "_file").c_str(), &tmpPB, tempPoint, *screen);
            pBars.push_back(tmp);
        }

        //Get beginning visibility state
        visibility = bool(uiDOM->GetIntFromData("ui_visibility"));
    }
    selectedText = 0;
    keyDown = false;
}

//Draw
void UI::Draw()
{
    //Draw exit button
    exit->Draw(*screen);
    //Draw textboxs
    for(std::list<textbox*>::iterator it = texts.begin(); it != texts.end(); it++)
    {
        textbox* tmp = *it;
        tmp->Draw(*screen);
    }

    //Draw buttons
    for(std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
    {
        Button* tmp = *it;
        tmp->Draw(*screen);
    }

    //Draw Progress Bars
    for(std::list<ProgressBar*>::iterator it = pBars.begin(); it != pBars.end(); it++)
    {
        ProgressBar* tmp = *it;
        tmp->Draw(*screen);
    }
}

void UI::ProcessEvents(SDL_Event *event)
{
    //Process our events
    Button *tmp;
    textbox *tmpText;
        //Mouse events
        for(std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
        {
            tmp = *it;
            if(event->button.state == SDL_PRESSED)
            {
                tmp->MouseClick(event->button.button, event->motion.x, event->motion.y,true);
            }
            else if(event->button.state == SDL_RELEASED)
            {
                tmp->MouseClick(event->button.button, event->button.x, event->button.y,false);
            }
            else
            {
                tmp->ProcessMouseLoc(event->motion.x, event->motion.y);
            }
        }

        //Textbox events
        for(std::list<textbox*>::iterator it = texts.begin(); it != texts.end(); it++)
        {
            tmpText = *it;
            if(event->button.state == SDL_PRESSED)
            {
                if(event->button.button == SDL_BUTTON_LEFT && tmpText->isInside(event->button.x, event->button.y))
                {
                    if(tmpText->isWritable())
                    {
                        selectedText = tmpText;
                        msg = selectedText->GetText();
                    }
                }
                if(event->button.button == SDL_BUTTON_RIGHT && tmpText->isInside(event->button.x, event->button.y))
                {
                    selectedText = 0;
                }
            }
            if(event->key.state == SDL_KEYDOWN)
            {
                keyDown = true;
            }
            else if(event->key.state == SDL_KEYUP && keyDown)
            {
                msg = msg + SDL_GetKeyName(event->key.keysym.sym);
                keyDown = false;
            }
        }
        //Check exit button
        if(exit->isInside(event->button.x, event->button.y))
        {
            toggleVisibility();
        }
}

void UI::Update()
{
    Button *tmp;
    textbox *tmpText;

    if(selectedText)
    {
        selectedText->changeMsg(msg, screen);
    }

    //Remove objects marked for removal (for whatever reason)
    for(std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
    {
       tmp = *it;
       if(tmp->GetDeath())
       {
           delete(tmp);
           buttons.remove(*it);
       }
    }
    for(std::list<textbox*>::iterator it = texts.begin(); it != texts.end(); it++)
    {
       tmpText = *it;
       if(tmpText->GetDeath())
       {
           delete(tmpText);
           texts.remove(*it);
       }
    }
}

void UI::AddNumToPBar(int num, std::string name)
{
    pBNums[name] = num;
}

void UI::toggleVisibility()
{
    if(!visibility)
    {
        visibility = true;
    }
    else
    {
        visibility = false;
    }
}

bool UI::isVisible() const
{
    return visibility;
}

UI::~UI()
{
    Button *tmp;
    textbox *tmpText;
    ProgressBar *tmpPB;
    //Remove objects
    //Buttons
    for(std::list<Button*>::iterator it = buttons.begin(); it != buttons.end(); it++)
    {
       tmp = *it;
       delete(tmp);
       buttons.remove(*it);
    }
    //Textboxes
    for(std::list<textbox*>::iterator it = texts.begin(); it != texts.end(); it++)
    {
       tmpText = *it;
       delete(tmpText);
       texts.remove(*it);
    }
    //ProgressBars
    for(std::list<ProgressBar*>::iterator it = pBars.begin(); it != pBars.end(); it++)
    {
       tmpPB = *it;
       delete(tmpPB);
       pBars.remove(*it);
    }
    //Remove other objects
    delete(exit);
    exit = 0;
    selectedText = 0;
}
