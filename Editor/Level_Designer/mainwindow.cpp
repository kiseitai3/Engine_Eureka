#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startup.h"
#include "data_base.h"
#include "globals.h"
#include <cstdio>
#include <string>
#include <list>
#include <QFileDialog>
#include <QMessageBox>
#include <QThread>
#include <QDir>
#include <QFile>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QTimer>
#include <QThread>

#include "cursorsettings.h"
#include "unitsettings.h"
#include "layersettings.h"
#include "ui_elements.h"
#include "trigger_settings.h"
#include "assetmenu.h"

void doNothing(){}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  DOM = NULL;
  DOMWriter = NULL;
  open = new QFileDialog();
  //Set up world preview image
  worldPrev = new QGraphicsScene(this);
  worldItm = new QGraphicsPixmapItem();
  worldPrev->addItem(worldItm);
  ui->gvGamePreview->setScene(worldPrev);
  frame = NULL;
  frameThread = new QThread(this);
  textPrev = new QGraphicsScene(this);
  ui->gvTexturePreview->setScene(textPrev);
  engine = new Game(true);
  tvBaseAssetsCount = 0;
  tvRegisteredObjsCount = 0;
  tvObjsListCount = 0;
  tvUIElementsCount = 0;

  tvBaseAssets_bk = new QTreeWidget(this);
  tvBaseAssets_bk->setVisible(false);
  for(size_t i = 0; i < ui->tvBaseAssets->topLevelItemCount(); i++)
  {
      tvBaseAssets_bk->addTopLevelItem(new QTreeWidgetItem(*ui->tvBaseAssets->topLevelItem(i)));
  }
  tvRegisteredObjs_bk = new QTreeWidget(this);
  tvRegisteredObjs_bk->setVisible(false);
  for(size_t i = 0; i < ui->tvRegisteredObjects->topLevelItemCount(); i++)
  {
      tvRegisteredObjs_bk->addTopLevelItem(new QTreeWidgetItem(*ui->tvRegisteredObjects->topLevelItem(i)));
  }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddTreeViewItem(char treeView, const std::string &name, bool root, QTreeWidgetItem *parent)
{
    QTreeWidgetItem* itm = NULL;

    switch(treeView)
    {
    case OBJECTLIST:
        root ? itm = new QTreeWidgetItem(ui->tvObjList) : itm = new QTreeWidgetItem(parent);
        tvObjsListCount++;
        break;
    case BASEASSETS:
        root ? itm = new QTreeWidgetItem(ui->tvBaseAssets) : itm = new QTreeWidgetItem(parent);
        tvBaseAssetsCount++;
        break;
    case UIELEMENTS:
        root ? itm = new QTreeWidgetItem(ui->tvUIElements) : itm = new QTreeWidgetItem(parent);
        tvUIElementsCount++;
        break;
    default:
        root ? itm = new QTreeWidgetItem(ui->tvRegisteredObjects) : itm = new QTreeWidgetItem(parent);
        tvRegisteredObjsCount++;
        break;
    }

    parent && !root ? parent->addChild(itm) : doNothing();
    itm->setText(0, name.c_str());
}

void MainWindow::RegisterAsset(const std::string &name, const std::string &path, size_t type, size_t subtype)
{
    AssetNode tmp;

    //Update node data
    tmp.name = name.c_str();
    tmp.path = path.c_str();
    tmp.type = type;
    tmp.subtype = subtype;

    //Copy entry
    assets[tmp.name] = tmp;
}

