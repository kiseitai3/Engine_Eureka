#include "cursorsettings.h"
#include "ui_cursorsettings.h"

cursorsettings::cursorsettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cursorsettings)
{
    ui->setupUi(this);
    open = new QFileDialog();
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

    for(size_t i = 0; i < count; i++)
    {
        ui->lstSet->addItem(DOM.GetStrFromData("cursor_" + intToStr(i) + "_name").c_str());
    }
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
    std::string file = ModPath + "/Cursor/" + ui->leName->text().toStdString() + ".txt";
    std::string sound_file = extract_file_name(ui->leSound->text().toStdString());
    std::string texture_file = extract_file_name(ui->leTexture->text().toStdString());

    copyfile(ModPath + "/Cursor/template_cursor.txt", file);
    data_base writer(file.c_str(), false);

    writer.WriteValue(ui->leName->text().toStdString(), "cur_name");
    writer.WriteValue(ModName + "/Sounds/" + sound_file, "cur_sound_file");
    writer.WriteValue(ModName + "/Textures/" + texture_file, "cur_texture");
    writer.WriteValue(intToStr(ui->sbFrames->value()), "cur_fps");

    writer.CloseFile();
}

void cursorsettings::on_pbCreateAdd_clicked()
{
    on_pbCreate_clicked();
    ui->lstSet->addItem(ui->leName->text());
}

void cursorsettings::on_pbRemove_clicked()
{
    delete ui->lstSet->currentItem();
}

void cursorsettings::on_pbAdd_clicked()
{
    std::string file_name = extract_file_name(open->getOpenFileName(NULL, "Select Cursor Descriptor File","" ,"All Files (*.*);; Cursor Descriptor (*.txt)").toStdString());
    file_name = file_name.substr(file_name.find(".txt"));
    open->setFileMode(QFileDialog::AnyFile);
    ui->lstSet->addItem(file_name.c_str());
}

void cursorsettings::on_pbLoadSet_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    LoadSet(open->getOpenFileName(NULL, "Select Cursor Set Descriptor File","" ,"All Files (*.*);; Cursor Set Descriptor (*.txt)").toStdString());
}

void cursorsettings::on_pbSaveSet_clicked()
{
    std::string file = ModPath + "/Cursor/" + ui->leNameSet->text().toStdString() + ".txt";

    copyfile(ModPath + "/Cursor/template_cursor_set.txt", file);
    data_base writer(file.c_str(), false);

    writer.WriteValue(intToStr(ui->lstSet->count()), "cur_count");
    for(size_t i = 0; i < ui->lstSet->count(); i++)
    {
        writer.WriteValue("cursor_" + intToStr(i) + "_name = ;");
        writer.WriteValue("cursor_" + intToStr(i) + "_file = ;");

        writer.WriteValue(ui->lstSet->item(i)->text().toStdString(), "cursor_" + intToStr(i) + "_name");
        writer.WriteValue(ModName + "/Cursor/" + ui->lstSet->item(i)->text().toStdString() + ".txt", "cursor_" + intToStr(i) + "_file");
    }

    writer.CloseFile();
}
