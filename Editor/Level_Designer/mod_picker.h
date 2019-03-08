#ifndef MOD_PICKER_H
#define MOD_PICKER_H

#include <QDialog>
#include <vector>
#include "data_base.h"
#include "conversion.h"
#include "globals.h"

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

    //Getter
    std::string getSelectedMod() const;
    size_t getSelectedModIndex() const;
    std::vector<std::string> getStringList() const;

    //Setter
    void setDialogTitle(const std::string& title);


private slots:
    void on_pbAddMod_clicked();

    void on_buttonBox_accepted();

private:
    Ui::mod_picker *ui;
};

std::string getModName(const data_base& dom, std::string& description);
std::vector<std::string> getList(const SearchPacket& p,
                                 const std::string title = "Function List",
                                 size_t searchType = NOSEARCH);

#endif // MOD_PICKER_H