void MainWindow::RegisterObject(AssetNode obj)
{
    size_t tree = OBJECTLIST;
    math_point p;
    switch(obj.type)
    {
    case CODETYPE|SCRIPT:
    //All unit kind of objects
    case UNIT:
    case OBJECT:
    case PROJECTILE:
    case OBJTYPE|UNIT:
    case OBJTYPE|OBJECT:
    case OBJTYPE|PROJECTILE:
        //Load the object into the engine with the data!
        obj.id = engine->SpawnUnitFromFile(obj.path.toStdString().c_str(), GetBlitOrderFromType(obj.type));
        p.X = engine->GetScreenLoc().X + obj.offset.X;
        p.Y = engine->GetScreenLoc().Y + obj.offset.Y;
        engine->GetUnit(obj.id).GetPhysics()->SetLoc(p);
        break;
    //All triggers
    case TRIGGER:
    case OBJTYPE|TRIGGER:
        obj.id = engine->RegisterTrigger(obj.path.toStdString().c_str());
        p.X = engine->GetScreenLoc().X + obj.offset.X;
        p.Y = engine->GetScreenLoc().Y + obj.offset.Y;
        engine->GetTrigger(obj.id).UpdateTriggerLoc(p.X, p.Y);
        break;
    //All cursors
    case CURSOR:
    case OBJTYPE|CURSOR:
        obj.id = engine->RegisterCursor(obj.path.toStdString().c_str());
        break;
    case CURSORSET:
    case OBJTYPE|CURSORSET:
        obj.idlist = engine->LoadCursors(obj.path.toStdString().c_str());
        break;
    case LAYER:
    case OBJTYPE|LAYER:
        obj.id = engine->AddLayer(obj.path.toStdString().c_str());
        break;
    case LAYERSET:
    case OBJTYPE|LAYERSET:
        obj.idlist = engine->AddLayerSet(obj.path.toStdString().c_str());
        break;
    case UITYPE:
    case UITYPE|BUTTON:
    case UITYPE|TEXTBOX:
        obj.id = engine->RegisterUI(obj.path.toStdString().c_str());
        tree = UIELEMENTS;
        break;
    case PHYSICS:
    case OBJTYPE|PHYSICS:
    default:
        break;
    }

    //Flag object as an instance for propper removal
    obj.subtype = INSTANCE;

    //Update the editor interface
    objects.push_back(obj);
    AddTreeViewItem(tree, obj.name.toStdString());
    objOrder.push(obj.id);

}

void MainWindow::UnregisterObject(const AssetNode &obj)
{
    size_t tree = OBJECTLIST;
    switch(obj.type)
    {
    case CODETYPE|SCRIPT:
    //All unit kind of objects
    case UNIT:
    case OBJECT:
    case PROJECTILE:
    case OBJTYPE|UNIT:
    case OBJTYPE|OBJECT:
    case OBJTYPE|PROJECTILE:
        //Load the object into the engine with the data!
        engine->DeleteUnitByID(obj.id);
        break;
    //All triggers
    case TRIGGER:
    case OBJTYPE|TRIGGER:
        engine->UnRegisterTrigger(obj.id);
        break;
    //All cursors
    case CURSOR:
    case OBJTYPE|CURSOR:
        engine->RemoveCursor(obj.id);
        break;
    case CURSORSET:
    case OBJTYPE|CURSORSET:
        for(size_t i = 0; i < obj.idlist.size(); i++)
        {
            engine->RemoveCursor(obj.idlist[i]);
        }
        break;
    case LAYER:
    case OBJTYPE|LAYER:
        engine->DeleteLayer(obj.id);
        break;
    case LAYERSET:
    case OBJTYPE|LAYERSET:
        for(size_t i = 0; i < obj.idlist.size(); i++)
        {
            engine->DeleteLayer(obj.idlist[i]);
        }
        break;
    case UITYPE:
    case UITYPE|BUTTON:
    case UITYPE|TEXTBOX:
        engine->UnregisterUI(obj.id);
        tree = UIELEMENTS;
        break;
    case PHYSICS:
    case OBJTYPE|PHYSICS:
    default:
        break;
    }

    //Update the editor interface
    objects.remove(obj);
    delete GetTreeViewRoot(tree, obj.name.toStdString());
    removeValFromStack(objOrder, obj.id);
}

void MainWindow::RemoveAsset(const std::string &name)
{
    remove_asset_contents(modRootPath, QString((modRootPath + "/").c_str()) + assets[name.c_str()].path, assets[name.c_str()].type);
    assets.erase(name.c_str());
}

void MainWindow::RemoveObj(const std::string &name)
{
    AssetNode tmp;
    for(std::list<AssetNode>::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        tmp = *itr;
        if(tmp.name.toStdString() == name)
        {
            //Remove from editor
            objects.remove(tmp);
            removeValFromStack(objOrder, tmp.id);
            delete GetTreeViewRoot(OBJECTLIST, tmp.name.toStdString());

            //Remove from engine
            engine->DeleteUnitByID(tmp.id);
            return;
        }
    }
}

void MainWindow::RemoveLastObj()
{
    AssetNode tmp;
    for(std::list<AssetNode>::iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        tmp = *itr;
        if(tmp.id == objOrder.top())
        {
            //Remove from editor
            objects.remove(tmp);
            objOrder.pop();
            delete GetTreeViewRoot(OBJECTLIST, tmp.name.toStdString());

            //Remove from engine
            engine->DeleteUnitByID(tmp.id);
        }
    }
}

