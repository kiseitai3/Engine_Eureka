#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startup.h"
#include "data_base.h"
#include "globals.h"
#include <string>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QGraphicsScene>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  DOM = NULL;
  DOMWriter = NULL;
  open = new QFileDialog();
  worldPrev = NULL;
  textPrev = new QGraphicsScene(this);
  ui->gvTexturePreview->setScene(textPrev);
  engine = new Game(true);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pbModBrowse_clicked()
{
    size_t tmpIndex = 0;
    open->setFileMode(QFileDialog::Directory);
    ui->leMod->setText(open->getExistingDirectory(this, "Open Folder Dialog", "."));
    if(DOM)
        delete DOM;
    //Open mod file
    DOM = new data_base((ui->leMod->text() + "/mod.txt").toStdString().c_str());

    //Check to see if the file exists
    if(!DOM->GetStateOfInternalBuffer())
    {
        delete DOM;
        //If file doesn't exists, then we will want to copy one of our templates to the target directory!
        //In fact, at this stage, this problem is likely due to the fact the user is starting a new Data structure!
        //As a result, it is time to copy Data to the target!
        build_new_directory_tree(QDir::currentPath().toStdString() + "/templates", ui->leMod->text().toStdString());

        //Retry reading the new copy of mod.txt
        DOM = new data_base((ui->leMod->text() + "/mod.txt").toStdString().c_str());
    }

    //summon the mod picker window so the user has a chance to select among mods saved in the current file tree!
    modName = getModName(*DOM, modDescription);

    //Update window
    ui->leModName->setText(modName.c_str());
    ui->leModNamePrev->setText(modName.c_str());
    ui->teModDescription->setText(modDescription.c_str());

    //Create mod directory if it is a new mod
    if(!modExists(tmpIndex) && modName != "")
    {
        QDir dir(ui->leMod->text());
        dir.mkdir(modName.c_str());
        //copy folder tree for the mod
        build_new_directory_tree("templates/campaign", (ui->leMod->text().toStdString() + "/" + modName).c_str());
    }

    //Let's store a quick paths to the mod directories
    modRootPath = ui->leMod->text().toStdString();
    modPath = modRootPath + "/" + modName;

    //Finally, we enable the other tabs and allow the user to do his/her work
    ui->tabRegisterAssets->setEnabled(true);
    ui->tabAssets->setEnabled(true);
    ui->tabDesigner->setEnabled(true);
    ui->tabUIDesigner->setEnabled(true);
}

void MainWindow::on_pBInstallBrowse_clicked()
{
  open->setFileMode(QFileDialog::Directory);
  ui->leModInstall->setText(open->getExistingDirectory(this, "Open Folder Dialog", "."));
}

void MainWindow::on_pbModSave_clicked()
{
  /*This method will save all settings for the mod into the project file (.pr).
   **/
  //Let's capture the string in the Mod's description.
    std::string tmp = ui->teModDescription->toPlainText().toStdString();
    std::string replacement = "";
    std::string output;
    size_t count = 0;
    size_t index = 0;
    size_t mod_num = 0;
    bool exists = false;
    //Let's clean the string of new line and ; characters since they interfere with the file parser.
    while(searchChar('\n', tmp) && tmp != "")
      {
        //Let's swap new line characters for spaces!
        index = searchCharIndex('\n', tmp.c_str());
        tmp = removeCharFromStr('\n', tmp.c_str());
        tmp.insert(index, " ");
      }
    while(searchChar(';', tmp) && tmp != "")
      {
        //Let's swap ; characters for .!
        index = searchCharIndex(';', tmp.c_str());
        tmp = removeCharFromStr(';', tmp.c_str());
        replacement = tmp[index];
        replacement = ". ";
        replacement += capitalizeChar(tmp[index]);
        tmp.replace(index, 1, "");
        tmp.insert(index, replacement);
      }

    //Let's read the data
    count = DOM->GetIntFromData("mod_number");
    //Let's prepare the writer
    if(DOMWriter)
        delete DOMWriter;
    DOMWriter = new data_base((ui->leMod->text().toStdString() + "/mod.txt").c_str(), false);
    //Prepare output block iff this is a new mod
    exists = modExists(mod_num);

    if(!exists)
    {
        output = DOM->GetStrBuffer();
        output = output.substr(0, output.find("mod_section_end"));
        output += "mod_" + intToStr(count) + "_name = " + modName + ";\n\r";
        output += "mod_" + intToStr(count) + "_path = " + modName + ";\n\r";
        output += "mod_" + intToStr(count) + "_description = " + tmp + ";\n\r";
        output += DOM->GetStrBuffer().substr(DOM->GetStrBuffer().find("mod_section_end"));
        //We are ready to write settings to project file
        DOMWriter->WriteValueAndFlush(output);
        //Increase counter
        count++;
        DOMWriter->WriteValue(intToStr(count), "mod_number");
    }
    else
    {
        DOMWriter->WriteValue(tmp, "mod_" + intToStr(mod_num) + "_description");
        DOMWriter->CloseFile();
    }

}

