#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startup.h"
#include "data_base.h"
#include "globals.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  DOM = NULL;
  //Once the file path was written to our global variables, open the file in read mode.
  std::string tmpPath = getProjectDirectory();
  tmpPath += getProjectName();
  DOM = new data_base(tmpPath.c_str());
  //Let's check if the file is empty! If it's empty, the file is a new project and the program has to be set up accordingly.
  if(DOM->SearchTermExists("this_is_a_project_file"))
    {
      //Let's parse the file and set the settings in the main window!
      setBasicSettings(getProjectDirectory(), getProjectName(), DOM->GetStrFromData("mod_loc").c_str());
      changeProgramWorkingDirectory(getMODPath().c_str());
    }
  else
    {
      //File is empty or potentially corrupted, so we have to regenerate its contents with default settings.
      DOM->CloseFile();
      DOM->OpenFile(tmpPath.c_str(), false);
      DOM->CloseFile();
      DOM->OpenFileForQuickWrite(tmpPath.c_str());
      /*Let's generate the data fields. I can generate the fields and give them values, but the code will be harder
      to read, so I will separate both processes! Also, some fields require further input from the user.
      */
      DOM->WriteValueAndFlush("proj_name = ;\n");
      DOM->WriteValueAndFlush("mod_loc = ;\n");
      DOM->WriteValueAndFlush("texture_count = ;\n");
      DOM->WriteValueAndFlush("sound_count = ;\n");
      DOM->WriteValueAndFlush("script_count = ;\n");
      //Let's set the values!
      DOM->CloseFile();
      DOM->OpenFile(tmpPath.c_str(), false);
      DOM->WriteValue(removeCharFromStr('/', getProjectName().c_str()), "proj_name");
      DOM->WriteValue("", "mod_loc");
      std::string test = intToStr(0);
      DOM->WriteValue(test, "texture_count");
      DOM->WriteValue(intToStr(0), "sound_count");
      DOM->WriteValue(intToStr(0), "script_count");
      //Let's validate the file by tagging it with the check field.
      DOM->CloseFile();
      DOM->OpenFileForQuickWrite(tmpPath.c_str());
      DOM->WriteValueAndFlush("this_is_a_project_file = ;");
      DOM->CloseFile();
    }

}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::quit();
}