QTreeWidgetItem *MainWindow::GetTreeViewRoot(char treeView, const std::string &rowName)
{
    QList<QTreeWidgetItem*> clist;

    switch(treeView)
    {
    case OBJECTLIST:
        clist = ui->tvObjList->findItems(rowName.c_str(), Qt::MatchExactly|Qt::MatchRecursive, 0);
        break;
    case BASEASSETS:
        clist = ui->tvBaseAssets->findItems(rowName.c_str(), Qt::MatchExactly|Qt::MatchRecursive, 0);
        break;
    case UIELEMENTS:
        clist = ui->tvUIElements->findItems(rowName.c_str(), Qt::MatchExactly|Qt::MatchRecursive, 0);
        break;
    default:
        clist = ui->tvRegisteredObjects->findItems(rowName.c_str(), Qt::MatchExactly|Qt::MatchRecursive, 0);
        break;
    }

    return clist.first();
}

AssetNode MainWindow::GetAsset(const std::string &name)
{
    return assets[name.c_str()];
}

AssetNode MainWindow::GetObjectInstance(const std::string &name) const
{
    for(std::list<AssetNode>::const_iterator itr = objects.begin(); itr != objects.end(); itr++)
    {
        if(itr->name.toStdString() == name)
            return *itr;
    }
}

void MainWindow::ResetTrees()
{
    //texture
    QTreeWidgetItem* itm = GetTreeViewRoot(BASEASSETS, "Texture");
    clearAllNodes(itm);
    //sound
    itm = GetTreeViewRoot(BASEASSETS, "Sound");
    clearAllNodes(itm);
    //Plugin
    itm = GetTreeViewRoot(BASEASSETS, "Plugin");
    clearAllNodes(itm);
    //sound
    itm = GetTreeViewRoot(BASEASSETS, "Script");
    clearAllNodes(itm);
    //physics
    itm = GetTreeViewRoot(BASEASSETS, "Physics");
    clearAllNodes(itm);

    //unit
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Unit");
    clearAllNodes(itm);
    //trigger
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Trigger");
    clearAllNodes(itm);
    //locale
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Locale");
    clearAllNodes(itm);
    //ui
    itm = GetTreeViewRoot(REGISTEREDOBJS, "UI");
    clearAllNodes(itm);
    //cursor
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Cursor");
    clearAllNodes(itm);
    //cursorset
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Cursorset");
    clearAllNodes(itm);
    //layer
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Layer");
    clearAllNodes(itm);
    //layerset
    itm = GetTreeViewRoot(REGISTEREDOBJS, "Layerset");
    clearAllNodes(itm);

    //clear trees
    if(tvBaseAssetsCount)
    {
        ui->tvBaseAssets->clear();
        tvBaseAssetsCount = 0;
        for(size_t i = 0; i < tvBaseAssets_bk->topLevelItemCount(); i++)
        {
            QTreeWidgetItem* tmp = new QTreeWidgetItem(*tvBaseAssets_bk->topLevelItem(i));
            ui->tvBaseAssets->addTopLevelItem(tmp);
        }
    }
    if(tvRegisteredObjsCount)
    {
        ui->tvRegisteredObjects->clear();
        tvRegisteredObjsCount = 0;
        for(size_t i = 0; i < tvRegisteredObjs_bk->topLevelItemCount(); i++)
        {
            QTreeWidgetItem* tmp =new QTreeWidgetItem(*tvRegisteredObjs_bk->topLevelItem(i));
            ui->tvRegisteredObjects->addTopLevelItem(tmp);
        }
    }
    if(tvObjsListCount)
    {
        ui->tvObjList->clear();
        tvObjsListCount = 0;
    }
    if(tvUIElementsCount)
    {
        ui->tvUIElements->clear();
        tvUIElementsCount = 0;
    }
}