void MainWindow::on_MainWindow_destroyed()
{
    if(DOM)
        DOM->CloseFile();
    if(DOMWriter)
        DOMWriter->CloseFile();
}



void MainWindow::on_pbTextureBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    std::string tmp = open->getOpenFileName(NULL, "Select Texture","" ,"Textures (*.png *.tiff *.tex *.bmp *.jpg *.jpeg)").toStdString();
   // tmp = tmp.replace(0, getMODPath().size(),"");
    ui->leTexturePath->setText(tmp.c_str());
    if(!textPrev->items().empty())
        textPrev->removeItem(textPrev->items()[0]);
    QPixmap p(ui->leTexturePath->text().toStdString().c_str());
    QImage img(ui->leTexturePath->text().toStdString().c_str());

    //Preview the image
    textPrev->addPixmap(p);
    textPrev->update();
    ui->gvTexturePreview->show();

    //Present the real size of the image
    ui->lbTextInfo->setText(("Texture size (HxW): " + intToStr(img.height()) + "x" + intToStr(img.width())).c_str());
    //set up basic values
    ui->sbHeight->setValue(img.height());
    ui->sbWidth->setValue(img.width());
}

void MainWindow::on_pbRegTexture_clicked()
{
  if(ui->leTexName->text() == "" || ui->leTexturePath->text() == "")
    {
      QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
  else
    {
      data_base tmp;
      //First, we need to build the file path we need for this io operation!
      std::string text_fileName;
      std::string path = "Textures/";
      //Let's cleanup the file name
      text_fileName = ui->leTexName->text().toStdString();
      if(searchChar('\\', text_fileName))
          text_fileName = text_fileName.substr(text_fileName.rfind('\\'));
      else
          text_fileName = text_fileName.substr(text_fileName.rfind('/'));

      //Now, let's build a relative path assuming the modRoot directory as the root
      path += text_fileName;
      path += ".txt";
      //Now, we create a new and empty file!
      tmp.CreateNewFile((modPath + "/" + path).c_str());
      //Now, let's generate the data fields in the file!
      tmp.OpenFileForQuickWrite(path.c_str());
      tmp.WriteValueAndFlush("tex_texture = ;\n");
      tmp.WriteValueAndFlush("tex_frames = 1;\n");
      tmp.WriteValueAndFlush("tex_height = 0;\n");
      tmp.WriteValueAndFlush("tex_width = 0;\n");
      tmp.WriteValueAndFlush("tex_anim_counter = 0;\n");
      tmp.WriteValueAndFlush("tex_anim_num = 0;\n");
      tmp.WriteValueAndFlush("tex_time_on_frames = 0;\n");
      tmp.WriteValueAndFlush("tex_noloop = 0;\n");
      //Now, let's initialize the fields!
      tmp.CloseFile();
      tmp.OpenFile((modPath + "/" + path).c_str());
      tmp.WriteValue(modName + "/" + path, "tex_texture");
      tmp.WriteValue(intToStr(ui->sbFrames->value()), "tex_frames");
      tmp.WriteValue(intToStr(ui->sbHeight->value()), "tex_height");
      tmp.WriteValue(intToStr(ui->sbWidth->value()), "tex_width");
      tmp.WriteValue(intToStr(ui->sbAnimCounter->value()), "tex_anim_counter");
      tmp.WriteValue(intToStr(ui->sbAnimNum->value()), "tex_anim_num");
      tmp.WriteValue(intToStr(ui->sbTimePerFrame->value()), "tex_time_on_frames");
      tmp.WriteValue(intToStr(ui->sbLoop->value()), "tex_noloop");
      tmp.CloseFile();
      //Now, copy the actual texture to the target
      copyfile(ui->leTexturePath->text().toStdString(), modPath + "/Textures/" + text_fileName);
  }
}

bool MainWindow::modExists(size_t &index)
{
    for(size_t i = 0; i < DOM->GetIntFromData("mod_number"); i++)
    {
        if(modName == DOM->GetStrFromData("mod_" + intToStr(i) + "_name"))
        {
            index = i;
            return true;
        }
    }
    return false;
}




//Global functions

void build_new_directory_tree(const std::string source, const std::string &target)
{
    std::cout << source << std::endl;
    QDir src(source.c_str());
    QDir dst(target.c_str());
    QFileInfo info;
    QStringList objs;
    std::string path, path_target;

    //Check if directory is valid
    if(!src.exists())
        return;
    //The null scenario. If no files, simply exit!
    if(src.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot).empty())
        return;
    else
        objs = src.entryList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    //Otherwise, iterate through each
    for(size_t i = 0; i < objs.count(); i++)
    {
        path = source + "/" + objs[i].toStdString();
        path_target = target + "/" + objs[i].toStdString();

        info.setFile(path.c_str());

        if(info.isDir())//If it is a directory
        {
            dst.mkdir(path_target.c_str());
            build_new_directory_tree(path, path_target);
        }
        else if(info.isFile())
        {
            QFile::copy(path.c_str(), path_target.c_str());
        }
    }
}
