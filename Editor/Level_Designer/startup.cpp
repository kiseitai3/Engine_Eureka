#include "startup.h"
#include "ui_startup.h"
#include <QFileDialog>
#include <QMessageBox>
#include "globals.h"
#include "conversion.h"


#define ERROR -1

Startup::Startup(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::Startup)
{
  ui->setupUi(this);
}

Startup::~Startup()
{
  delete ui;
}


