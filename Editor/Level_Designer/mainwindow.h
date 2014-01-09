#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class data_base;
class QFileDialog;

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

  void on_pbModBrowse_clicked();

  void on_pBInstallBrowse_clicked();

  void on_pbModSave_clicked();

  void on_MainWindow_destroyed();

private:
  Ui::MainWindow *ui;
  data_base* DOM, *DOMWriter;
  QFileDialog *open;

  //Methods
};

#endif // MAINWINDOW_H
