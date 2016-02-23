#include "trigger_settings.h"
#include "ui_trigger_settings.h"

trigger_settings::trigger_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::trigger_settings)
{
    ui->setupUi(this);
}

trigger_settings::~trigger_settings()
{
    delete ui;
}
