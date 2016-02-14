#include "layersettings.h"
#include "ui_layersettings.h"

Layersettings::Layersettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Layersettings)
{
    ui->setupUi(this);
}

Layersettings::~Layersettings()
{
    delete ui;
}
