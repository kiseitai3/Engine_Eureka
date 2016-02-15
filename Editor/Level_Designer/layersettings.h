#ifndef LAYERSETTINGS_H
#define LAYERSETTINGS_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class Layersettings;
}

class Layersettings : public QDialog
{
    Q_OBJECT

public:
    explicit Layersettings(QWidget *parent = 0);
    ~Layersettings();

    void SetRootLocation(const std::string &modName, const std::string &modPath);
    void LoadSet(const std::string& loc);
    void LoadLayer(const std::string& loc);
private slots:
    void on_pbSave_clicked();

    void on_pbBrowse_clicked();

    void on_pbSaveAdd_clicked();

    void on_pbSetAdd_clicked();

    void on_pbSetRemove_clicked();

    void on_pbSetOpen_clicked();

    void on_pbSetSave_clicked();

private:
    Ui::Layersettings *ui;
    QFileDialog *open;
    std::string ModPath, ModName;
};

#endif // LAYERSETTINGS_H
