#include "ui_elements.h"
#include "ui_ui_elements.h"
#include "color_picker.h"
#include "mainwindow.h"

#include <QRgb>

UI_Elements::UI_Elements(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::UI_Elements)
{
    ui->setupUi(this);
    open = new QFileDialog();
    win = parent;
}

UI_Elements::~UI_Elements()
{
    if(open)
        delete open;
    delete ui;
}

void UI_Elements::SetRootLocation(const std::string &modName, const std::string &modPath)
{
    ModName = modName;
    ModPath = modPath;
}

void UI_Elements::on_pbTextureBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTexture->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void UI_Elements::on_pbFontBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leFont->setText(open->getOpenFileName(NULL, "Select Font File","" ,"Fonts (*.*)"));

}

void UI_Elements::on_pbTextureEnterBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTextureEnter->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void UI_Elements::on_pbTextureClickBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTextureClick->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void UI_Elements::on_pbTextureIdleBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTextureIdle->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void UI_Elements::on_pbTextureSelectBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTextureSelect->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void UI_Elements::on_pbTextureDownBrowse_clicked()
{
    open->setFileMode(QFileDialog::AnyFile);
    ui->leTextureDown->setText(open->getOpenFileName(NULL, "Select Texture Descriptor File","" ,"All Files (*.*);; Texture Descriptor (*.txt)"));
}

void UI_Elements::on_pbFontColorPicker_clicked()
{
    Color_picker picker;
    picker.show();
    ui->pbFontColorPicker->setPalette(picker.GetColor());
}

void UI_Elements::on_pbSave_clicked()
{
    int r,g,b;
    std::string font_file = extract_file_name(ui->leFont->text().toStdString());
    std::string font_path = ModPath + "/UI_elements/" + font_file;
    std::string textbox_file = ModPath + "/UI_elements/" + ui->leName->text().toStdString();
    data_base writer;

    //Get color bytes
    ui->pbFontColorPicker->palette().color(QPalette::Window).getRgb(&r,&g,&b);

    //copy font
    copyfile(ui->leFont->text().toStdString(), font_path);

    //Create textbox file, which is required regardless of whether it is a button or not!
    copyfile(ModPath + "/UI_elements/textbox_default.txt", textbox_file + ".txt");
    writer.OpenFile((textbox_file + ".txt").c_str(), false);
    writer.WriteValue(extract_correct_path(ui->leTexture->text().toStdString(), ModName), "texture_file");
    writer.WriteValue(extract_correct_path(ui->leFont->text().toStdString(), ModName), "textbox_fontloc");
    writer.WriteValue(ui->leName->text().toStdString(), "name");
    writer.WriteValue("textbox", "textbox_type");
    writer.WriteValue(intToStr(ui->cbWrite->isChecked()), "texture_writemode");
    writer.WriteValue(intToStr(r), "textbox_colorbyte1");
    writer.WriteValue(intToStr(g), "textbox_colorbyte2");
    writer.WriteValue(intToStr(b), "textbox_colorbyte3");
    writer.WriteValue(intToStr(ui->sbFontSize->value()), "textbox_font_size");
    writer.WriteValue(intToStr(ui->sbX->value()), "textbox_x");
    writer.WriteValue(intToStr(ui->sbY->value()), "textbox_y");
    writer.WriteValue(intToStr(ui->sbTextX->value()), "textbox_txt_x");
    writer.WriteValue(intToStr(ui->sbTextY->value()), "textbox_txt_y");
    writer.WriteValue(intToStr(ui->sbTextH->value()), "textbox_txt_h");
    writer.WriteValue(intToStr(ui->sbTextW->value()), "textbox_txt_w");

    //Now we start updating the main window
    win->AddTreeViewItem(REGISTEREDOBJS, ui->leName->text().toStdString() + "_textbox", false, win->GetTreeViewRoot(REGISTEREDOBJS, "UI"));
    win->RegisterAsset(ui->leName->text().toStdString() + "_textbox", textbox_file + ".txt", UITYPE);

    //Create button file if it is a button
    if(ui->cbType->isChecked())
    {
        //If this is a button, overwrite type before closing the textbox file
        writer.WriteValue("button", "textbox_type");
        writer.CloseFile();

        //Create button file
        copyfile(ModPath + "/UI_elements/button_default.txt", textbox_file + "_button.txt");

        //Now we update it!
        writer.OpenFile((textbox_file + "_button.txt").c_str(), false);
        writer.WriteValue(extract_correct_path(textbox_file + ".txt", ModName), "textbox_file");
        writer.WriteValue(extract_correct_path(ui->leTextureEnter->text().toStdString(), ModName), "button_tex_enter");
        writer.WriteValue(extract_correct_path(ui->leTextureClick->text().toStdString(), ModName), "button_tex_clicking");
        writer.WriteValue(extract_correct_path(ui->leTextureIdle->text().toStdString(), ModName), "button_tex_idle");
        writer.WriteValue(extract_correct_path(ui->leTextureSelect->text().toStdString(), ModName), "button_tex_selected");
        writer.WriteValue(extract_correct_path(ui->leTextureDown->text().toStdString(), ModName), "button_tex_down");

        //Now we start updating the main window
        win->AddTreeViewItem(REGISTEREDOBJS, ui->leName->text().toStdString() + "_button", false, win->GetTreeViewRoot(REGISTEREDOBJS, "UI"));
        win->RegisterAsset(ui->leName->text().toStdString(), textbox_file + "_button.txt", UITYPE);
    }

    //Close the file
    writer.CloseFile();
}
