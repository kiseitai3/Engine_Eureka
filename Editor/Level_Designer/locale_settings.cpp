#include "locale_settings.h"
#include "ui_locale_settings.h"

Locale_settings::Locale_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Locale_settings)
{
    ui->setupUi(this);
}

Locale_settings::~Locale_settings()
{
    delete ui;
}
