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

#include "cursorsettings.h"
#include "unitsettings.h"
#include "layersettings.h"
#include "ui_elements.h"

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
    if(ui->leMod->text().toStdString().empty())
        ui->leMod->setText(open->getExistingDirectory(this, "Open Folder Dialog", "."));
    else
        ui->leMod->setText(open->getExistingDirectory(this, "Open Folder Dialog", modRootPath.c_str()));
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
    ui->pbModSave->setEnabled(true);
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
    DOMWriter = new data_base();//Prepare output block iff this is a new mod
    exists = modExists(mod_num);

    if(!exists)
    {
        DOMWriter->CloseFile();
        DOMWriter->OpenBinFileForQuickWrite((ui->leMod->text().toStdString() + "/mod.txt").c_str());
        std::string buff = DOM->GetStrBuffer();
        size_t loc = buff.find("mod_section_end");
        output = buff;
        output = output.substr(0, loc);
        //We are ready to write settings to project file
        DOMWriter->WriteValueAndFlush(output);
        DOMWriter->WriteValueAndFlush("mod_" + intToStr(count) + "_name = " + modName + ";\n");
        DOMWriter->WriteValueAndFlush("mod_" + intToStr(count) + "_path = " + modName + ";\n");
        DOMWriter->WriteValueAndFlush("mod_" + intToStr(count) + "_description = " + tmp + ";\n");
        DOMWriter->WriteValueAndFlush(buff.substr(loc, buff.size() - loc));
        //Increase counter
        count++;
        DOMWriter->CloseFile();
        DOMWriter->OpenFile((ui->leMod->text().toStdString() + "/mod.txt").c_str(), false);
        DOMWriter->WriteValue(intToStr(count), "mod_number");
    }
    else
    {
        DOMWriter->OpenFile((ui->leMod->text().toStdString() + "/mod.txt").c_str(), false);
        DOMWriter->WriteValue(tmp, "mod_" + intToStr(mod_num) + "_description");
    }
    DOMWriter->CloseFile();
    DOM->CloseFile();
    DOM->OpenFile((ui->leMod->text().toStdString() + "/mod.txt").c_str());
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
    std::string tmp = open->getOpenFileName(NULL, "Select Texture","" ,"All Files (*.*);; Textures (*.png *.tiff *.tex *.bmp *.jpg *.jpeg)").toStdString();
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
      text_fileName = extract_file_name(ui->leTexturePath->text().toStdString());


      //Now, let's build a relative path assuming the modRoot directory as the root
      path += text_fileName;
      path += ".txt";
      //Now, we create a new and empty file!
      tmp.CreateNewFile((modPath + "/" + path).c_str());
      //Now, let's generate the data fields in the file!
      tmp.OpenFileForQuickWrite((modPath + "/" + path).c_str());
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
      tmp.OpenFile((modPath + "/" + path).c_str(), false);
      tmp.WriteValue(modName + "/Textures" + text_fileName, "tex_texture");
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
    index = 0;
    return false;
}

void MainWindow::on_pbSoundBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leSoundLoc->setText(open->getOpenFileName(this, "Open File Dialog", modRootPath.c_str(), "All Files (*.*);; Sound Files (*.ogg *.wav *.mp3 *.wmv *.m4a)"));
}

void MainWindow::on_pbRegSound_clicked()
{
    data_base tmp;
    std::string file = extract_file_name(ui->leSoundLoc->text().toStdString());
    std::string path = modPath + "/Sounds/" + file + ".txt";
    //Copy the actual sound file
    copyfile(ui->leSoundLoc->text().toStdString(), modPath + "/Sounds/" + file);

    //Now, we write descriptor
    copyfile(modPath + "/Sounds/template_sound.txt", path);

    //Now, let's initialize the fields!
    tmp.OpenFile(path.c_str(), false);
    switch(ui->cbSoundType->currentIndex())
    {
    case 0:
        tmp.WriteValue("m", "sound_type");
        tmp.WriteValue(modName + "/Sounds" + file + ".txt", "music_loc");
        break;
    case 1:
        tmp.WriteValue("e", "sound_type");
        tmp.WriteValue(modName + "/Sounds" + file + ".txt", "effect_loc");
        break;
    case 2:
        tmp.WriteValue("a", "sound_type");
        tmp.WriteValue(modName + "/Sounds" + file + ".txt", "effect_loc");
        break;
    default:
        break;
    }
    tmp.WriteValue(intToStr(ui->sbSoundX->value()), "sound_x");
    tmp.WriteValue(intToStr(ui->sbSoundY->value()), "sound_y");
    tmp.WriteValue(intToStr(ui->sbSoundRange->value()), "range");
    //Save file and close it!
    tmp.CloseFile();
}

void MainWindow::on_pbCodeBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leCodeLoc->setText(open->getOpenFileName(this, "Open File Dialog", modRootPath.c_str(),
                                                 "All Files (*.*);; Scripts (*.py *.pyc *.lua *.luo);; Plugins (*.dll *.dylib *.so)"));
}

