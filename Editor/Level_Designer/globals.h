#ifndef GLOBALS_H
#define GLOBALS_H
#include <vector>
#include <string>

//functions
void setBasicSettings(std::string _projDirectory = "", std::string _projName = "", std::string _MOD = "");
std::string getProjectDirectory();
std::string getProjectName();
std::string getMODPath();
#endif // GLOBALS_H
