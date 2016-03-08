#ifndef TRIGGER_SETTINGS_H
#define TRIGGER_SETTINGS_H

#include <QDialog>

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

    void SetRootLocation(const std::string &modName, const std::string &modPath, const std::string &lvlName);
private slots:
    void on_pbScript_clicked();

private:
    Ui::trigger_settings *ui;
    MainWindow* win;
};

#endif // TRIGGER_SETTINGS_H
