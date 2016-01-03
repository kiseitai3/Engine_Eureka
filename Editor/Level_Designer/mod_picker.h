#ifndef MOD_PICKER_H
#define MOD_PICKER_H

#include <QDialog>
#include "data_base.h"
#include "conversion.h"

namespace Ui {
class mod_picker;
}

class mod_picker : public QDialog
{
    Q_OBJECT

public:
    explicit mod_picker(QWidget *parent = 0);
    ~mod_picker();

    //Extra
    void AddMod(const std::string& name);
    void AutoSelect();

    std::string getSelectedMod() const;
    size_t getSelectedModIndex() const;


private slots:
    void on_pbAddMod_clicked();

    void on_buttonBox_accepted();

private:
    Ui::mod_picker *ui;
};

std::string getModName(const data_base& dom, std::string& description);

#endif // MOD_PICKER_H
