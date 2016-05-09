#ifndef TRIGGER_SETTINGS_H
#define TRIGGER_SETTINGS_H

#include <QDialog>
#include <QFileDialog>

class MainWindow;

namespace Ui {
class trigger_settings;
}

class trigger_settings : public QDialog
{
    Q_OBJECT

public:
    explicit trigger_settings(MainWindow *parent = 0);
    ~trigger_settings();

    void SetRootLocation(const std::string &modName, const std::string &modPath);
    void LoadTrigger(const std::string& file);
private slots:
    void on_pbScript_clicked();

    void on_pbSave_clicked();

private:
    Ui::trigger_settings *ui;
    MainWindow* win;
    QFileDialog *open;
    std::string mod_name, mod_path;
};

#endif // TRIGGER_SETTINGS_H
