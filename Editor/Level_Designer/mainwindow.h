#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
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

    void AddTreeViewItem(char treeView, const std::string& name, bool root = true, QTreeWidgetItem* parent = NULL);
    void RegisterAsset(const std::string& name, const std::string& path, size_t type);
    void RemoveAsset(const std::string& name);
    QTreeWidgetItem* GetTreeViewRoot(char treeView, const std::string& rowName);
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

  void on_twTabs_currentChanged(int index);

  void on_tvRegisteredObjects_itemEntered(QTreeWidgetItem *item, int column);

  void on_pbDelAsset_clicked();

  void on_pbDelObj_clicked();

  void on_sbWidth_editingFinished();

  void on_sbWidth_valueChanged(int arg1);

private:
  Ui::MainWindow *ui;
  data_base* DOM, *DOMWriter;
  QFileDialog *open;
  QGraphicsScene* textPrev, *worldPrev;
  std::string modName, modDescription, modPath, modRootPath;
  Game* engine;

  std::list<AssetNode> ojs;
  std::map<QString, AssetNode> assets;

  //Methods
  bool modExists(size_t& index);
  void loadProjectObjects();
  void registerProjectObjects(const QStringList& lst, const std::string& path, size_t type);
  void clearTreeViews(size_t treeView, QTreeWidgetItem* root);
  std::string getRelPath(const std::string& path);
};

void build_new_directory_tree(const std::string source, const std::string &target);
std::string extract_file_name(const std::string& path);
std::string extract_correct_path(const std::string& fullPath, const std::string& modName);
void remove_asset_contents(const std::string& rootPath, const QString &path, size_t type);
bool pluginExists(const std::string& searchTerm, const data_base& file, size_t& index);
std::string getType(char type);

#endif // MAINWINDOW_H