void MainWindow::on_action_Exit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_pbModBrowse_clicked()
{
    size_t tmpIndex = 0;
    //Stop drawing timer
    if(frame)
    {
        frameThread->quit();
        frameThread->wait();
        delete frame;
    }

    //Proceed to loading data
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

    //Let's clear the asset lists if they were filled in a previous load
    ResetTrees();

    //Let's load presaved assets
    loadProjectObjects();

    //Load some basic video settings so we can get the engine drawing!
    loadVideoSettings();

    //Start asynchronoush drawing of game objects
    frame = new QTimer(0);
    connect(frame, SIGNAL(timeout()), this, SLOT(drawObjs()));
    frame->setInterval(100);
    frame->moveToThread(frameThread);
    connect(frameThread, SIGNAL(started()), frame, SLOT(start()));
    frameThread->start();


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

      //Now we start updating the main window
      AddTreeViewItem(BASEASSETS, ui->leTexName->text().toStdString(), false, GetTreeViewRoot(BASEASSETS, "Texture"));
      RegisterAsset(ui->leTexName->text().toStdString(), modName + "/Textures" + text_fileName + ".txt", OBJTYPE|TEXTURE);
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

void MainWindow::loadProjectObjects()
{
    QDir src(modRootPath.c_str());
    QFileInfo info;
    QStringList objLst;
    QString objName;
    AssetNode tmp;

    //Set the filter for the file list to the Descriptor format
    src.setNameFilters(QStringList() << "*.txt");

    //Load plugins. First, enter target directory!
    src.cd("plugins");
    objLst = src.entryList();
    registerProjectObjects(objLst, modRootPath + "/plugins", CODETYPE|PLUGIN);

    //Load units
    src.cdUp();
    src.cd(modName.c_str());
    src.cd("Creatures");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Creatures", OBJTYPE|UNIT);

    //Load textures
    src.cdUp();
    src.cd("Textures");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Textures", OBJTYPE|TEXTURE);

    //Load sound
    src.cdUp();
    src.cd("Sounds");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Sounds", OBJTYPE|SOUND);

    //Load scripts
    src.cdUp();
    src.cd("Scripts");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Textures", CODETYPE|SCRIPT);

    //Load cursor
    src.cdUp();
    src.cd("Cursor");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Cursor", OBJTYPE|CURSOR);

    //Load physics
    src.cdUp();
    src.cd("Physics");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Cursor", OBJTYPE|PHYSICS);

    //Load ui elements
    src.cdUp();
    src.cd("UI_elements");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/UI_elements", UITYPE);

    //Load uis
    src.cdUp();
    src.cd("UI");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/UI", UITYPE);

    //Load layers
    src.cdUp();
    src.cd("Layers");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Layers", OBJTYPE|LAYER);

    //Load triggers
    src.cdUp();
    src.cd("Levels/Triggers");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Levels/Triggers", OBJTYPE|TRIGGER);

    //Load sets
    src.setNameFilters(QStringList() << ".set");

    //Load layerset
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Layers", OBJTYPE|LAYERSET);

    //Load cursorset
    src.cdUp();
    src.cd("Cursor");
    objLst = src.entryList();
    registerProjectObjects(objLst, modPath + "/Cursor", OBJTYPE|CURSORSET);

    //Load levels!


}

void MainWindow::loadVideoSettings()
{
    //Basic variables
    std::string rootDir, modLoc, saveLoc, gameName, icon, renderQuality, driver;
    size_t fps, width, height, bpp, blitlvls, freq, chan, chunksize, displayIndex, displayCount, screenmode, vol;
    data_base *gameDOM = DOM;

    rootDir = modRootPath;

    modLoc = gameDOM->GetStrFromData("selected_mod");
    gameName = gameDOM->GetStrFromData("game_name");
    icon = gameDOM->GetStrFromData("icon");
    displayIndex = gameDOM->GetIntFromData("current_display");
    displayCount = gameDOM->GetIntFromData("display_count");
    renderQuality = gameDOM->GetStrFromData("render_quality");
    fps = gameDOM->GetIntFromData("frames_per_second");
    width = gameDOM->GetIntFromData("screen_width");
    height = gameDOM->GetIntFromData("screen_height");
    bpp = gameDOM->GetIntFromData("screen_bpp");
    blitlvls = gameDOM->GetIntFromData("blit_levels");
    screenmode = gameDOM->GetIntFromData("screen_mode");
    driver = gameDOM->GetStrFromData("video_driver");
    freq = gameDOM->GetIntFromData("frequency");
    chan = gameDOM->GetIntFromData("channels");
    chunksize = gameDOM->GetIntFromData("chunk_size");
    vol = gameDOM->GetIntFromData("sound_volume");


    engine->SetInfo(rootDir, modLoc, saveLoc, gameName, icon, renderQuality,
                    displayCount, displayIndex, fps, width, height, bpp,
                    blitlvls, screenmode, driver, freq, chan, chunksize);
    engine->SetSoundVolume(vol);
    engine->initSubSys();
    engine->init();
    engine->ShowWindow(false);
}

void MainWindow::registerProjectObjects(const QStringList &lst, const std::string &path, size_t type)
{
    data_base file;
    std::string name, textbox_file, rowName;
    bool isSet = false;
    char treeView = 0;
    for(size_t i = 0; i < lst.count(); i++)
    {
        /*
         * */
        file.OpenFile((path + "/" + lst[i].toStdString()).c_str());
        if(lst[i].toStdString().find("set") < lst[i].size())
            isSet = true;

        switch(type)
        {
        //All unit kind of objects
        case UNIT:
        case OBJECT:
        case PROJECTILE:
        case OBJTYPE|UNIT:
        case OBJTYPE|OBJECT:
        case OBJTYPE|PROJECTILE:
            name = file.GetStrFromData("unit_name");
            treeView = REGISTEREDOBJS;
            rowName = "Unit";
            goto default_actions;
            //All triggers
        case TRIGGER:
        case OBJTYPE|TRIGGER:
            name = file.GetStrFromData("trigger_name");
            treeView = REGISTEREDOBJS;
            rowName = "Trigger";
            goto default_actions;
            //All cursors
        case CURSOR:
        case OBJTYPE|CURSOR:
            if(isSet)
                break;
            name = file.GetStrFromData("cur_name");
            treeView = REGISTEREDOBJS;
            rowName = "Cursor";
            goto default_actions;
        case LAYER:
        case OBJTYPE|LAYER:
            if(isSet)
                break;
            name = file.GetStrFromData("layer_name");
            treeView = REGISTEREDOBJS;
            rowName = "Layer";
            goto default_actions;
        case UITYPE:
        case UITYPE|BUTTON:
        case UITYPE|TEXTBOX:
            file.CloseFile();
            textbox_file = lst[i].toStdString();
            textbox_file.find("_button.txt") && textbox_file.find("_button.txt") < textbox_file.size() ? textbox_file = textbox_file.substr(0, textbox_file.find("_button.txt")) + ".txt" : textbox_file = textbox_file;
            file.OpenFile((path + "/" + textbox_file).c_str());
            name = textbox_file;
            treeView = REGISTEREDOBJS;
            rowName = "UI";
            goto default_actions;
        case LAYERSET:
        case OBJTYPE|LAYERSET:
            treeView = REGISTEREDOBJS;
            rowName = "Layerset";
            goto catch_all;
            //All sounds
        case SOUND:
        case OBJTYPE|SOUND:
            treeView = BASEASSETS;
            rowName = "Sound";
            goto catch_all;
            //All textures
        case TEXTURE:
        case OBJTYPE|TEXTURE:
            treeView = BASEASSETS;
            rowName = "Texture";
            goto catch_all;
        case PHYSICS:
        case OBJTYPE|PHYSICS:
            treeView = BASEASSETS;
            rowName = "Physics";
            goto catch_all;
        case CODETYPE|PLUGIN:
            treeView = BASEASSETS;
            rowName = "Plugin";
            goto catch_all;
        case CODETYPE|SCRIPT:
            treeView = BASEASSETS;
            rowName = "Script";
            goto catch_all;
        case CURSORSET:
        case OBJTYPE|CURSORSET:
            treeView = REGISTEREDOBJS;
            rowName = "Cursorset";

            catch_all:
            textbox_file = lst[i].toStdString();
            textbox_file.find(".set") && textbox_file.find(".set") <= textbox_file.size() ? textbox_file = textbox_file.substr(0, textbox_file.find("set")) : textbox_file = textbox_file;
            name = textbox_file;
            goto default_actions;
        default:
            default_actions:
            RegisterAsset(name, getRelPath(path) + "/" + lst[i].toStdString(), type);
            AddTreeViewItem(treeView, name, false, GetTreeViewRoot(treeView, rowName));
            break;
        }
    }
}

void MainWindow::clearAll(QTreeWidgetItem *root)
{
    //Null case
    if(root == NULL)
        return;

    if(root->childCount() == 0)
    {
        AssetNode tmp = assets[root->text(0)];
        assets.erase(root->text(0));
        return;
    }

    if(root->childCount() > 0)
    {
        for(size_t i = 0; i < root->childCount(); i++)
        {
            clearAll(root->child(i));
        }
        return;
    }
    return;
}

void MainWindow::clearAllNodes(QTreeWidgetItem *root)
{
    for(size_t i = 0; i < root->childCount(); i++)
    {
        clearAll(root->child(i));
    }
}

std::string MainWindow::getRelPath(const std::string &path)
{
    size_t start = path.find(modRootPath);
    return path.substr(start, path.size() - start);
}

size_t MainWindow::GetBlitOrderFromType(size_t type)
{
    switch(type)
    {
    //All unit kind of objects
    case UNIT:
    case OBJECT:
    case PROJECTILE:
    case OBJTYPE|UNIT:
    case OBJTYPE|OBJECT:
    case OBJTYPE|PROJECTILE:
    //All gameplay accessories
    case TRIGGER:
    case OBJTYPE|TRIGGER:
    case SOUND:
    case OBJTYPE|SOUND:
        return 20;
    //All interface components
    case CURSOR:
    case OBJTYPE|CURSOR:
    case UITYPE:
    case UITYPE|BUTTON:
    case UITYPE|TEXTBOX:
        return 40;
    //All background components
    case LAYER:
    case OBJTYPE|LAYER:
    case LAYERSET:
    case OBJTYPE|LAYERSET:
        return 10;
    defaut:
    //Anything else at same level as most units in the game
    return 20;
    }
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
        tmp.WriteValue(modName + "/Sounds" + file + ".txt", "file_loc");
        break;
    case 1:
        tmp.WriteValue("e", "sound_type");
        tmp.WriteValue(modName + "/Sounds" + file + ".txt", "file_loc");
        break;
    case 2:
        tmp.WriteValue("a", "sound_type");
        tmp.WriteValue(modName + "/Sounds" + file + ".txt", "file_loc");
        break;
    default:
        break;
    }
    tmp.WriteValue(intToStr(ui->sbSoundX->value()), "sound_x");
    tmp.WriteValue(intToStr(ui->sbSoundY->value()), "sound_y");
    tmp.WriteValue(intToStr(ui->sbSoundRange->value()), "range");
    //Save file and close it!
    tmp.CloseFile();

    //Now we start updating the main window
    AddTreeViewItem(BASEASSETS, file, false, GetTreeViewRoot(BASEASSETS, "Sound"));
    RegisterAsset(file, modName + "/Sounds" + file + ".txt", OBJTYPE|SOUND);
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

        //Now we start updating the main window
        AddTreeViewItem(BASEASSETS, file, false, GetTreeViewRoot(BASEASSETS, "Plugin"));
        RegisterAsset(file, modRootPath + file, CODETYPE|PLUGIN);

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

        //Now we start updating the main window
        AddTreeViewItem(BASEASSETS, file, false, GetTreeViewRoot(BASEASSETS, "Script"));
        RegisterAsset(file, p.path.substr(p.path.find(".txt")), CODETYPE|SCRIPT);

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

    //Now we start updating the main window
    AddTreeViewItem(BASEASSETS, ui->lePhysName->text().toStdString(), false, GetTreeViewRoot(BASEASSETS, "Physics"));
    RegisterAsset(ui->lePhysName->text().toStdString(), path, PHYSICS);
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
    if(fullPath.empty())
        return fullPath;
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
        unit.SetRootLocation(modName, modPath);
        unit.exec();
        break;
    }
    case 1://Cursor
    case 2://Cursor set
    {
        cursorsettings cursor(this);
        cursor.SetRootLocation(modName, modPath);
        cursor.exec();
        break;
    }
    case 3://Layer
    case 4://Layer set
    {
        Layersettings settings(this);
        settings.SetRootLocation(modName, modPath);
        settings.exec();
        break;
    }
    case 5://Locale
        break;
    case 6://Trigger
    {
        trigger_settings trigger;
        trigger.SetRootLocation(modName, modPath);
        trigger.exec();
        break;
    }
    case 8://UI
    {
        UI_Elements ui_stuff(this);
        ui_stuff.SetRootLocation(modName, modPath);
        ui_stuff.exec();
        break;
    }
    default:
        break;
    }
}

