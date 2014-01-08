#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class data_base;

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void on_action_Exit_triggered();

private:
  Ui::MainWindow *ui;
  data_base* DOM;
};

#endif // MAINWINDOW_H
