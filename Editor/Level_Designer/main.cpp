#include "mainwindow.h"
#include <QApplication>
#include "startup.h"

//Globals
std::string projDirectory = "test";
std::string projName = ".pr";
std::string MOD = "";

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Let's run the custom dialog box prior to displaying the window. We have to collect the project file path!
  Startup dialog(NULL);
  if(dialog.exec() == Startup::Rejected)
    {
      return 0;
    }
  MainWindow w;
  w.show();

  return a.exec();
}

void setBasicSettings(std::string _projDirectory, std::string _projName, std::string _MOD)
{
  projDirectory = _projDirectory;
  projName = _projName;
  MOD = _MOD;
}

std::string getProjectDirectory()
{
  return projDirectory;
}

std::string getProjectName()
{
  return projName;
}

std::string getMODPath()
{
  return MOD;
}

