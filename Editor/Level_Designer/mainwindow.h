#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mod_picker.h"


class Game;
class data_base;
class QFileDialog;
class QGraphicsScene;

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

  void on_pbTextureBrowse_clicked();

  void on_pbRegTexture_clicked();

  void on_pbSoundBrowse_clicked();

  void on_pbRegSound_clicked();

  void on_pbCodeBrowse_clicked();

  void on_pbRegCode_clicked();

  void on_pbRegPhys_clicked();

  void on_cbHasMagnetic_clicked();

  void on_pbNewObj_clicked();

private:
  Ui::MainWindow *ui;
  data_base* DOM, *DOMWriter;
  QFileDialog *open;
  QGraphicsScene* textPrev, *worldPrev;
  std::string modName, modDescription, modPath, modRootPath;
  Game* engine;

  //Methods
  bool modExists(size_t& index);
};

void build_new_directory_tree(const std::string source, const std::string &target);
std::string extract_file_name(const std::string& path);
std::string extract_correct_path(const std::string& fullPath, const std::string& modName);
bool pluginExists(const std::string& searchTerm, const data_base& file, size_t& index);

#endif // MAINWINDOW_H
