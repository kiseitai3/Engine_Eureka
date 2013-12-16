#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED
#include <SDL.h>
#include <string>
#include "physics.h"
#include "input.h"

class inputMouse
{
    private:
    math_point _2D_coordinates; //coordinates of mouse pointer
    SDL_Event* event;
    bool pressedButton;
    int mouseButton;

    public:
        inputMouse(SDL_Event* pEvent);
        bool UpdateProcessedCoordinates();
        bool ChangeCoordinates(int x, int y);
        void buttonPress();
        int getButtonState();
        unsigned int GetButton();

};

class inputKeyboard
{
    private:
    SDL_Event* event;
    SDL_Keysym pressKey;
    std::string text;
    bool textMode;// flag that will change the context of key presses in the game
    bool textReady;// flag to prevent string from getting erased prior to display. The getText function is the only function hat can reset the text vaiable to "".

    public:
    inputKeyboard(SDL_Event* pEvent);
    void setInputText();
    void toggleTextMode();
    std::string getText();
    std::string GetKey();
};


#endif // INPUT_H_INCLUDED
