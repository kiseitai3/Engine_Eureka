#include "assetmenu.h"
#include "ui_assetmenu.h"

AssetMenu::AssetMenu(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::AssetMenu)
{
    ui->setupUi(this);
    win = parent;
}

AssetMenu::~AssetMenu()
{
    delete ui;
}

void AssetMenu::LoadItems(const QTreeWidget &source)
{
    QTreeWidgetItem* top = NULL;
    ui->tvItemsMenu->clear();
    for(size_t i = 0; i < source.topLevelItemCount(); i++)
    {
        top =  new QTreeWidgetItem(*source.topLevelItem(i));
        createChildChain(source.topLevelItem(i), top);
        ui->tvItemsMenu->addTopLevelItem(top);
    }
}

void AssetMenu::SetPosition(size_t x, size_t y)
{
    this->setGeometry(x, y, this->geometry().width(), this->geometry().height());
}

void AssetMenu::createChildChain(QTreeWidgetItem *parent, QTreeWidgetItem * chain)
{
    QTreeWidgetItem* itm = NULL;
    if(parent == NULL)
        return;

    for(size_t i = 0; i < parent->childCount(); i++)
    {
        itm = new QTreeWidgetItem(*parent->child(i));
        createChildChain(parent->child(i), itm);
        chain->addChild(itm);
    }

}

void AssetMenu::on_tvItemsMenu_doubleClicked(const QModelIndex &index)
{
    AssetNode itm = win->GetAsset(ui->tvItemsMenu->currentItem()->text(0).toStdString());
    itm.offset.X = win->mapFromParent(pos()).x();
    itm.offset.Y = win->mapFromParent(pos()).y();
    win->RegisterObject(itm);
}