std::string getType(char type)
{
    switch(type)
    {
    //All unit kind of objects
    case UNIT:
    case OBJECT:
    case PROJECTILE:
    case OBJTYPE|UNIT:
    case OBJTYPE|OBJECT:
    case OBJTYPE|PROJECTILE:
        return "Unit";
    //All textures
    case TEXTURE:
    case OBJTYPE|TEXTURE:
        return "Texture";
    //All triggers
    case TRIGGER:
    case OBJTYPE|TRIGGER:
        return "Trigger";
     //All sounds
    case SOUND:
    case OBJTYPE|SOUND:
        return "Sound";
    //All cursors
    case CURSOR:
    case OBJTYPE|CURSOR:
        return "Cursor";
    case LAYER:
    case OBJTYPE|LAYER:
        return "Layer";
    case LAYERSET:
    case OBJTYPE|LAYERSET:
        return "Layerset";
    case UITYPE:
        return "UI";
    case CODETYPE|PLUGIN:
        return "Plugin";
    case CODETYPE|SCRIPT:
        return "Script";
    case PHYSICS:
    case OBJTYPE|PHYSICS:
        return "Physics";
    case UITYPE|BUTTON:
        return "Button";
    case UITYPE|TEXTBOX:
        return "Textbox";
    default:
        break;
    }
    return "None";
}

