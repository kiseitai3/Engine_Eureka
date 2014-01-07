#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startup.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  Startup dialog(this);
  dialog.exec();
}

MainWindow::~MainWindow()
{
  delete ui;
}
