#include "mainwindow.h"
#include <QApplication>
#include "startup.h"



int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  //Let's run the custom dialog box prior to displaying the window. We have to collect the project file path!

  MainWindow w;
  w.show();

  return a.exec();
}

