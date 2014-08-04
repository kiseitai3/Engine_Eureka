#include <SDL.h>
#include <string>
#include "physics.h"
#include "input.h"

    inputMouse::inputMouse(SDL_Event* pEvent)
    {
        event = pEvent; //We want to have an object that can access the event instance since that's where all event data is updated by SDL
        mouseButton = 0; //I'm hoping to use the numbers 0 = nothing, 1= left, 2= mid, 3= right
    }
    bool inputMouse::UpdateProcessedCoordinates()// update our internal copy of the mouse coordinates on screen.
    {
        if(event->type== SDL_MOUSEMOTION)
        {
            _2D_coordinates.X = event->motion.xrel;
            _2D_coordinates.Y = event->motion.yrel;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool inputMouse::ChangeCoordinates(int x, int y)// This method will be useful in putting the mouse wherever we want when the user triggers a script
    {
        event->motion.xrel = x;
        event->motion.yrel = y;
        return true;
    }

    void inputMouse::buttonPress()// update our button press flag (mouseButton)
    {
        if(event->type == SDL_MOUSEBUTTONDOWN)
        {
            if(!pressedButton)
            {
                pressedButton = true;
            }
        }
        if(event->type == SDL_MOUSEBUTTONUP)
        {
            if(pressedButton)
            {
                if(event->button.button == SDL_BUTTON_LEFT)
                mouseButton= 1;
                if(event->button.button == SDL_BUTTON_MIDDLE)
                mouseButton= 2;
                if(event->button.button == SDL_BUTTON_RIGHT)
                mouseButton= 3;
                pressedButton = false;
            }
            else
            {
                if(mouseButton != 0)
                {
                    mouseButton = 0;
                }
            }
        }
    }

    int inputMouse::getButtonState() const
    {
        return mouseButton;
    }

unsigned int inputMouse::GetButton() const
{
    return event->button.button;
}

    inputKeyboard::inputKeyboard(SDL_Event* pEvent)//constructor
    {
        event = pEvent;
        text = "";
        textMode = false;
        textReady = false;
        pressKey = event->key.keysym;
    }

    void inputKeyboard::setInputText()//Adds pessed characters to a string that will be displayed
    {
        if(SDL_GetKeyName(event->key.keysym.sym) != "Return" && textMode == true)
        {
            if(event->key.type == SDL_KEYUP)
            {
                text = text + std::string(SDL_GetKeyName(event->key.keysym.sym));
            }
        }
        else
        {
            toggleTextMode();
        }
    }

    void inputKeyboard::toggleTextMode()//Activates /deactivates text mode.
    {
        if(textMode == false)
        {
            textMode = true;
            textReady = false;
        }
        else
        {
            textMode = false;
            textReady = true;
        }
    }

    std::string inputKeyboard::getText()//if textReady is ready, return the available text and set text = "". Else, simply return text but do not modify it!
    {
        if(textMode == false)
        {
            if(textReady == true)
            {
                std::string temp = text;
                text = "";
                textReady = false;
                return temp;
            }
        }
        else
        {
            return text;
        }
    }

   char inputKeyboard::GetKey() const
   {
       return (char)*SDL_GetKeyName(event->key.keysym.sym);
   }

