#include "cursorsettings.h"
#include "ui_cursorsettings.h"
#include <QMessageBox>

cursorsettings::cursorsettings(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::cursorsettings)
{
    ui->setupUi(this);
    open = new QFileDialog();
    win = parent;
}

void cursorsettings::SetRootLocation(const std::string &modName, const std::string &modPath)
{
    ModName = modName;
    ModPath = modPath;
}

void cursorsettings::LoadSet(const std::string &loc)
{
    data_base DOM(loc.c_str());
    size_t count = DOM.GetIntFromData("cursor_count");

    std::string name = extract_file_name(loc);
    name = name.substr(name.find(".txt"));
    ui->leNameSet->setText(name.c_str());

    for(size_t i = 0; i < count; i++)
    {
        ui->lstSet->addItem(DOM.GetStrFromData("cursor_" + intToStr(i) + "_name").c_str());
    }
}

void cursorsettings::LoadCursor(const std::string &loc)
{
    data_base DOM(loc.c_str());

    ui->leName->setText(DOM.GetStrFromData("cur_name").c_str());
    ui->leSound->setText(DOM.GetStrFromData("cur_sound_file").c_str());
    ui->leTexture->setText(DOM.GetStrFromData("cur_texture").c_str());
    ui->sbFrames->setValue(DOM.GetIntFromData("cur_fps"));
}

cursorsettings::~cursorsettings()
{
    if(open)
        delete open;
    delete ui;
}

void cursorsettings::on_pbSound_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leSound->setText(open->getOpenFileName(NULL, "Select Sound Descriptor File","" ,"All Files (*.*);; Sound Descriptor (*.txt)"));
}

void cursorsettings::on_pbTexture_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTexture->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void cursorsettings::on_pbCreate_clicked()
{
    if(ui->leName->text() == "")
    {
       QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
    else
    {
        std::string file = ModPath + "/Cursor/" + ui->leName->text().toStdString() + ".txt";
        std::string sound_file = extract_file_name(ui->leSound->text().toStdString());
        std::string texture_file = extract_file_name(ui->leTexture->text().toStdString());

        copyfile(ModPath + "/Cursor/template_cursor.txt", file);
        data_base writer(file.c_str(), false);

        writer.WriteValue(ui->leName->text().toStdString(), "cur_name");
        writer.WriteValue(ModName + "/Sounds/" + sound_file, "cur_sound_file");
        writer.WriteValue(ModName + "/Textures/" + texture_file, "cur_texture");
        writer.WriteValue(intToStr(ui->sbFrames->value()), "cur_fps");

        //Now we start updating the main window
        win->AddTreeViewItem(REGISTEREDOBJS, ui->leName->text().toStdString(), false, win->GetTreeViewRoot(REGISTEREDOBJS, "Cursor"));

        writer.CloseFile();
    }
}

void cursorsettings::on_pbCreateAdd_clicked()
{
    if(ui->leName->text() == "")
    {
       QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
    else
    {
        on_pbCreate_clicked();
        ui->lstSet->addItem(ui->leName->text());
    }
}

void cursorsettings::on_pbRemove_clicked()
{
    delete ui->lstSet->currentItem();
}

void cursorsettings::on_pbAdd_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    std::string file_name = extract_file_name(open->getOpenFileName(NULL, "Select Cursor Descriptor File","" ,"All Files (*.*);; Cursor Descriptor (*.txt)").toStdString());
    file_name = file_name.substr(file_name.find(".txt"));
    ui->lstSet->addItem(file_name.c_str());
    ui->lstSet->setCurrentIndex(ui->lstSet->currentIndex());
}

void cursorsettings::on_pbLoadSet_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    LoadSet(open->getOpenFileName(NULL, "Select Cursor Set Descriptor File","" ,"All Files (*.*);; Cursor Set Descriptor (*.txt)").toStdString());
}

void cursorsettings::on_pbSaveSet_clicked()
{
    if(ui->leNameSet->text() == "")
    {
       QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    }
    else
    {
        std::string file = ModPath + "/Cursor/" + ui->leNameSet->text().toStdString() + ".txt";

        copyfile(ModPath + "/Cursor/template_cursor_set.txt", file);
        data_base writer(file.c_str(), false);

        writer.WriteValue(intToStr(ui->lstSet->count()), "cur_count");
        for(size_t i = 0; i < ui->lstSet->count(); i++)
        {
            writer.WriteValue(ui->lstSet->item(i)->text().toStdString(), "cursor_" + intToStr(i) + "_name");
            writer.WriteValue(ModName + "/Cursor/" + ui->lstSet->item(i)->text().toStdString() + ".txt", "cursor_" + intToStr(i) + "_file");
        }

        //Now we start updating the main window
        win->AddTreeViewItem(REGISTEREDOBJS, ui->leNameSet->text().toStdString(), false, win->GetTreeViewRoot(REGISTEREDOBJS, "Cursorset"));

        writer.CloseFile();
    }
}
