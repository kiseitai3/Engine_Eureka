#include "mod_picker.h"
#include "ui_mod_picker.h"

mod_picker::mod_picker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mod_picker)
{
    ui->setupUi(this);
}

void mod_picker::AddMod(const std::string& name)
{
    ui->lstMods->addItem(name.c_str());
}

void mod_picker::AutoSelect()
{
    ui->lstMods->setCurrentItem(ui->lstMods->item(0));
}

size_t mod_picker::getSelectedModIndex() const
{
    return ui->lstMods->currentIndex().row();
}

std::string mod_picker::getSelectedMod() const
{
    return ui->lstMods->currentItem()->text().toStdString();
}

mod_picker::~mod_picker()
{
    delete ui;
}





std::string getModName(const data_base& dom, std::string& description)
{
    mod_picker picker;
    size_t modCount = dom.GetIntFromData("mod_number");

    //Iterate through list of mods
    for(size_t i = 0; i < modCount; i++)
    {
        picker.AddMod(dom.GetStrFromData("mod_" + intToStr(i) + "_name"));
    }

    //Select first item
    picker.AutoSelect();

    //Show the dialog
    picker.exec();

    //Return the selected mod name!
    description = dom.GetStrFromData("mod_" + intToStr(picker.getSelectedModIndex()) + "_description");
    return picker.getSelectedMod();
}

void mod_picker::on_pbAddMod_clicked()
{
    ui->lstMods->addItem(ui->leModName->text());
}

void mod_picker::on_buttonBox_accepted()
{
    this->hide();
}
