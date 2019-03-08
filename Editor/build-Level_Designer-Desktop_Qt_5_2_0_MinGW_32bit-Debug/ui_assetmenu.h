/********************************************************************************
** Form generated from reading UI file 'assetmenu.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSETMENU_H
#define UI_ASSETMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_AssetMenu
{
public:
    QTreeWidget *tvItemsMenu;

    void setupUi(QDialog *AssetMenu)
    {
        if (AssetMenu->objectName().isEmpty())
            AssetMenu->setObjectName(QStringLiteral("AssetMenu"));
        AssetMenu->resize(341, 312);
        tvItemsMenu = new QTreeWidget(AssetMenu);
        tvItemsMenu->setObjectName(QStringLiteral("tvItemsMenu"));
        tvItemsMenu->setGeometry(QRect(10, 10, 321, 291));

        retranslateUi(AssetMenu);

        QMetaObject::connectSlotsByName(AssetMenu);
    } // setupUi

    void retranslateUi(QDialog *AssetMenu)
    {
        AssetMenu->setWindowTitle(QApplication::translate("AssetMenu", "Dialog", 0));
        QTreeWidgetItem *___qtreewidgetitem = tvItemsMenu->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("AssetMenu", "Name", 0));
    } // retranslateUi

};

namespace Ui {
    class AssetMenu: public Ui_AssetMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSETMENU_H