void MainWindow::on_twTabs_currentChanged(int index)
{
    if(ui->twTabs->tabText(index) == "Level Designer")
    {
        ui->tvObjList->addTopLevelItem(GetTreeViewRoot(REGISTEREDOBJS, "Unit"));
        ui->tvObjList->addTopLevelItem(GetTreeViewRoot(REGISTEREDOBJS, "Trigger"));
        ui->tvObjList->addTopLevelItem(GetTreeViewRoot(REGISTEREDOBJS, "Layer"));
        ui->tvObjList->addTopLevelItem(GetTreeViewRoot(REGISTEREDOBJS, "Layerset"));
    }
    else if(ui->twTabs->tabText(index) == "UI Designer")
    {
        ui->tvObjList->addTopLevelItem(GetTreeViewRoot(REGISTEREDOBJS, "UI"));
    }
}

void MainWindow::on_tvRegisteredObjects_itemEntered(QTreeWidgetItem *item, int column)
{

}

void remove_asset_contents(const std::string& rootPath, const QString &path, size_t type)
{
    data_base file(path.toStdString().c_str());
    size_t count;
    std::string buffer, tmp;

    switch(type)
    {
    //All textures
    case TEXTURE:
    case OBJTYPE|TEXTURE:
        tmp = rootPath + "/" + file.GetStrFromData("tex_texture");
        remove(tmp.c_str());
        file.CloseFile();
        remove(path.toStdString().c_str());
        break;
    //All sounds
    case SOUND:
    case OBJTYPE|SOUND:
        tmp = rootPath + "/" + file.GetStrFromData("file_loc");
        remove(tmp.c_str());
        file.CloseFile();
        remove(path.toStdString().c_str());
        break;
    case CODETYPE|PLUGIN:
    {
        file.CloseFile();
        tmp = (path.toStdString().substr(path.toStdString().rfind("/")) + "plugins.txt");
        file.OpenFile(tmp.c_str());
        count = file.GetIntFromData("module_number");
        for(size_t i = 0; i < count; i++)
        {
            if(file.GetStrFromData("module_" + intToStr(i)) == path.toStdString())
            {
                size_t pos = file.GetStrBuffer().find("module_" + intToStr(i));
                size_t offset = std::string("module_" + intToStr(i)).size();
                size_t remaining = file.GetStrBuffer().size() - offset;
                file.CloseFile();
                file.OpenFile(tmp.c_str(), false);
                file.WriteValue(intToStr(count - 1), "module_number");
                file.CloseFile();
                file.OpenFile(tmp.c_str());
                buffer += file.GetStrBuffer().substr(pos);
                buffer += file.GetStrBuffer().substr(pos + offset, remaining);

                for(size_t j = 0; j < count; j++)
                {
                    buffer.replace(buffer.find("module_" + intToStr(j)), std::string("module_" + intToStr(j)).size(), "module_" + intToStr(j-1));
                }
                file.CloseFile();
                file.OpenFileForQuickWrite(tmp.c_str());
                file.WriteValueAndFlush(buffer);
            }
        }

        remove((path.toStdString() + ".txt").c_str());
    }
    case CODETYPE|SCRIPT:
    //All unit kind of objects
    case UNIT:
    case OBJECT:
    case PROJECTILE:
    case OBJTYPE|UNIT:
    case OBJTYPE|OBJECT:
    case OBJTYPE|PROJECTILE:
    //All triggers
    case TRIGGER:
    case OBJTYPE|TRIGGER:
    //All cursors
    case CURSOR:
    case OBJTYPE|CURSOR:
    case LAYER:
    case OBJTYPE|LAYER:
    case LAYERSET:
    case OBJTYPE|LAYERSET:
    case UITYPE:
    case UITYPE|BUTTON:
    case UITYPE|TEXTBOX:
    case PHYSICS:
    case OBJTYPE|PHYSICS:
    default:
        file.CloseFile();
        remove(path.toStdString().c_str());
        break;
    }
}

