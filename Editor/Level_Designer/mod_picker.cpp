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

std::vector<std::string> mod_picker::getStringList() const
{
    std::vector<std::string> data;

    for(size_t i = 0; i < ui->lstMods->count(); i++)
    {
        data.push_back(ui->lstMods->item(i)->text().toStdString());
    }

    return data;
}

std::string mod_picker::getSelectedMod() const
{
    return ui->lstMods->currentItem()->text().toStdString();
}

void mod_picker::setDialogTitle(const std::string& title)
{
    ui->groupBox->setTitle(title.c_str());
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
    ui->lstMods->setCurrentItem(ui->lstMods->item(ui->lstMods->count() - 1));
}

void mod_picker::on_buttonBox_accepted()
{
    this->hide();
}

std::vector<std::string> getList(const SearchPacket& p,
                                 const std::string title,
                                 size_t searchType)
{
    mod_picker dialog;
    data_base f(p.path.c_str());

    switch(searchType)
    {
    case PARTIALSEARCH:
        for(size_t i = 0; i < f.GetIntFromData(p.term); i++)
        {
            dialog.AddMod(f.GetStrFromData(p.prefix + intToStr(i)));
        }
        break;
    case FULLSEARCH:
        for(size_t i = 0; i < f.GetIntFromData(p.term); i++)
        {
            dialog.AddMod(f.GetStrFromData(p.prefix + intToStr(i) + p.suffix));
        }
        break;
    default:
        break;
    }

    dialog.setDialogTitle(title);

    dialog.exec();

    return dialog.getStringList();

}
