#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <stack>
#include "game.h"


class data_base;
class Unit;
struct math_point;
class SDL_Renderer;
bool init();
void FrameCapper();
void SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero = false, bool hasBars = false);
Unit *FindNearbyUnit(Unit *pUnit);
Unit *FindUnitByName(std::string name);
void loadGameConstants();
SDL_Renderer *GetRenderer();
void saveToFile(std::string file, std::string value, std::string searchTerm);
data_base *loadFile(char* fileName);
std::stack<fuzzy_obj> reverseOrderStack(const std::stack<fuzzy_obj>& in);

#endif // GLOBALS_H_INCLUDED
