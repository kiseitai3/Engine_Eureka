#include "startup.h"
#include "ui_startup.h"
#include <QFileDialog>
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

void Startup::on_pbOpenBrowse_clicked()
{
  QFileDialog open(this);
  open.setFileMode(QFileDialog::Directory);
  ui->leLocation->setText(open.getExistingDirectory(this, "Project Folder", "."));
}

void Startup::on_pbNameBrowse_clicked()
{
  QFileDialog open(this);
  open.setFileMode(QFileDialog::AnyFile);
  std::string filePath = open.getOpenFileName(this, "Project File", ui->leLocation->text(),"*.pr").toStdString();
  while(findString(ui->leLocation->text().toStdString().c_str(), filePath.c_str()) == ERROR)
    {
      filePath = open.getOpenFileName(this, "Project File: Selected File is not Within Project Folder", ui->leLocation->text(),"*.pr").toStdString();
    };
  filePath = sliceStr(filePath,ui->leLocation->text().toStdString().size(), filePath.size());
  ui->leName->setText(QString(filePath.c_str()));
}

void Startup::on_buttonBox_accepted()
{
  MOD = ui->leLocation->text().toStdString().c_str();
  projName = ui->leName->text().toStdString().c_str();
  this->close();
}
