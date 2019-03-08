#include "unitsettings.h"
#include "ui_unitsettings.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

UnitSettings::UnitSettings(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::UnitSettings)
{
    doc = NULL;
    ui->setupUi(this);
    doc = new QFileDialog();
    unit_descriptor.type = NONETYPE;
    win = parent;
}

UnitSettings::~UnitSettings()
{
    delete ui;
}

void UnitSettings::LoadData(cstr file)
{
    data_base reader(file);
    AssetNode tmp;
    tmp.type = NONETYPE;

    //Update ui with unit's base stats
    ui->leUnitName->setText(reader.GetStrFromData("unit_name").c_str());
    ui->sbHP->setValue(reader.GetIntFromData("unit_hp"));
    ui->sbMana->setValue(reader.GetIntFromData("unit_mana"));
    ui->sbAD->setValue(reader.GetIntFromData("unit_ad"));
    ui->sbAP->setValue(reader.GetIntFromData("unit_ap"));
    ui->sbRange->setValue(reader.GetIntFromData("unit_range"));
    ui->sbVRange->setValue(reader.GetIntFromData("unit_vRange"));
    ui->sbMSpeed->setValue(reader.GetIntFromData("unit_mSpeed"));
    ui->sbBarH->setValue(reader.GetIntFromData("unit_hp_bar_h"));
    ui->sbBarW->setValue(reader.GetIntFromData("unit_hp_bar_w"));
    ui->cbHasBars->setChecked(reader.GetIntFromData("unit_has_bars"));
    on_cbHasBars_clicked();
    ui->cbHasBuffs->setChecked(reader.GetIntFromData("unit_has_buff"));
    ui->cbUnitMelee->setChecked(reader.GetIntFromData("unit_melee"));
    ui->leGenScriptLoc->setText((ModPath.substr(0,ModPath.find(ModName)) + reader.GetStrFromData("unit_generalscripts")).c_str());
    ui->leBuffLoc->setText((ModPath.substr(0,ModPath.find(ModName)) + reader.GetStrFromData("unit_buffscripts")).c_str());
    ui->lePhysicsLoc->setText((ModPath.substr(0,ModPath.find(ModName)) + reader.GetStrFromData("unit_physics")).c_str());
    ui->leAILoc->setText((ModPath.substr(0,ModPath.find(ModName)) + reader.GetStrFromData("unit_ai")).c_str());
    ui->leHPBar->setText((ModPath.substr(0,ModPath.find(ModName)) + reader.GetStrFromData("unit_hp_bar_tex")).c_str());
    ui->leManaBar->setText((ModPath.substr(0,ModPath.find(ModName)) + reader.GetStrFromData("unit_mana_bar_tex")).c_str());

    //Now, we update the ui with the texture and sound data
    for(size_t i = 0; i < reader.GetIntFromData("unit_texture_counter"); i++)
    {
        tmp.name = reader.GetStrFromData("unit_texture_" + intToStr(i) + "_name").c_str();
        tmp.path = reader.GetStrFromData("unit_texture_" + intToStr(i)).c_str();
        ui->lstTextures->addItem(tmp.name);
        ui->lstTextures->setCurrentRow(i);
        textures.push_back(tmp);
    }

    for(size_t i = 0; i < reader.GetIntFromData("unit_sound_counter"); i++)
    {
        tmp.name = reader.GetStrFromData("unit_sound_" + intToStr(i) + "_name").c_str();
        tmp.path = reader.GetStrFromData("unit_sound_" + intToStr(i)).c_str();
        ui->lstSounds->addItem(tmp.name);
        ui->lstSounds->setCurrentRow(i);
        sounds.push_back(tmp);
    }

    //Close the file
    reader.CloseFile();
}

void UnitSettings::SetRootLocation(const std::string &modName, const std::string &modPath)
{
    ModName = modName;
    ModPath = modPath;
}

void UnitSettings::on_pbBuffBrowse_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Script","" ,"Scripts (*.py *.pyc *.lua *luo);; All Files (*.*)");
    ui->leBuffLoc->setText(tmp);
}

