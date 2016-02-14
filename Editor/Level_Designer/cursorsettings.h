#ifndef CURSORSETTINGS_H
#define CURSORSETTINGS_H

#include <QDialog>
#include <QFileDialog>
#include "data_base.h"
#include "mainwindow.h"

namespace Ui {
class cursorsettings;
}

class cursorsettings : public QDialog
{
    Q_OBJECT

public:
    explicit cursorsettings(QWidget *parent = 0);
    ~cursorsettings();

    void SetRootLocation(const std::string &modName, const std::string &modPath);
    void LoadSet(const std::string& loc);
private slots:
    void on_pbSound_clicked();

    void on_pbTexture_clicked();

    void on_pbCreate_clicked();

    void on_pbCreateAdd_clicked();

    void on_pbRemove_clicked();

    void on_pbAdd_clicked();

    void on_pbLoadSet_clicked();

    void on_pbSaveSet_clicked();

private:
    Ui::cursorsettings *ui;
    QFileDialog *open;
    std::string ModName, ModPath;
};

#endif // CURSORSETTINGS_H
