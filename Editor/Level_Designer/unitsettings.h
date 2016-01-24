#ifndef UNITSETTINGS_H
#define UNITSETTINGS_H

#include <QDialog>
#include "globals.h"

class QFileDialog;

namespace Ui {
class UnitSettings;
}

class UnitSettings : public QDialog
{
    Q_OBJECT

public:
    explicit UnitSettings(QWidget *parent = 0);
    ~UnitSettings();

    void LoadData(cstr file);
    void SetRootLocation(const std::string& modName, const std::string& modPath);

private slots:
    void on_pbBuffBrowse_clicked();

    void on_pbBrowseTexture_clicked();

    void on_pbGenScriptBrowse_clicked();

    void on_pbAIBrowse_clicked();

    void on_pbHPBar_clicked();

    void on_pbManaBar_clicked();

    void on_pbBrowseSound_clicked();

    void on_pbPhysicsBrowse_clicked();

    void on_cbHasBars_clicked();

    void on_pbAddTexture_clicked();

    void on_pbAddSound_clicked();

    void on_pbRemTexture_clicked();

    void on_pbRemSound_clicked();

    void on_pbCreateUnit_clicked();

private:
    Ui::UnitSettings *ui;
    QFileDialog* doc;
    std::list<AssetNode> textures;
    std::list<AssetNode> sounds;
    std::string ModName, ModPath;
    AssetNode unit_descriptor;
};

#endif // UNITSETTINGS_H
