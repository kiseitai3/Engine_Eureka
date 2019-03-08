#include "texturesettings.h"
#include "ui_texturesettings.h"

TextureSettings::TextureSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextureSettings)
{
    ui->setupUi(this);
}

TextureSettings::~TextureSettings()
{
    delete ui;
}