void MainWindow::on_pbDelAsset_clicked()
{
    RemoveAsset(ui->tvBaseAssets->currentItem()->text(0).toStdString());
    delete ui->tvBaseAssets->currentItem();
    if(tvBaseAssetsCount > 0)
        tvBaseAssetsCount--;
}

void MainWindow::on_pbDelObj_clicked()
{
    RemoveAsset(ui->tvRegisteredObjects->currentItem()->text(0).toStdString());
    delete ui->tvRegisteredObjects->currentItem();
    if(tvRegisteredObjsCount > 0)
        tvRegisteredObjsCount--;
}

void MainWindow::on_sbWidth_editingFinished()
{
    size_t width = ui->gvTexturePreview->frameWidth();

    if(width > ui->sbWidth->value())
        ui->sbFrames->setValue(width / ui->sbWidth->value());
}

void MainWindow::on_sbWidth_valueChanged(int arg1)
{
    size_t width = ui->gvTexturePreview->frameWidth();

    if(width > ui->sbWidth->value())
        ui->sbFrames->setValue(width / ui->sbWidth->value());
}

char getTreeByType(byte type, byte subtype)
{
    if(subtype == BASEASSET)
        switch(type)
        {
        //All unit kind of objects
        case UNIT:
        case OBJECT:
        case PROJECTILE:
        case OBJTYPE|UNIT:
        case OBJTYPE|OBJECT:
        case OBJTYPE|PROJECTILE:
            //All triggers
        case TRIGGER:
        case OBJTYPE|TRIGGER:
            //All cursors
        case CURSOR:
        case OBJTYPE|CURSOR:
        case LAYER:
        case OBJTYPE|LAYER:
        case LAYERSET:
        case OBJTYPE|LAYERSET:
        case UITYPE:
        case UITYPE|BUTTON:
        case UITYPE|TEXTBOX:
            return REGISTEREDOBJS;
            //All textures
        case TEXTURE:
        case OBJTYPE|TEXTURE:
            //All sounds
        case SOUND:
        case OBJTYPE|SOUND:
        case CODETYPE|PLUGIN:
        case CODETYPE|SCRIPT:
        case PHYSICS:
        case OBJTYPE|PHYSICS:
            return BASEASSETS;
        default:
            return REGISTEREDOBJS;
        }
    else if(subtype == INSTANCE)
        switch(type)
        {
        //All unit kind of objects
        case UNIT:
        case OBJECT:
        case PROJECTILE:
        case OBJTYPE|UNIT:
        case OBJTYPE|OBJECT:
        case OBJTYPE|PROJECTILE:
            //All triggers
        case TRIGGER:
        case OBJTYPE|TRIGGER:
            //All cursors
        case CURSOR:
        case OBJTYPE|CURSOR:
        case LAYER:
        case OBJTYPE|LAYER:
        case LAYERSET:
        case OBJTYPE|LAYERSET:
            return OBJECTLIST;
        case UITYPE:
        case UITYPE|BUTTON:
        case UITYPE|TEXTBOX:
            return UIELEMENTS;
        default:
            return OBJECTLIST;
        }
}

