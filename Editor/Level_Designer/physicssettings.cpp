#include "physicssettings.h"
#include "ui_physicssettings.h"

PhysicsSettings::PhysicsSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PhysicsSettings)
{
    ui->setupUi(this);
}

PhysicsSettings::~PhysicsSettings()
{
    delete ui;
}
