#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
class data_base;
class Unit;
struct math_point;
bool init();
void FrameCapper();
void SpawnUnit(const char type, int BlitOrder, math_point loc, std::string file, bool hero = false, bool hasBars = false);
Unit *FindNearbyUnit(Unit *pUnit);
Unit *FindUnitByName(std::string name);
void loadGameConstants();
SDL_Renderer *GetRenderer();
void saveToFile(std::string file, std::string value, std::string searchTerm);
data_base *loadFile(const char* fileName);

#endif // GLOBALS_H_INCLUDED
