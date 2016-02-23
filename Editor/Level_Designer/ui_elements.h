#ifndef UI_ELEMENTS_H
#define UI_ELEMENTS_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class UI_Elements;
}

class UI_Elements : public QDialog
{
    Q_OBJECT

public:
    explicit UI_Elements(QWidget *parent = 0);
    ~UI_Elements();

    void SetRootLocation(const std::string &modName, const std::string &modPath);
private slots:
    void on_pbTextureBrowse_clicked();

    void on_pbFontBrowse_clicked();

    void on_pbTextureEnterBrowse_clicked();

    void on_pbTextureClickBrowse_clicked();

    void on_pbTextureIdleBrowse_clicked();

    void on_pbTextureSelectBrowse_clicked();

    void on_pbTextureDownBrowse_clicked();

    void on_pbFontColorPicker_clicked();

    void on_pbSave_clicked();

private:
    Ui::UI_Elements *ui;
    QFileDialog *open;
    std::string ModName, ModPath;
};

#endif // UI_ELEMENTS_H