void MainWindow::on_pbRegCode_clicked()
{
    data_base tmp;
    std::string file = extract_file_name(ui->leCodeLoc->text().toStdString());
    std::string path = modPath + "/plugins/" + file + ".txt";
    std::vector<std::string> data;
    SearchPacket p;
    size_t index, count;

    switch(ui->cbCodeType->currentIndex())
    {
    case PLUGIN:
        //Set up search type
        p.prefix = "func_";
        p.suffix = "_name";
        p.fileName = file + ".txt";
        p.term = "func_count";
        p.path = modRootPath + "/plugins/" + p.fileName;
        //Copy the actual plugin file
        copyfile(ui->leCodeLoc->text().toStdString(), modRootPath + "/plugins" + file);
        //create function list
        data = getList(p, "Function List!", FULLSEARCH);
        data_base::CreateNewFile_static((modRootPath + "/plugins" + p.fileName).c_str());

        //Add functions
        tmp.OpenFileForQuickWrite(p.path.c_str());
        tmp.WriteValue("func_count = " + intToStr(data.size()) + ";\n");
        for(size_t i = 0; i < data.size(); i++)
        {
            tmp.WriteValue("func_" + intToStr(i) + "_name = " + data[i] + ";\n");
        }
        tmp.CloseFile();

        //Now, we update plugins.txt
        tmp.OpenFile((modRootPath + "/plugins/plugins.txt").c_str());
        count = tmp.GetIntFromData("module_number");
        tmp.CloseFile();

        if(pluginExists(p.path, tmp, index))
        {
            tmp.OpenFile((modRootPath + "/plugins/plugins.txt").c_str(), false);
            tmp.WriteValue("/plugins" + file, "module_" + intToStr(index));
        }
        else
        {
            tmp.OpenFileForQuickWrite((modRootPath + "/plugins/plugins.txt").c_str());
            tmp.WriteValueAndFlush("module_" + intToStr(count) + "= " + "/plugins" + file + ";\n");
            count++;
            tmp.CloseFile();
            tmp.OpenFile((modRootPath + "/plugins/plugins.txt").c_str(), false);
            tmp.WriteValue(intToStr(count), "module_number");
        }
        tmp.CloseFile();
        break;
    default://If it is a script
        //Set up search type
        p.prefix = "func_";
        p.suffix = "_name";
        p.fileName = file + ".txt";
        p.term = "func_count";
        p.path = modPath + "/Scripts" + p.fileName;
        //Copy the actual plugin file
        copyfile(ui->leCodeLoc->text().toStdString(), modPath + "/Scripts" + file);
        //create function list
        data = getList(p, "Function List!", FULLSEARCH);
        data_base::CreateNewFile_static((modPath + "/Scripts" + p.fileName).c_str());

        //Add functions
        tmp.OpenFileForQuickWrite(p.path.c_str());
        tmp.WriteValue("func_count = " + intToStr(data.size()) + ";\n");
        for(size_t i = 0; i < data.size(); i++)
        {
            tmp.WriteValue("func_" + intToStr(i) + "_name = " + data[i] + ";\n");
        }
        tmp.CloseFile();
        break;
    }
}

void MainWindow::on_pbRegPhys_clicked()
{
    //Create writer
    data_base fileWriter;
    std::string path = modPath + "/Physics/" + ui->lePhysName->text().toStdString() + ".txt";
    //Let's copy the template
    copyfile(modPath + "/Physics/template.txt", path);
    //Let's update file
    fileWriter.OpenFile(path.c_str(), false);
    fileWriter.WriteValue(intToStr(ui->sbCharge->value()), "C");
    fileWriter.WriteValue(intToStr(ui->sbMass->value()), "mass");
    fileWriter.WriteValue(numToStr(ui->dsbElasticity->value()), "elasticity");
    fileWriter.WriteValue(numToStr(ui->dsbMu->value()), "mu");
    if(ui->cbUnmovable->isChecked())
        fileWriter.WriteValue("1", "unmovable");
    else
        fileWriter.WriteValue("0", "unmovable");
    if(ui->cbHasMagnetic->isChecked())
    {
        fileWriter.WriteValue(ui->cbMagneticDirection->currentText().toStdString(), "B");
        fileWriter.WriteValue(intToStr(ui->sbMagneticField->value()), "B_magnitude");
    }
    else
        fileWriter.WriteValue("None", "B");
    //Flush buffer
    fileWriter.CloseFile();
}

void MainWindow::on_cbHasMagnetic_clicked()
{
   if(ui->cbHasMagnetic->isChecked())
       ui->sbMagneticField->setEnabled(true);
   else
       ui->sbMagneticField->setEnabled(false);
}

//Global functions

void build_new_directory_tree(const std::string source, const std::string &target)
{
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

std::string extract_file_name(const std::string& path)
{
    if(searchChar('\\', path))
        return path.substr(path.rfind('\\'));
    return path.substr(path.rfind('/'));
}

bool pluginExists(const std::string& searchTerm, const data_base& file, size_t& index)
{
    std::string fileName = extract_file_name(searchTerm);
    for(size_t i = 0; i < file.GetIntFromData("module_number"); i++)
    {
        if(fileName == file.GetStrFromData("module_" + intToStr(i)))
        {
            index = i;
            return true;
        }
    }
    index = 0;
    return false;
}

std::string extract_correct_path(const std::string& fullPath, const std::string& modName)
{
    return fullPath.substr(fullPath.find(modName));
}


void MainWindow::on_pbNewObj_clicked()
{
    switch(ui->cbObjType->currentIndex())
    {
    case 0://Environmental object
    case 7://Unit settings
    {
        UnitSettings unit(this);
        unit.show();
        break;
    }
    case 1://Cursor
    case 2://Cursor set
    {
        cursorsettings cursor(this);
        cursor.show();
        break;
    }
    case 3://Layer
    case 4://Layer set
    {
        Layersettings settings(this);
        settings.show();
        break;
    }
    case 5://Locale
        break;
    case 6://Trigger
    {
        break;
    }
    case 8://UI
    {
        UI_Elements ui_stuff(this);
        ui_stuff.show();
        break;
    }
    default:
        break;
    }
}