void UnitSettings::on_pbBrowseTexture_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"Texture Descriptor File (*.txt);; All Files (*.*)");
    ui->leTextLoc->setText(tmp);
}

void UnitSettings::on_pbGenScriptBrowse_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Script","" ,"Scripts (*.py *.pyc *.lua *luo);; All Files (*.*)");
    ui->leGenScriptLoc->setText(tmp);
}

void UnitSettings::on_pbAIBrowse_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Script","" ,"Scripts (*.py *.pyc *.lua *luo);; All Files (*.*)");
    ui->leAILoc->setText(tmp);
}

void UnitSettings::on_pbHPBar_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"Texture Descriptor File (*.txt);; All Files (*.*)");
    ui->leHPBar->setText(tmp);
}

void UnitSettings::on_pbManaBar_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"Texture Descriptor File (*.txt);; All Files (*.*)");
    ui->leManaBar->setText(tmp);
}

void UnitSettings::on_pbBrowseSound_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Sound Descriptor File","" ,"Sound Descriptor File (*.txt);; All Files (*.*)");
    ui->leSoundLoc->setText(tmp);
}

void UnitSettings::on_pbPhysicsBrowse_clicked()
{
    doc->setFileMode(QFileDialog::AnyFile);
    QString tmp = doc->getOpenFileName(NULL, "Select Physics Descriptor File","" ,"Physics Descriptor File (*.txt);; All Files (*.*)");
    ui->lePhysicsLoc->setText(tmp);
}

void UnitSettings::on_cbHasBars_clicked()
{
    if(ui->cbHasBars->isChecked())
    {
        ui->leHPBar->setEnabled(true);
        ui->leManaBar->setEnabled(true);
        ui->pbHPBar->setEnabled(true);
        ui->pbManaBar->setEnabled(true);
        ui->sbBarH->setEnabled(true);
        ui->sbBarW->setEnabled(true);
        ui->cbShowHP->setEnabled(true);
        ui->cbShowMana->setEnabled(true);
    }
    else
    {
        ui->leHPBar->setEnabled(false);
        ui->leManaBar->setEnabled(false);
        ui->pbHPBar->setEnabled(false);
        ui->pbManaBar->setEnabled(false);
        ui->sbBarH->setEnabled(false);
        ui->sbBarW->setEnabled(false);
        ui->cbShowHP->setEnabled(false);
        ui->cbShowMana->setEnabled(false);
    }
}

void UnitSettings::on_pbAddTexture_clicked()
{
    if(ui->leTextName->text().isEmpty() || ui->leTextLoc->text().isEmpty())
        QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    else
    {
        //Set up metadata
        AssetNode tmp;
        tmp.name = ui->leTextName->text();
        tmp.path = ui->leTextLoc->text();
        tmp.type = NONETYPE;
        //Save it
        textures.push_back(tmp);

        //update ui
        ui->lstTextures->addItem(tmp.name);
    }
}

void UnitSettings::on_pbAddSound_clicked()
{

    if(ui->leSoundName->text().isEmpty() || ui->leSoundLoc->text().isEmpty())
        QMessageBox::critical(this, "Error!", "Error: Either the filename or the object name was not specified. Fill the missing fields and try again!");
    else
    {
        //Set up metadata
        AssetNode tmp;
        tmp.name = ui->leSoundName->text();
        tmp.path = ui->leSoundLoc->text();
        tmp.type = NONETYPE;
        //Save it
        sounds.push_back(tmp);

        //update ui
        ui->lstSounds->addItem(tmp.name);
        ui->lstSounds->setCurrentRow(ui->lstSounds->count() - 1);//Select the last item
    }
}

void UnitSettings::on_pbRemTexture_clicked()
{
    for(std::list<AssetNode>::iterator itr = textures.begin(); itr != textures.end(); itr++)
    {
        AssetNode& tmp = *itr;
        if(tmp.name == ui->lstTextures->currentItem()->text())//Search for the item
        {
            //Remove the contents
            delete ui->lstTextures->currentItem();
            textures.remove(tmp);
        }
    }
}

