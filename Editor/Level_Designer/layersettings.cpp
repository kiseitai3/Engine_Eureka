#include "layersettings.h"
#include "ui_layersettings.h"
#include "mainwindow.h"
#include "data_base.h"
#include <QMessageBox>

Layersettings::Layersettings(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::Layersettings)
{
    ui->setupUi(this);
    open = new QFileDialog();
    win = parent;
}

Layersettings::~Layersettings()
{
    if(open)
        delete open;
    delete ui;
}

void Layersettings::SetRootLocation(const std::string &modName, const std::string &modPath)
{
    ModName = modName;
    ModPath = modPath;
}

void Layersettings::LoadSet(const std::string &loc)
{
    data_base DOM(loc.c_str());
    size_t count = DOM.GetIntFromData("layer_count");
    std::string name;

    for(size_t i = 0; i < count; i++)
    {
        name = DOM.GetStrFromData("cursor_" + intToStr(i) + "_file");
        name = extract_file_name(name);
        name = name.substr(name.find(".txt"));
        ui->lstSet->addItem(name.c_str());
    }

    ui->leLayerName->setText(DOM.GetStrFromData("layer_set_name").c_str());
}

void Layersettings::LoadLayer(const std::string &loc)
{
    data_base DOM(loc.c_str());

    ui->leLayerName->setText(DOM.GetStrFromData("layer_name").c_str());
    ui->leTexture->setText(DOM.GetStrFromData("texture_file").c_str());
    ui->sbX->setValue(DOM.GetIntFromData("x"));
    ui->sbY->setValue(DOM.GetIntFromData("y"));
    ui->sbZ->setValue(DOM.GetIntFromData("z"));
}

void Layersettings::on_pbSave_clicked()
{
    if(ui->leLayerName->text() == "" || ui->leTexture->text() == "")
    {
       QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
    else
    {
        std::string file = ModPath + "/Layers/" + ui->leLayerName->text().toStdString() + ".txt";
        std::string texture_file = extract_file_name(ui->leTexture->text().toStdString());

        copyfile(ModPath + "/Layers/template_layer.txt", file);
        data_base writer(file.c_str(), false);

        writer.WriteValue(ui->leLayerName->text().toStdString(), "layer_name");
        writer.WriteValue(ModName + "/Layers/" + texture_file, "texture_file");
        writer.WriteValue(intToStr(ui->sbX->value()), "x");
        writer.WriteValue(intToStr(ui->sbY->value()), "y");
        writer.WriteValue(intToStr(ui->sbZ->value()), "z");

        //Now we start updating the main window
        win->AddTreeViewItem(REGISTEREDOBJS, ui->leLayerName->text().toStdString(), false, win->GetTreeViewRoot(REGISTEREDOBJS, "Layer"));
        win->RegisterAsset(ui->leLayerName->text().toStdString(), file, OBJTYPE|LAYER);

        writer.CloseFile();
    }
}

void Layersettings::on_pbBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTexture->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void Layersettings::on_pbSaveAdd_clicked()
{
    if(ui->leLayerName->text() == "" || ui->leTexture->text() == "")
    {
       QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
    else
    {
        on_pbSave_clicked();
        ui->lstSet->addItem(ui->leLayerName->text());
    }
}

void Layersettings::on_pbSetAdd_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    std::string file_name = extract_file_name(open->getOpenFileName(NULL, "Select Layer Descriptor File","" ,"All Files (*.*);; Cursor Descriptor (*.txt)").toStdString());
    file_name = file_name.substr(file_name.find(".txt"));
    ui->lstSet->addItem(file_name.c_str());
    ui->lstSet->setCurrentIndex(ui->lstSet->currentIndex());
}

void Layersettings::on_pbSetRemove_clicked()
{
    delete ui->lstSet->currentItem();
}

void Layersettings::on_pbSetOpen_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    LoadSet(open->getOpenFileName(NULL, "Select Layer Set Descriptor File","" ,"All Files (*.*);; Layer Set Descriptor (*.set)").toStdString());
}

void Layersettings::on_pbSetSave_clicked()
{
    if(ui->leNameSet->text() == "")
    {
       QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
    else
    {
        std::string file = ModPath + "/Layers/" + ui->leNameSet->text().toStdString() + ".set";

        copyfile(ModPath + "/Layers/template_layerset.txt", file);
        data_base writer(file.c_str(), false);

        writer.WriteValue(intToStr(ui->lstSet->count()), "layer_count");
        for(size_t i = 0; i < ui->lstSet->count(); i++)
        {
            writer.WriteValue(ModName + "/Layers/" + ui->lstSet->item(i)->text().toStdString() + ".txt", "layer_" + intToStr(i) + "_file");
        }

        writer.WriteValue(ui->leNameSet->text().toStdString(), "layer_set_name");

        //Now we start updating the main window
        win->AddTreeViewItem(REGISTEREDOBJS, ui->leNameSet->text().toStdString(), false, win->GetTreeViewRoot(REGISTEREDOBJS, "Layerset"));
        win->RegisterAsset(ui->leNameSet->text().toStdString(), file, OBJTYPE|LAYERSET);

        writer.CloseFile();
    }
}
