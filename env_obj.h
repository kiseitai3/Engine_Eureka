#ifndef ENV_OBJ_H_INCLUDED
#define ENV_OBJ_H_INCLUDED
class Env_obj
{
    public:
    Env_obj(int BlitOrder, std::string name, char soundName, math_point *screenPoint, math_point loc, SDL_Surface *screen, SDL_Surface *sharedTexture = NULL);
    int getBlitOrder();
    math_point getLoc();
    void Draw();
}


#endif // ENV_OBJ_H_INCLUDED