void UnitSettings::on_pbRemSound_clicked()
{
    for(std::list<AssetNode>::iterator itr = sounds.begin(); itr != sounds.end(); itr++)
    {
        AssetNode& tmp = *itr;
        if(tmp.name == ui->lstSounds->currentItem()->text())//Search for the item
        {
            //Remove the contents
            delete ui->lstSounds->currentItem();
            sounds.remove(tmp);
        }
    }
}

void UnitSettings::on_pbCreateUnit_clicked()
{
    if(ui->leUnitName->text().isEmpty())
        QMessageBox::critical(this, "Error!", "Error: The object name was not specified. Fill the missing fields and try again!");
    else
    {
        size_t i = 0;
        //Set up metadata
        unit_descriptor.name = ui->leUnitName->text();
        unit_descriptor.path = (ModName + "/Creatures/" + unit_descriptor.name.toStdString()).c_str();
        switch(ui->cbUnitType->currentIndex())
        {
        case 0:
            unit_descriptor.type = OBJTYPE | UNIT;
            break;
        case 1:
            unit_descriptor.type = OBJTYPE | OBJECT;
            break;
        default:
            unit_descriptor.type = OBJTYPE | PROJECTILE;
            break;
        }

        //Now we create the file on disk
        copyfile((ModPath + "/Creatures/template.txt").c_str(),(ModPath + "/Creatures/" + unit_descriptor.name.toStdString() + ".txt").c_str());
        //Update file
        data_base reader((ModPath + "/Creatures/" + unit_descriptor.name.toStdString() + ".txt").c_str());
        data_base writer((ModPath + "/Creatures/" + unit_descriptor.name.toStdString() + ".txt").c_str(), false);
        //Update script and bar paths
        writer.WriteValue(ui->leUnitName->text().toStdString(), "unit_name");
        writer.WriteValue(extract_correct_path(ui->lePhysicsLoc->text().toStdString(), ModName), "unit_physics");
        writer.WriteValue(extract_correct_path(ui->leGenScriptLoc->text().toStdString(), ModName), "unit_generalscripts");
        writer.WriteValue(extract_correct_path(ui->leBuffLoc->text().toStdString(), ModName), "unit_buffscripts");
        writer.WriteValue(extract_correct_path(ui->leAILoc->text().toStdString(), ModName), "unit_ai");
        writer.WriteValue(extract_correct_path(ui->leHPBar->text().toStdString(), ModName), "unit_hp_bar_tex");
        writer.WriteValue(extract_correct_path(ui->leManaBar->text().toStdString(), ModName), "unit_mana_bar_tex");
        //Update unit basic stats
        writer.WriteValue(intToStr(ui->sbHP->value()), "unit_hp");
        writer.WriteValue(intToStr(ui->sbMana->value()), "unit_mana");
        writer.WriteValue(intToStr(ui->sbAD->value()), "unit_ad");
        writer.WriteValue(intToStr(ui->sbAP->value()), "unit_ap");
        writer.WriteValue(intToStr(ui->sbRange->value()), "unit_range");
        writer.WriteValue(intToStr(ui->sbVRange->value()), "unit_vRange");
        writer.WriteValue(intToStr(ui->sbMSpeed->value()), "unit_mSpeed");
        writer.WriteValue(numToStr(ui->dsbASpeed->value()), "unit_aSpeed");
        writer.WriteValue(intToStr(ui->sbBarH->value()), "unit_mana_bar_h");
        writer.WriteValue(intToStr(ui->sbBarW->value()), "unit_mana_bar_w");
        writer.WriteValue(intToStr(ui->sbBarH->value()), "unit_hp_bar_h");
        writer.WriteValue(intToStr(ui->sbBarW->value()), "unit_hp_bar_w");

        //Update boolean options
        if(ui->cbHasBars->isChecked())
        {
            writer.WriteValue("1", "unit_has_bars");

            if(ui->cbShowHP->isChecked())
                writer.WriteValue("1", "unit_hp_bar");
            else
                writer.WriteValue("0", "unit_hp_bar");

            if(ui->cbShowMana->isChecked())
                writer.WriteValue("1", "unit_mana_bar");
            else
                writer.WriteValue("0", "unit_mana_bar");
        }
        else
        {
            writer.WriteValue("0", "unit_has_bars");
            writer.WriteValue("0", "unit_hp_bar");
            writer.WriteValue("0", "unit_mana_bar");

        }

        if(ui->cbHasBuffs->isChecked())
            writer.WriteValue("1", "unit_has_buff");
        else
            writer.WriteValue("0", "unit_has_buff");

        if(ui->cbUnitMelee->isChecked())
            writer.WriteValue("1", "unit_melee");
        else
            writer.WriteValue("0", "unit_melee");


        //Update unit type
        switch(unit_descriptor.type)
        {
        case OBJTYPE | UNIT:
            writer.WriteValue("u", "unit_type");
            break;
        case OBJTYPE | OBJECT:
            writer.WriteValue("o", "unit_type");
            break;
        default:
            writer.WriteValue("p", "unit_type");
            break;
        }

        //Update textures
        writer.WriteValue(intToStr(textures.size()), "unit_texture_counter");
        for(std::list<AssetNode>::iterator itr = textures.begin(); itr != textures.end(); itr++)
        {
            AssetNode& tmp = *itr;
            std::string searchTerm = "unit_texture_" + intToStr(i) + "_name";
            if(reader.SearchTermExists(searchTerm))
            {
                if(reader.GetStrFromData("unit_texture_default") == searchTerm)
                {
                    writer.WriteValueWithLineIndex(tmp.name.toStdString(), searchTerm, 1);
                    writer.WriteValue(extract_correct_path(tmp.path.toStdString(), ModName), "unit_texture_" + intToStr(i));
                }
                else
                {
                    writer.WriteValue(tmp.name.toStdString(), searchTerm);
                    writer.WriteValue(extract_correct_path(tmp.path.toStdString(), ModName), "unit_texture_" + intToStr(i));
                }
            }
            else
            {
                writer.WriteValue(searchTerm + " = ;\n");
                writer.WriteValue("unit_texture_" + intToStr(i) + " = ;\n");
                writer.WriteValue(tmp.name.toStdString(), searchTerm);
                writer.WriteValue(extract_correct_path(tmp.path.toStdString(), ModName), "unit_texture_" + intToStr(i));
            }
            i++;
        }

        //Update sounds
        i = 0;
        writer.WriteValue(intToStr(sounds.size()), "unit_sound_counter");
        for(std::list<AssetNode>::iterator itr = sounds.begin(); itr != sounds.end(); itr++)
        {
            AssetNode& tmp = *itr;
            std::string searchTerm = "unit_sound_" + intToStr(i) + "_name";
            if(reader.SearchTermExists(searchTerm))
            {
                if(reader.GetStrFromData("unit_sound_default") == searchTerm)
                {
                    writer.WriteValueWithLineIndex(tmp.name.toStdString(), searchTerm, 1);
                    writer.WriteValue(extract_correct_path(tmp.path.toStdString(), ModName), "unit_sound_" + intToStr(i));
                }
                else
                {
                    writer.WriteValue(tmp.name.toStdString(), searchTerm);
                    writer.WriteValue(extract_correct_path(tmp.path.toStdString(), ModName), "unit_sound_" + intToStr(i));
                }
            }
            else
            {
                writer.WriteValue(searchTerm + " = ;\n");
                writer.WriteValue("unit_sound_" + intToStr(i) + " = ;\n");
                writer.WriteValue(tmp.name.toStdString(), searchTerm);
                writer.WriteValue(extract_correct_path(tmp.path.toStdString(), ModName), "unit_sound_" + intToStr(i));
            }
            i++;
        }

        //Now we start updating the main window
        win->AddTreeViewItem(REGISTEREDOBJS, ui->leUnitName->text().toStdString(), false, win->GetTreeViewRoot(REGISTEREDOBJS, "Unit"));
        win->RegisterAsset(ui->leUnitName->text().toStdString(), ModPath + "/Creatures/" + unit_descriptor.name.toStdString(), OBJTYPE|UNIT);

        //Save file
        reader.CloseFile();
        writer.CloseFile();
    }
}
