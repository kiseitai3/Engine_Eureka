#include "trigger_settings.h"
#include "ui_trigger_settings.h"
#include "mainwindow.h"

trigger_settings::trigger_settings(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::trigger_settings)
{
    ui->setupUi(this);
    win = parent;
}

trigger_settings::~trigger_settings()
{
    delete ui;
}

void trigger_settings::SetRootLocation(const std::string &modName, const std::string &modPath)
{
    mod_name = modName;
    mod_path = modPath;
}

void trigger_settings::LoadTrigger(const std::string &file)
{
    data_base f(file.c_str());
    ui->leName->setText(f.GetStrFromData("trigger_name").c_str());
    ui->leScript->setText(f.GetStrFromData("trigger_script").c_str());
    ui->sbDuration->setValue(f.GetIntFromData("trigger_duration"));
    ui->sbH->setValue(f.GetIntFromData("trigger_height"));
    ui->sbW->setValue(f.GetIntFromData("trigger_width"));
    ui->sbX->setValue(f.GetIntFromData("trigger_x"));
    ui->sbY->setValue(f.GetIntFromData("trigger_y"));
    f.CloseFile();
}

void trigger_settings::on_pbScript_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leScript->setText(open->getOpenFileName(NULL, "Select Script File","" ,"All Files (*.*);; Trigger Script (*.py *.pyc *lua *luo)"));
}

void trigger_settings::on_pbSave_clicked()
{
    std::string path = mod_path + "/Levels/Triggers/" + ui->leName->text().toStdString() + ".txt";
    copyfile(mod_path + "/Levels/Triggers/template.txt", path);
    data_base f((mod_path + "/Levels/Triggers/" + ui->leName->text().toStdString() + ".txt").c_str(), false);
    f.WriteValue(ui->leName->text().toStdString(), "trigger_name");
    f.WriteValue(intToStr(ui->sbH->value()), "trigger_height");
    f.WriteValue(intToStr(ui->sbW->value()), "trigger_width");
    f.WriteValue(intToStr(ui->sbX->value()), "trigger_x");
    f.WriteValue(intToStr(ui->sbY->value()), "trigger_y");
    f.WriteValue(intToStr(ui->sbDuration->value()), "trigger_duration");
    f.WriteValue(ui->leScript->text().toStdString(), "trigger_script");
    f.CloseFile();

    //Register object
    win->AddTreeViewItem(REGISTEREDOBJS, ui->leName->text().toStdString(), false, win->GetTreeViewRoot(REGISTEREDOBJS, "Trigger"));
    win->RegisterAsset(ui->leName->text().toStdString(), path, TRIGGER);
}