void MainWindow::on_gvGamePreview_customContextMenuRequested(const QPoint &pos)
{
    AssetMenu menu;
    //QPoint p = this->mapTo(ui->gbGamePreview->window(), pos);//Because mapto is useless
    QPoint p(pos.x() + this->window()->x() + ui->gbGamePreview->x() + 10,
             pos.y() + this->window()->y() + ui->gbGamePreview->y() + menu.height() / 2);
    menu.LoadItems(*ui->tvRegisteredObjects);
    menu.SetPosition(p.x(), p.y());
    menu.exec();
}


void MainWindow::on_pbClearUI_clicked()
{
    ui->tvUIElements->clear();
}

void MainWindow::drawObjs()
{
    /*QRect r = ui->gvGamePreview->geometry();
    QPoint p(this->window()->x() + r.x(),
             this->window()->y() + r.y());
    engine->SetWindowPosition(p.x(), p.y());
    engine->ShowWindow(true);
    engine->drawWorld();*/
    worldPrev->clear();
    engine->drawWorld();
    worldItm = worldPrev->addPixmap(QPixmap::fromImage(QImage(( const uchar*)engine->GetFrameBuffer(),engine->GetScreenWidth(), engine->GetScreenHeight(), QImage::Format_RGBA8888)));
    ui->gvGamePreview->update();
    ui->gvGamePreview->show();
}
