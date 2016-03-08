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

void trigger_settings::on_pbScript_clicked()
{

}
