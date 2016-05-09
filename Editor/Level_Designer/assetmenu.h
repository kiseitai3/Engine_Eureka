#ifndef ASSETMENU_H
#define ASSETMENU_H

#include <QDialog>
#include <QTreeWidget>

#include "mainwindow.h"

namespace Ui {
class AssetMenu;
}

class AssetMenu : public QDialog
{
    Q_OBJECT

public:
    explicit AssetMenu(MainWindow *parent = 0);
    ~AssetMenu();


    void LoadItems(const QTreeWidget& source);
    void SetPosition(size_t x, size_t y);
private slots:
    void on_tvItemsMenu_doubleClicked(const QModelIndex &index);

private:
    Ui::AssetMenu *ui;
    MainWindow* win;

    void createChildChain(QTreeWidgetItem* parent, QTreeWidgetItem *chain);
};

#endif // ASSETMENU_H
